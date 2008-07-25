#ifndef LIBLIBSHERPA_RANDOM_H
#define LIBLIBSHERPA_RANDOM_H

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

#include <libsherpa/ByteString.hxx>

namespace sherpa {
  namespace rnd {
    /// We use the following ordering for seeding the RNG:
    ///
    /// @li /dev/urandom, if we've got it. If we do, ignore everything else.
    ///
    /// @li opt_RandomFile, it is is set
    ///
    /// @li The RANDFILE env variable, if that is set.  This is assumed
    /// to point to a plain file, or a character device.
    ///
    /// @li The EGD_PATH env variable, if that is set. This is assumed
    /// to point to an EGD socket
    ///
    /// The enviromental variable names were not at random; both are
    /// used fairly widely across OpenSSL-based programs (stunnel,
    /// openldap, etc).
    ///
    /// We limit the read size to 32K, which seems more than enough.

    void initialize();

    /// @brief Returns length random bytes.
    ByteString GetBytes(size_t length);
  } /* namespace rnd */
} /* namespace sherpa */

// Local Variables:
// mode:c++
// End:

#endif /* LIBLIBSHERPA_RANDOM_H */
