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

#include <stdio.h>
#include <dirent.h>

#include <string>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/convenience.hpp>
#include <boost/filesystem/path.hpp>

#include <libsherpa/xfopen.hxx>

using namespace boost;

namespace sherpa {
  std::string
  ReadOneLineFile(const boost::filesystem::path& path)
  {
    uintmax_t len = filesystem::file_size(path);
    FILE *f = xfopen(path, 'r', 't');
    std::string buf;

    buf.resize(len);

    /* Length may get truncated if this is a WIN32 text file */
    len = fread(const_cast<char *>(buf.data()), 1, len, f);

    while (buf.length() && 
	   (buf[buf.length()-1] == '\n' || buf[buf.length()-1] == '\r'))
      buf.erase(buf.begin() + buf.length() - 1, buf.end());

    xfclose(f);

    return buf;
  }

  int
  WriteOneLineFile(const filesystem::path& path, 
		   const std::string& s)
  {
    int result;
    FILE *f = xfopen(path, 'c', 't');

    result = fprintf(f, "%s\n", s.c_str());

    xfclose(f);

    return result;
  }

} /* namespace sherpa */
