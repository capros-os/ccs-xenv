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

#ifndef HAVE_OPENSSL
  #error "Configure script did not locate OpenSSL"
#endif

#include <assert.h>

#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/rand.h>

#include <string>

#include <libsherpa/sha1.hxx>

namespace sherpa {

  OpenSHA::OpenSHA()
  {
    SHA1_Init(&context);
    totlen = 0;
    isFinished = false;
  }

  void
  OpenSHA::append(unsigned len, const void *buf)
  {
    if (isFinished)
      return;

    SHA1_Update(&context, buf, len);
    totlen += len;
  }

  void
  OpenSHA::finish()
  {
    if (isFinished)
      return;
  
    SHA1_Final(hash, &context);

    isFinished = true;
  }

  OpenSHA::OpenSHA(std::string s)
  {
    SHA1_Init(&context);

    totlen = 0;
    isFinished = false;

    append(s.length(), s.data());
    finish();
  }

  ByteString
  OpenSHA::byteRepresentation() const
  {
    assert(isFinished);

    return ByteString(hash, 20);
  }

  uint32_t
  OpenSHA::signature32() const
  {
    assert(isFinished);

    return ( (((uint32_t) hash[0]) << 24) |
	     (((uint32_t) hash[1]) << 16) |
	     (((uint32_t) hash[2]) << 8) |
	     ((uint32_t) hash[3]) );
  }

  uint64_t
  OpenSHA::signature64() const
  {
    assert(isFinished);

    return ( (((uint64_t) hash[0]) << 56) |
	     (((uint64_t) hash[1]) << 48) |
	     (((uint64_t) hash[2]) << 40) |
	     (((uint64_t) hash[3]) << 32) |
	     (((uint64_t) hash[4]) << 24) |
	     (((uint64_t) hash[5]) << 16) |
	     (((uint64_t) hash[6]) << 8) |
	     ((uint64_t) hash[7]) );
  }

} /* namespace sherpa */
