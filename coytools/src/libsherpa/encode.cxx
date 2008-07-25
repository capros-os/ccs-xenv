/**************************************************************************
 *
 * Copyright (C) 2000, 2001, 2002, 2003, 2004, 2005, 2006, The EROS
 *   Group, LLC. 
 * Copyright (C) 2004, 2005, 2006, Johns Hopkins University.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or
 * without modification, are permitted provided that the following
 * conditions are met:
 *
 *   - Redistributions of source code must contain the above 
 *     copyright notice, this list of conditions, and the following
 *     disclaimer. 
 *
 *   - Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions, and the following
 *     disclaimer in the documentation and/or other materials 
 *     provided with the distribution.
 *
 *   - Neither the names of the copyright holders nor the names of any
 *     of any contributors may be used to endorse or promote products
 *     derived from this software without specific prior written
 *     permission. 
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 **************************************************************************/

#include "../config.h"

#include <stdint.h>

#include <string>
#include <algorithm>

#include <libsherpa/UExcept.hxx>
#include <libsherpa/util.hxx>
#include <libsherpa/BigNum.hxx>
#include <libsherpa/encode.hxx>

namespace sherpa {
  const char b64chars[] = 
  "ABCDEFGHIJKLMNOP"
  "QRSTUVWXYZabcdef"
  "ghijklmnopqrstuv"
  "wxyz0123456789+-";	/* not slash! */

  static unsigned
  fromhex(char c)
  {
    if (c >= '0' && c <= '9')
      return c - '0';
    else if (c >= 'a' && c <= 'f')
      return c - 'a' + 10;
    else if (c >= 'A' && c <= 'F')
      return c - 'A' + 10;
    else
      THROW(excpt::Malformed, format("Invalid hex character %c", c));
  }

  /* Return decoded sequence of bytes along
   * with length of that sequence in 'len'*/
  ByteString
  hex_decode(std::string s)
  {
    if(s.length() % 2 == 1)
      THROW(excpt::Malformed, "Hexadecimal strings must be even length");

    ByteString out;

    for (size_t u = 0; u < s.length(); u += 2) {
      unsigned char c_upper = s[u];
      unsigned char c_lower = s[u+1];

      unsigned char b;

      b = fromhex(c_upper) << 4;
      b |= fromhex(c_lower);
      out += b;
    }

    return out;
  }

  /* Return encoded string that represents
   * 'len' bytes beginning at buf: */
  std::string
  hex_encode(const ByteString& s)
  {
    static const char *hex_digits = "0123456789abcdef";
    std::string out;

    for (size_t u = 0; u < s.length(); u++) {
      unsigned char upper = (s[u] >> 4) & 0xfu;
      unsigned char lower = s[u] & 0xfu;

      out += hex_digits[upper];
      out += hex_digits[lower];
    }
    return out;
  }

  static unsigned char 
  b64_lookup(unsigned char c)
  {
    if (isupper(c))
      return c - 'A';
    else if (islower(c))
      return c - 'a' + 26;
    else if (isdigit(c))
      return c - '0' + 52;
    else if (c == '+')
      return 62;
    else if (c == '-')
      return 63;
    else
      THROW(excpt::Malformed, format("Invalid base64 character %c", c));
  }

  ByteString
  bad_b64_decode(std::string str)
  {
    const char *s = str.data();
    uint32_t len = str.length();
    ByteString out;

    while (len) {
      uint32_t value = 0;

      if (len >= 4) {
	value = (b64_lookup(s[3]) << 18 |
		 b64_lookup(s[2]) << 12 |
		 b64_lookup(s[1]) << 6 |
		 b64_lookup(s[0]) << 0);
	s += 4;
      }
      else if (len == 3) {
	value = (b64_lookup(s[2]) << 12 |
		 b64_lookup(s[1]) << 6 |
		 b64_lookup(s[0]) << 0);
	s += 3;
      }
      else if (len == 2) {
	value = (b64_lookup(s[1]) << 6 |
		 b64_lookup(s[0]) << 0);
	s += 2;
      }

      /* Len is *always* > 1 */

      if (len == 1)
	THROW(excpt::BadValue, "b64 string truncated");

      if (len >= 4) {
	out += value & 0xffu;
	out += (value >> 8) & 0xffu;
	out += (value >> 16) & 0xffu;
      }
      else if (len == 3) {
	out += value & 0xffu;
	out += (value >> 8) & 0xffu;
      }
      else if (len == 2) {
	out += value & 0xffu;
      }

      len -= std::min(len, 4u);
    }

    return out;
  }

  std::string
  bad_b64_encode(const ByteString& s)
  {
    const uint8_t *cp = s.data();
    size_t len = s.length();
    std::string out;

    while (len) {
      uint32_t take = std::min(len, (size_t)3);
      uint32_t value = 0;
      uint32_t outlen = (take * 8 + 5) / 6;
      uint32_t i;

      if (take == 3) {
	value = cp[2];
	value <<= 8;
      }
      if (take >= 2) {
	value |= cp[1];
	value <<= 8;
      }
      value |= cp[0];
    
      for (i = 0; i < outlen; i++) {
	out += b64chars[value & 0x3f];
	value >>= 6;
      }

      len -= take;
      cp += 3;
    }

    return out;
  }

} /* namespace sherpa */
