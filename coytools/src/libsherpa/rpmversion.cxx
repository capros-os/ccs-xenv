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
#include <dirent.h>

#include <string>

#include "rpmversion.hxx"
#include "util.hxx"
#include "Logging.hxx"

namespace sherpa {
  /* The RPM version comparison logic is black magic, and ours may not
     correspond exactly -- I haven't looked at the RPM code.
   
     What ours does is view the version strings as sequences of the form

     AAAxNNNxBBBxMMM

     where 'A', 'B' indicates alphabetic characters, 'N', 'M' indicates numeric
     characters, and 'x' indicates (possibly absent) don't cares. What
     the version comparitor does is segment the strings into things of
     like type and then compare them. Thus,

     opencm-0.1.0-alpha1

     segments as "opencm" "0" "1" "0" "alpha" "1".

     Note that the segmentation strategy gives

     1  =>  "" "1"
     x10 => "x" "10"

     and that therefore 1 < x10 in this comparison routine.

     If both segments at a given comparison point are numeric, the
     comparison is done numerically. Otherwise, the comparison is done
     lexically.

     WARNING: This strategy may change as I learn more about how RPM
     does things. In particular, there appear to be some cases where RPM
     compares numbers lexically.
  */

  logger::LogType DbgRpmVersion("RPMVERSION", logger::LTY_trace);

  static const char *
  stralpha(const char *s)
  {
    while (isalpha(*s))
      s++;

    return s;
  }

  static int
  strfragcmp(const char *s1, size_t l1, const char *s2, size_t l2)
  {
    size_t minlen = std::min(l1, l2);
    int result = 0;

    if (minlen && ((result = strncmp(s1, s2, minlen)) != 0))
      return result;

    /* The strncmp() could not decide. Shorter string wins. */
    if (l1 < l2)
      return -1;
    if (l1 > l2)
      return 1;
    return 0;
  }

  int
  compare_rpm_versions(std::string s1, std::string s2)
  {
    const char *v1 = s1.c_str();
    const char *v2 = s2.c_str();

    int result = 0;

    while (result == 0 && (*v1 || *v2)) {
      char *v1_end;
      char *v2_end;
      unsigned u1, u2;

      /* Skip leading junk */
      while (*v1 && !isalnum(*v1))
	v1++;
      while (*v2 && !isalnum(*v2))
	v2++;

      if (*v1 && *v2 == 0)
	return 1;
      if (*v1 == 0 && *v2)
	return -1;

      /* Assume optimistically that both segments are digits, and try to
	 convert them: */
      u1 = strtoul(v1, &v1_end, 0);
      u2 = strtoul(v2, &v2_end, 0);

      if (v1_end != v1 && v2_end != v2) {
	std::string v1frag(v1, v1_end - v1);
	std::string v2frag(v2, v2_end - v2);
	logger::trace(DbgRpmVersion, "Compare %s to %s numerically\n", 
		      v1frag.c_str(),
		      v2frag.c_str());

	if (u1 < u2)
	  result = -1;
	else if (u1 > u2)
	  result = 1;
      }
      else {
	v1_end = (char *) stralpha(v1);
	v2_end = (char *) stralpha(v2);

	std::string v1frag(v1, v1_end - v1);
	std::string v2frag(v2, v2_end - v2);

	logger::trace(DbgRpmVersion, "Compare %s to %s lexically\n", 
		      v1frag.c_str(),
		      v2frag.c_str());

	result = strfragcmp(v1, v1_end - v1, v2, v2_end - v2);
      }

      v1 = v1_end;
      v2 = v2_end;
    }

    return result;
  }

} /* namespace sherpa */
