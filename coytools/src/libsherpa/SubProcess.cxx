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

#include <sys/wait.h>
#include <dirent.h>
#include <fcntl.h>
#include <errno.h>
#include <stdint.h>

#include <string>
#include <vector>

#include <boost/filesystem/operations.hpp>

#include <libsherpa/UExcept.hxx>
#include <libsherpa/SubProcess.hxx>
#include <libsherpa/Logging.hxx>
#include <libsherpa/os.hxx>

using namespace boost;

namespace sherpa {
  logger::LogType DbgSubProcess("SUBPROCESS", logger::LTY_trace);

#if defined(__unix__) || defined(MAC_OS_X)
  int
  SubProcess::run(const char *input, const char *output, const char *errput,
		  unsigned flags)
  {
    pid_t pid;
    int fin = 0, fout = 1, ferr = 2;

    logger::trace(DbgSubProcess, "Curdir is %s\n", 
		  filesystem::current_path().string().c_str());

    size_t narg = argv.size();

    try{
      /* Set up the requested input/output channels: */
      if (input) {
	fin = open(input, O_RDONLY);
	if (fin < 0)
	  THROW(excpt::Subprocess, 
		format("Unable to redirect command input from: %s", input));
      }
  
      if (output) {
	fout = open(output, O_WRONLY | O_CREAT, 0666);
	if (fout < 0)
	  THROW(excpt::Subprocess, 
		format("Unable to redirect command output to %s", output));
      }
  
      if (errput) {
	ferr = open(errput, O_WRONLY);
	if (fout < 0)
	  THROW(excpt::Subprocess, 
		format("Unable to redirect command errors to %s", errput));
      }
    }
    catch(...) {
      if (fin > 0)
	close(fin);
      if (fout > 0)
	close(fout);
      if (ferr > 0)
	close(ferr);

      throw;
    }


    char **real_argv = new char *[narg+1];

    for (size_t i = 0; i < narg; i++)
      real_argv[i] = const_cast<char *> (argv[i].c_str());

    real_argv[narg] = 0;

    {
      for (size_t i = 0; i < narg; i++)
	logger::trace(DbgSubProcess, "arg %d: %s\n", i, real_argv[i]);
    }

    /* Below this point all file descriptors are known valid. */

    pid = fork();

    if (pid == 0) {
      /* This is the child */

      if (fin != 0) {
	dup2(fin, 0);
	close(fin);
      }

      if (fout != 1) {
	dup2(fout, 1);
	close(fout);
      }

      if (ferr != 2) {
	dup2(ferr, 2);
	close(ferr);
      }

      if (flags & SPF_DISCONNECT)
	os::background();

      /* Operating descriptors are set up. Now exec the requested
	 command. */

      (void) execvp (real_argv[0], real_argv);
      logger::syslog_error("Cannot exec %s\n", real_argv[0]);
      _exit (127);
    }
    else {
      /* parent */
      int status;
      pid_t w;

      if (fin != 0)
	close(fin);
      if (fout != 1)
	close(fout);
      if (ferr != 2)
	close(ferr);
    
      delete [] real_argv;

      if (flags & SPF_DISCONNECT)
	return 0;

      for (;;) {
	w = waitpid(pid, &status, 0);
      
	if (w == -1 && errno != EINTR) {
	  logger::trace(DbgSubProcess, "Return status: %d errno %d\n", status, errno);
	  THROW(excpt::Subprocess, 
		format("Wait on child (pid=%d) failed", pid));
	}

	if (w == pid) {
	  if(!WIFEXITED(status)) /* child exited abnormally */
	    THROW(excpt::Subprocess, "Child process exited abnormally");
	  if(WIFSIGNALED(status))
	    THROW(excpt::Subprocess,
		  format("Child process died due to signal %d", WTERMSIG(status)));
	  logger::trace(DbgSubProcess, 
			"Return pid %d, status %d, errno %d\n", w, status, errno);
	  return WEXITSTATUS(status);
	}
      }
    }
  }
#endif

} /* namespace sherpa */
