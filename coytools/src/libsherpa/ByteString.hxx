#ifndef LIBSHERPA_BYTESTRING_HXX
#define LIBSHERPA_BYTESTRING_HXX

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

#include <string.h>  // for memcpy() and friends

// Need a specialization of char_traits for this:
namespace std {
  template<> struct char_traits<uint8_t> {
    typedef unsigned char char_type;
    typedef int           int_type;
    typedef streampos     pos_type;
    typedef streamoff     off_type;
    typedef mbstate_t     state_type;

    static void assign(uint8_t& c1, const uint8_t& c2) {
      c1 = c2;
    }

    static bool eq(const uint8_t& c1, const uint8_t& c2) {
      return c1 == c2;
    }

    static bool lt(const uint8_t& c1, const uint8_t& c2) {
      return c1 < c2;
    }

    // Do not specialize the length() trait, as there is no correct
    // length() operator for a binary string!
    //  static size_t length(const uint8_t *s) {
    //  }
    //

    static int compare(const uint8_t *s1, const uint8_t *s2, size_t n) {
      return memcmp(s1, s2, n);
    }

    static uint8_t *copy(uint8_t *s1, const uint8_t *s2, size_t n) {
      return (uint8_t*)memcpy(s1, s2, n);
    }

    static uint8_t *move(uint8_t *s1, const uint8_t *s2, size_t n) {
      return (uint8_t*)memmove(s1, s2, n);
    }

    static uint8_t *assign(uint8_t *s, size_t n, char c) {
      return (uint8_t*)memset(s,c,n);
    }

    static const uint8_t *find(const uint8_t *s, size_t n, const char& c) {
      return (const uint8_t*)memchr(s,c,n);
    }

    static int eof() {
      return EOF;
    }

    static int to_int_type(const uint8_t& c) {
      return (int)c;
    }

    static char to_char_type(const int& i) {
      return (uint8_t)i;
    }

    static int not_eof(const int& i) {
      return (i!=EOF) ? 1 : !EOF;
    }

    static bool eq_int_type(const int& i1, const int& i2) {
      return i1 == i2;
    }
  };
}

namespace sherpa {
  typedef std::basic_string<uint8_t> ByteString;
} /* namespace sherpa */

#endif /* LIBSHERPA_BYTESTRING_HXX */
