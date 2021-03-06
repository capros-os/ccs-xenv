/**************************************************************************
 *
 * Copyright (C) 2008, The EROS Group, LLC. 
 * Copyright (C) 2006, Johns Hopkins University.
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

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

#include <string>

#include <libsherpa/Logging.hxx>
#include <libsherpa/Report.hxx>

namespace sherpa {
  void
  usage(const char *fmt, ...)
  {
    if (fmt) {
      va_list	args;
      va_start(args, fmt);

      vfprintf(stderr, fmt, args);
  
      va_end(args);
    }
  
    exit(1);
  }

  static logger::LogType* traceKey = 0;

  void 
  report_to_tracelog(logger::LogType& argTraceKey)
  {
    traceKey = &argTraceKey;
  }

  void
  report(unsigned lvl, const char *fmt, ...)
  {
    va_list	args;
    va_start(args, fmt);

    if (verbosity_lvl >= lvl) {
      if (!traceKey) {
	/*    fprintf(stdout, "%s: ", appName); */
	vfprintf(stdout, fmt, args);
	fflush(stdout);
      }
      else {
	logger::vtrace(*traceKey, fmt, args);
      }
    }
  
    va_end(args);
  }

} /* namespace sherpa */
