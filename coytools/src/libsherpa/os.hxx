#ifndef LIBSHERPA_OS_H
#define LIBSHERPA_OS_H

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

#include <stdint.h>
#include <string>

namespace sherpa {
  /* OS-dependent functions: */

  namespace os
  {
    std::string GetUserName(void);
    std::string GetHostName(void);
    std::string GetHomeDirAsString(void);
    std::string GetISOTime(void);
    uint32_t GetPid(void);
    void create_local_lockfile(std::string path);
    bool validate_local_lockfile(std::string path);
    void nap(uint32_t ms);
    bool pid_exists(uint32_t pid);
    bool is_local_path(std::string path);
    void background(void);
    void daemonize(void);

    /* Regrettably, diff output represents time in a different way from ISO: */
    std::string ToDiffTime(time_t);

    /* Convert from internal time representation to ISO representation: */
    std::string ToISO(time_t);
    time_t FromISO(std::string);

    int GetServicePort(const char *name, const char *proto);
  } /* namespace os */

} /* namespace sherpa */

// Local Variables:
// mode:c++
// End:

#endif /* LIBSHERPA_OS_H */
