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

#include <netdb.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "../config.h"
#include <libsherpa/os.hxx>

#if !(defined(__unix__) || defined(MAC_OS_X))
#error "This source file provides UNIX-specific support."
#endif

#include <sys/time.h>

/* IRIX needs statvfs.h to call statvfs

   On Solaris, we get away with including vfs.h, but the 2.6 statvfs manpage
   shows that statvfs.h is the proper include to use.

   OpenCM hasn't been tested on any other SVR4 variants yet.
      - JL (July 18, 2002)
*/
#ifdef HAVE_SVR4_STATVFS
#include <sys/types.h>
#include <sys/statvfs.h>
#endif

#ifdef HAVE_SYS_STATFS_H
#include <sys/statfs.h>
#endif

#ifdef HAVE_SYS_VFS_H
#include <sys/vfs.h>
#endif

#ifdef HAVE_SYS_PARAM_H
#include <sys/param.h>
#endif

#ifdef HAVE_SYS_MOUNT_H
#include <sys/mount.h>
#endif

#ifdef __linux__
#define NFS_SUPER_MAGIC  0x6969
#endif /* __linux__ */

#include <pwd.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>

#include <string>

#include <libsherpa/UExcept.hxx>
#include <libsherpa/format.hxx>
#include <libsherpa/os.hxx>

namespace sherpa {
  namespace os {
    /*
      Return the service port, if available, in HOST byte order (this
      is how the opencmport variable is stored). If we don't know what
      the port number is, return 0, which is reserved by IANA, so it
      couldn't possibly be a port number for us to use.
    */
    int
    GetServicePort(const char *name, const char *proto)
    {
      struct servent* service = getservbyname(name, proto);
      if(service)
	return htons(service->s_port);
      else
	return 0;
    }
  } /* namespace os */
} /* namespace sherpa */
