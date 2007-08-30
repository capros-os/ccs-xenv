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

#include <syslog.h>
#include <stdarg.h>
#include <stdint.h>
#include <dirent.h>

#include <string>

#include "UExcept.hxx"
#include "util.hxx"
#include "Logging.hxx"
#include "os.hxx"
#include "xfopen.hxx"
#include "avl.hxx"

namespace sherpa {
  std::string appName = "Who Am I?";
  std::string appInvokedName = "Who Am I?";

  namespace logger {
    typedef AvlMapNode<std::string,LogType*> LogMapNode;
    static AvlMap<std::string,LogType*> logMap;

    /* Forward declaration: */
    static void do_log(FILE *chan, const char *prefix, 
		       const char *fmt, va_list args);

    void LogType::do_init(const std::string& s, TraceType tt, unsigned lvl)
    {
      name = s;
      traceType = tt;
      level = lvl;
      shouldTrace = false;

      if (logMap.contains(name)) {
	syslog_error("Duplicate LogType %s\n", (char *) s.c_str());
	exit(-1);
      }    
    
      logMap.insert(name, this);
    }

#define LOG_TIME_STAMPS

    int server_mode;		/* are we running server or client? */

    /* Until proven otherwise, all of the logging output goes to standard
       error: */
    FILE *trace_channel = 0;
    FILE *error_channel = 0;
    FILE *access_channel = 0;

    unsigned long long log_counter = 0;

    /* these versions of the functions do not allocate memory, which is important
       if we want to be able to log malloc()s. */
    extern char *unsigned64_to_string(uint64_t ul, char *buf);
    extern void os_GetISOTime_s(char *buf);

    static void
    do_log(FILE *chan, const char *prefix, const char *fmt, va_list args)
    {
      /* max of (19 for digits + 1 for null << unsigned64_to_string)
	 and (49 + 1 for null from os_GetISOTime_s) */
#define BUFSZ 50

      std::string logCounterString = unsigned64_str(log_counter);

      log_counter++;

#ifdef LOG_TIME_STAMPS
      if (server_mode) {
	std::string theTime = os::GetISOTime();
	fprintf(chan, "%s ", theTime.c_str());
      }
#endif

      if (server_mode)
	fprintf(chan, "%s %s %s:", appName.c_str(),
		logCounterString.c_str(), prefix);
      else
	fprintf(chan, "%s %s: ", appName.c_str(), prefix);


      vfprintf(chan, fmt, args);
      fflush(chan);
    }

    void
    vtrace(LogType& key, const char *fmt, va_list args)
    {
      FILE *chan;

      if (trace_channel == 0)
	trace_channel = stderr;
      if (error_channel == 0)
	error_channel = stderr;

      if (key.traceType == LTY_trace)
	chan = trace_channel;
      else
	chan = error_channel;

      if (key.shouldTrace)
	do_log(chan, "TRC", fmt, args);
    }

    void
    trace(LogType& key, const char *fmt, ...)
    {
      va_list	args;
      va_start(args, fmt);

      if (trace_channel == 0)
	trace_channel = stderr;
      if (error_channel == 0)
	error_channel = stderr;

      if (key.shouldTrace)
	do_log(trace_channel, "TRC", fmt, args);

      va_end(args);
    }

#define MAX_ERROR 1024

    static void
    vsyslog_error(const char *fmt, va_list args)
    {
      if(server_mode) {
	char buf[MAX_ERROR];
	vsnprintf(buf, MAX_ERROR-1, fmt, args);
	buf[MAX_ERROR-1]=0;

	syslog(LOG_INFO, "%s", buf);
      }
    } 

    void
    syslog_error(const char *fmt, ...)
    {
      va_list   args;

      va_start(args, fmt);

      if (error_channel == 0)
	error_channel = stderr;

      do_log(error_channel, "ERR", fmt, args);

      vsyslog_error(fmt, args);

      va_end(args);
    } 

    void
    initDirectory(Path logDir)
    {
      Path err_logFile = logDir + Path("error_log");
      Path acc_logFile = logDir + Path("access_log");
      Path trc_logFile = logDir + Path("trace_log");

      FILE *f;

      if ((f = xfopen(err_logFile, 'w', 't')) != NULL)
	error_channel = f;

      if ((f = xfopen(acc_logFile, 'w', 't')) != NULL)
	access_channel = f;

      if ((f = xfopen(trc_logFile, 'w', 't')) != NULL)
	trace_channel = f;
    }


    static bool setVerbosityIterator(GCPtr<LogMapNode> nd,
				     const void *vlevel)
    {
      long level = * ((long *)vlevel);

      LogType *lt = nd->value;

      if (lt->level != DebuggingTraceLevel)
	lt->shouldTrace = (level > lt->level);

      return true;
    }

    void
    setVerbosity(unsigned long level)
    {
      logMap.iterate(setVerbosityIterator, &level);
    }

#if 0
    static bool setDebuggingIterator(LogMapNode *nd,
				     const void *vname)
    {
      const char *name = (const char *) vname;

      LogType *lt = nd->value;

      if (lt->level == DebuggingTraceLevel) {
	if (strcasecmp(name, lt->name.c_str()) == 0)
	  lt->shouldTrace = true;
      }

      return true;
    }
#endif

    void
    setDebugging(const std::string& arg)
    {
      GCPtr<LogMapNode> nd = logMap.lookup(arg);

      if (!nd)
	THROW(excpt::BadValue, "Argument to -d was unrecognized");

      nd->value->shouldTrace = true;
    }

    bool
    helpDebuggingIterator(LogMapNode *nd, const void *aux)
    {
      LogType *lt = nd->value;

      if (lt->level == DebuggingTraceLevel)
	fprintf(stderr, "%s\n", strdowncase(lt->name).c_str());

      return true;
    }

    void
    helpDebugging(void)
    {
      fprintf(stderr, "The following debugging flags are available:\n");

      logMap.iterate(setVerbosityIterator);
    }

    bool
    shouldLog(LogType& key)
    {
      return key.shouldTrace;
    }

#ifdef NOCONVERT
    void
    access(const char *fmt, ...)
    {
      va_list	args;
      va_start(args, fmt);

      if (access_channel == 0)
	access_channel = stderr;

      do_log(access_channel, "ACC", fmt, args);

      va_end(args);
    }

    void
    unimplemented(const char *s)
    {
      trace(ERR_UNIMPL, s);
      exit(1);
    }
#endif
  } /* namespace logger */
} /* namespace sherpa */
