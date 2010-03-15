#ifndef LIBSHERPA_LOGGING_HXX
#define LIBSHERPA_LOGGING_HXX

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

#include <stdarg.h>
#include <boost/filesystem/path.hpp>

namespace sherpa {
  extern std::string appName;
  extern std::string appInvokedName;

  namespace logger {
    enum {
      DebuggingTraceLevel = 255u
    };

    enum TraceType {
      LTY_trace,
      LTY_error
    };

    struct LogType {
      TraceType traceType;
      unsigned char level;
      std::string name;
      bool shouldTrace;

    private:
      void do_init(const std::string& s, TraceType tt, unsigned level);

    public:
      inline LogType(const std::string& s, TraceType tt, unsigned level)
      {
	do_init(s, tt, level);
      }
      inline LogType(const std::string& s, TraceType tt)
      {
	do_init(s, tt, DebuggingTraceLevel);
      }
    };

    void helpDebugging(void);
    bool shouldLog(LogType* key);

    void vtrace(LogType& key, const char *msg, va_list args);
    void trace(LogType& key, const char *msg, ...);
    void syslog_error(const char *msg, ...);

    void setVerbosity(unsigned long verbosity);
    void setDebugging(const std::string& arg);
    void setServerMode();

    void initDirectory(const boost::filesystem::path& logDir);
  } /* namespace logging */
} /* namespace sherpa */

#endif /* LIBSHERPA_LOGGING_HXX */
