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

#ifndef HAVE_OPENSSL
  #error "Configure script did not locate OpenSSL"
#endif

#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/rand.h>

#include <libsherpa/random.hxx>
#include <libsherpa/UExcept.hxx>

namespace sherpa {
  namespace rnd {
    void initialize()
    {
#ifdef HAVE_OPENSSL
      /* RAND_status will return 1 without us doing a thing if /dev/urandom
	 is around for OpenSSL to seed itself. In this case, don't bother with
	 this other stuff.
      */
      if(RAND_status())
	return;

#define MAX_READ 32*1024

#if 0
      if(opt_RandomFile.size())
	RAND_load_file(opt_RandomFile.c_str(), MAX_READ);
#endif

      if(getenv("RANDFILE"))
	RAND_load_file(getenv("RANDFILE"), MAX_READ);

      /* Check to see if we are sufficiently initialized */
      if(!RAND_status())
	{
	  THROW(excpt::PrngError, "Insufficient randomness to seed the PRNG");
	}
#endif /* HAVE_OPENSSL */
    }

    ByteString GetBytes(size_t len)
    {
      ByteString s;
      s.resize(len, ' ');

#ifdef HAVE_OPENSSL
      if (RAND_bytes((unsigned char *) s.data(), len) <= 0)
	THROW(excpt::PrngError, format("Problem with PRNG: %s",
				       ERR_reason_error_string(ERR_get_error())));
#endif /* HAVE_OPENSSL */

      return s;
    }
  } /* namespace rnd */
} /* namespace sherpa */
