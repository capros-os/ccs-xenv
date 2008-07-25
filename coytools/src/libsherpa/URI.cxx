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
#include <string.h>
#include <stdlib.h>

#include <string>

#include <libsherpa/UExcept.hxx>
#include <libsherpa/URI.hxx>

#define PARENT_DIR  1
#define SAME_DIR    2
#define SKIP_SCHEMA 3

#define FTP_PORT 21
#define HTTP_PORT 80
#define HTTPS_PORT 443
#define OPENCM_PORT 3434

#define DEFAULT_PORT OPENCM_PORT

#define USER_ANONYMOUS  "anonymous"
#define DEFAULT_HOST    "localhost"

/* Recognized schemes */
#define SCHEME_FILE   "file"
#define SCHEME_OPENCM "opencm"
#define SCHEME_HTTP   "http"
#define SCHEME_HTTPS  "https"
#define SCHEME_FTP    "ftp"

using namespace boost;

namespace sherpa {
  static filesystem::path
  canonical_path(const filesystem::path& p)
  {
    /// @bug This is a placeholder implementation for what used to be
    /// Path(theRest).canonical(), which has no analogous operation in
    /// the boost library.
    return p;
  }

  void
  URI::GuessPort()
  {
    port = 0;

    if (scheme.empty())
      port = DEFAULT_PORT;
    else if (scheme == "http")
      port = HTTP_PORT;
    else if (scheme == "https")
      port = HTTPS_PORT;
    else if (scheme == "ftp")
      port = FTP_PORT;
    else if (scheme == "opencm")
      port = OPENCM_PORT;
  }

  void
  URI::validateScheme()
  {
    if ((scheme != SCHEME_FILE) && (scheme != SCHEME_OPENCM))
      THROW(excpt::NoObject, 
	    format("Unsupported scheme for uri: \"%s\".", scheme.c_str()));
  }

  /* Regenerate what the "URI" field is supposed to store.
     Occasionally, we need to trim excess subdirs off the path part.  Thus,
     this routine is convenient for regenerating the stringified format. */
  std::string
  URI::toString()
  {
    std::string outURI = scheme + "://";

    outURI += user + "@";

    outURI += netloc;

    /* Only include the port for non-local schemes */
    if (scheme != SCHEME_FILE)
      outURI += format(":%d", port);

    outURI += path.string();

    return outURI;
  }

  bool
  URI::validScheme(std::string s)
  {
    /* Check for all well-known schemes.  We can't just check for the
       presence of "://" because we want to support embedded URIs and we
       could have a relative URI that has an embedded absolute URI... */
    if ((s == SCHEME_FILE) ||
	(s == SCHEME_OPENCM) ||
	(s == SCHEME_HTTP) ||
	(s == SCHEME_HTTPS) ||
	(s == SCHEME_FTP))
      return true;
    return false;
  }

  URI::URI(std::string str)
    : path("/")
  {
    wellFormed = false;		// until proven otherwise
    relative = true;		// until proven otherwise

    user = USER_ANONYMOUS;	// until proven otherwise
    netloc = DEFAULT_HOST;	// until proven otherwise

    GuessPort();

    size_t colon = str.find(':');
    std::string theScheme = str.substr(0, colon);
    std::string theRest = str.substr(colon+1);

    /* A colon is valid in a file name, which presents us with a 
     * recognition challenge. If we do not have a colon, or if the
     * first colon does not appear at the end of a recognized scheme,
     * we assume that this is a relative URI. We also check if the colon 
     * is followed by a slash, which it should be:
     */

    if (colon == std::string::npos || // no colon
	validScheme(theScheme) == false || // invalid scheme
	theRest[0] != '/') {	// colon not followed by '/'
      path = canonical_path(theRest);
      scheme = SCHEME_FILE;
      wellFormed = true;	
      uriString = toString();
      relative = !path.is_complete();
      return;
    }

    /* Until proven otherwise */
    path = theRest;
    scheme = theScheme;
    wellFormed = true;

    /* Skip the "//", if any.
     * If there isn't a "//" then rest of URI is considered path!
     */

    if (theRest.length() > 1 && theRest[0] == '/' && theRest[1] == '/') {
      str = theRest.substr(2);

      /* This is a full-format URI. Need to check for explicit user, host 
	 and port number. First split off the path part: */

      size_t pathPos = str.find('/');
      path = str.substr(pathPos+1);
      str = str.substr(0, pathPos);

      /* str now holds user@host:port part only */
      size_t atPos = str.find('@');
      if (atPos != std::string::npos) {
	user = str.substr(0, atPos);
	str = str.substr(atPos + 1);
      }

      size_t colonPos = str.find(':');
      if (colonPos == std::string::npos) {
	netloc = str;
      }
      else {
	netloc = str.substr(0, colonPos);
	std::string thePort = str.substr(colonPos+1);
	port = strtoul(thePort.c_str(), 0, 0);
      }
    }

#if 0
    debug(DBG_URI, 
	  "\nScheme: %s\nPort: %d\nNetloc: %s\nUsername: %s\nPath: %s\n", 
	  uri->scheme, uri->port, uri->netloc, uri->username, uri->path);
#endif 
  
    path = canonical_path(path);

    if (path.is_complete())
      relative = false;

    /* When all done, restore the entire URI for future use:*/
    uriString = toString();
  }

  bool
  URI::isAbsolute(std::string uri)
  {
    /* Check for all well-known schemes.  We can't just check for the
       presence of "://" because we want to support embedded URIs and we
       could have a relative URI that has an embedded absolute URI... */
    if (uri.find(std::string(SCHEME_FILE) + "://") == 0)
      return true;
    if (uri.find(std::string(SCHEME_OPENCM) + "://") == 0)
      return true;
    if (uri.find(std::string(SCHEME_HTTP) + "://") == 0)
      return true;
    if (uri.find(std::string(SCHEME_HTTPS) + "://") == 0)
      return true;
    if (uri.find(std::string(SCHEME_FTP) + "://") == 0)
      return true;

    return false;
  }

} /* namespace sherpa */
