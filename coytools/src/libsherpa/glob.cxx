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

#include <dirent.h>

#include <string>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/convenience.hpp>

#include <libsherpa/glob.hxx>

using namespace boost;

/* Shell-style glob processing for client and server */
namespace sherpa {

  static inline bool
  isDirSep(char c) {
    return c == '/';
  }

  static bool
  goodglob(const char *s)
  {
    int nsquare = 0;
  
    for (; *s; s++) {
      switch (*s) {
      case '[':
	nsquare++;
	break;
      case ']':
	nsquare--;
	break;
      case '\\':
	if (s[1] == 0)
	  return false;
	s++;			/* skip escaped character */
	break;
      }
    }

    return (nsquare == 0);
  }

  static bool
  proper_charset(const char *s)
  {
    while (*s && *s != ']') {
      if (*s == '\\')
	s++;

      if (*s == '-' && s[1] == ']')
	return false;

      s++;
    }

    return true;
  }

  static const char *
  skip_charset(const char *s)
  {
    while (*s && *s != ']') {
      if (*s == '\\')
	s++;
      s++;
    }

    return ++s;
  }

#define get_next(s) ((*s == '\\' ? s++ : s) , *s++)

  static int
  glob_charset_match(char match_c, const char * set)
  {
    int charset[256];
    int i;
    int isfirst = 1;
    int invert = 0;
    char last = 'a';

    for (i = 0; i < 256; i++)
      charset[i] = 0;

    if (!proper_charset(set))
      return 0;

    set++;			/* skip leading '[' */
  
    for (;;) {
      int c = *set++;
    
      if (c == ']')		/* end of charset */
	break;
    
      if (c == '\\')
	c = *set++;
    
      switch (c) {
      case '-':
	{
	  if (isfirst)
	    invert = 1;
	  else {
	    int ndx;
	    c = *set++;
	    if (c == '\\')
	      c = *set++;
	
	    for (ndx = last; ndx <= c; ndx++)
	      charset[ndx] = 1;	  
	  }
	  break;
	}
      default:
	{
	  charset[c] = 1;
	  break;
	}
      }

      last = c;

      isfirst = 0;
    }

    if (invert) {
      int ndx;
      for (ndx = 0; ndx < 256; ndx++)
	charset[ndx] = !charset[ndx];
    }

    return charset[(unsigned)match_c];
  }

#define ismeta(c) ((c) == '?' || (c) == '*' || (c) == '[')
  static const char *
  do_glob_match(const char *s, const char *pattern, unsigned flags)
  {
  loop:
    for ( ; !ismeta(*pattern) ; s++, pattern++) {
      if (*pattern == '\\')
	pattern ++;
    
      /* Special check if it is sufficient to match a component of a
	 potentially longer path: */
      if ((flags & GM_FS_COMPONENT) &&
	  *pattern == 0 &&
	  isDirSep(*s))
	return s+1;		/* NOTE: skip the dir separator */

      if (*s != *pattern)
	return 0;

      if (*s == 0)
	return s;			/* valid ptr to trailing null -> success */
    }

    /* Doing metacharacter processing */
    if (*pattern == '?' && *s) {
      pattern ++;
      s ++;
      goto loop;
    }
    else if (*pattern == '*') {
      /* If matching FS component, * does not cross / in the
	 string. Otherwise, try both strategies for advancing. */

      if ((flags & GM_FS_COMPONENT) && isDirSep(*s)) {
	/* If this is the end of the pattern, then this is a successful
	   match: */
	if (pattern[1] == 0)
	  return s + 1;		/* NOTE: skip the dir separator */

	else if (isDirSep(pattern[1]))
	  return do_glob_match(s, pattern+1, flags);

	else
	  return do_glob_match(s+1, pattern+1, flags);
      }
      else {
	const char *rest;

	if ((rest = do_glob_match(s, pattern + 1, flags)) ||
	    (*s && (rest = do_glob_match(s + 1, pattern, flags))))
	  return rest;
	else
	  return 0;
      }
    }
    else if (*pattern == '[') {
      const char *pat_rest = skip_charset(pattern);

      if (!glob_charset_match(*s, pattern))
	return 0;

      pattern = pat_rest;
      s++;
      goto loop;
    }
  
    return 0;
  }

  std::string
  glob_match(const std::string s, const std::string pattern, unsigned flags)
  {
    if (!goodglob(pattern.c_str()))
      return 0;

    /* Initial '.' is not matched by wildcard. Check that case here. */
    if (s[0] == '.' && pattern[0] != '.')
      return 0;
  
    return do_glob_match(s.c_str(), pattern.c_str(), flags);
  }

  bool
  glob_isglob(std::string str)
  {
    const char *s = str.c_str();
    while (*s) {
      switch (*s) {
      case '[':
      case ']':
      case '*':
      case '?':
      case '\\':
      case '.':			/* not sure this needs to be here */
	return true;
      default:
	break;
      }
      s++;
    }

    return false;
  }

} /* namespace sherpa */
