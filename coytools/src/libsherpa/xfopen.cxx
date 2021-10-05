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

#include <stdint.h>
#include <dirent.h>
#include <stdio.h>
#include <errno.h>

#include <string>

#include <boost/version.hpp>

#include <libsherpa/UExcept.hxx>
#include <libsherpa/Logging.hxx>
#include <libsherpa/util.hxx>

using namespace boost;

namespace sherpa {

  static int nOpenFile = 0;
  logger::LogType DbgFdLeak("FDLEAK", logger::LTY_trace);

  FILE *
  do_xfopen(const filesystem::path& path, const char mode, const char ftype, 
	    const char *file, unsigned line)
  {
    const char *fopen_mode;
    FILE *f;

    if (mode == 'r' && ftype == 't')
      fopen_mode = "rt";
    else if (mode == 'r' && ftype == 'b')
      fopen_mode = "rb";
    else if (mode == 'w' && ftype == 't')
      fopen_mode = "wt";
    else if (mode == 'w' && ftype == 'b')
      fopen_mode = "wb";
    else if (mode == 'c' && ftype == 't')
      fopen_mode = "wt+";
    else if (mode == 'c' && ftype == 'b')
      fopen_mode = "wb+";
    else
      THROW(excpt::BadValue, "Unknown mode or ftype to xfopen");

    f = fopen(path.string().c_str(), fopen_mode);
    if (f == NULL)
      THROW(excpt::NoAccess,
	    format("Could not open file %s, mode %s (errno %d)", 
		   path.string().c_str(), fopen_mode, errno));

    nOpenFile++;
    logger::trace(DbgFdLeak, "%d files now open at %s:%d\n", 
		  nOpenFile, file, line);

    return f;
  }

  void
  do_xfclose(FILE *f, const char *file, unsigned line)
  {
    int retval; 

    if (f != NULL)
      {
	retval = fclose(f);
	if(retval) /* shame we can't get the filename here... */
	  THROW(excpt::Truncated, format("Closing file failed, error %d\n", retval));

	nOpenFile--;
	logger::trace(DbgFdLeak, "%d files now open at %s:%d\n", 
		      nOpenFile, file, line);
      }
  }

} /* namespace sherpa */
