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
#include <stdlib.h>
#include <string.h>

#include "../config.h"
#include "os.hxx"

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

#include "UExcept.hxx"
#include "format.hxx"
#include "os.hxx"

namespace sherpa {
  namespace os {
    std::string
    GetUserName()
    {
      struct passwd *pw;

      uid_t uid = getuid();
      pw = getpwuid(uid);

      if (strlen(pw->pw_gecos) != 0)
	return std::string(pw->pw_gecos);
      else
	return std::string(pw->pw_name) + "@" + GetHostName();
    }

    std::string
    GetHostName()
    {
      char hostbuf[1024];
      gethostname(hostbuf, 1024);

      return std::string(hostbuf);
    }

    std::string
    GetHomeDirAsString()
    {
      return std::string(getenv("HOME"));
    }

    /* Returns GMT time! */
    std::string
    ToDiffTime(time_t local_secs)
    {
      char time_string[40];
      size_t len = 40;
      struct tm *tm_utc;
      tm_utc = localtime(&local_secs);

      len = strftime(time_string, len, "%Y-%m-%d %H:%M:%S.000000000 %z", tm_utc);
      return std::string(time_string);
    }

    /* Returns GMT time! */
    std::string
    ToISO(time_t local_secs)
    {
      char time_string[40];
      size_t len = 40;
      struct tm *tm_utc;
      tm_utc = gmtime(&local_secs);

      len = strftime(time_string, len, "%Y-%m-%dT%H:%M:%S", tm_utc);
      return std::string(time_string) + "GMT";
    }

    time_t
    FromISO(std::string isoTime)
    {
      struct tm tm;
      struct tm local_tm;
      struct tm gmt_tm;
      time_t now_local_secs;

      memset(&tm, 0, sizeof(tm));
      memset(&local_tm, 0, sizeof(local_tm));
      memset(&gmt_tm, 0, sizeof(gmt_tm));

      /* Get a representation of "now" in local timezone */
      now_local_secs = time(0);
      localtime_r(&now_local_secs, &local_tm);
      gmtime_r(&now_local_secs, &gmt_tm);

      {
	const char *isoPos = isoTime.c_str();

	/* Grab off the year */
	while (isdigit(*isoPos)) {
	  tm.tm_year *= 10;
	  tm.tm_year += (*isoPos - '0');

	  isoPos++;
	}

	isoPos++;           /* skip the '-' */

	/* Grab off the month */
	while (isdigit(*isoPos)) {
	  tm.tm_mon *= 10;
	  tm.tm_mon += (*isoPos - '0');

	  isoPos++;
	}

	isoPos++;           /* skip the '-' */

	/* Grab off the day */
	while (isdigit(*isoPos)) {
	  tm.tm_mday *= 10;
	  tm.tm_mday += (*isoPos - '0');

	  isoPos++;
	}

	isoPos++;           /* skip the 'T' */

	/* Grab off the hour */
	while (isdigit(*isoPos)) {
	  tm.tm_hour *= 10;
	  tm.tm_hour += (*isoPos - '0');

	  isoPos++;
	}

	isoPos++;           /* skip the ':' */

	/* Grab off the minute */
	while (isdigit(*isoPos)) {
	  tm.tm_min *= 10;
	  tm.tm_min += (*isoPos - '0');

	  isoPos++;
	}

	isoPos++;           /* skip the ':' */

	/* Grab off the second */
	while (isdigit(*isoPos)) {
	  tm.tm_sec *= 10;
	  tm.tm_sec += (*isoPos - '0');

	  isoPos++;
	}

	/* There should not be fractional seconds (yet): */
	if (*isoPos == '.')
	  THROW(excpt::BadValue,
		"Cannot handle fractional seconds in modtimes (yet)");

	/* Skip fractional component, if any */
	while (isdigit(*isoPos) || *isoPos == '.' || isspace(*isoPos))
	  isoPos++;

	if (strcmp(isoPos, "GMT") != 0)
	  THROW(excpt::BadValue, 
		format("Don't know how to decode non-GMT iso time \"%s\"\n",
		       isoPos));
      }

      /* mktime() demands a struct tm that is expressed in *local* time. 
	 While BSD systems have added a GMT offset field to struct TM, the
	 mktime() implementation is unable to use this for reasons of
	 compatibility. We therefore take the above-constructed struct tm
	 whose values reflect GMT and apply the deltas derived from a
	 comparison of the current time expressed locally and as GMT. */

      tm.tm_year -= 1900;      /* UNIX time baseline */
      tm.tm_mon -= 1;      /* Jan is month zero */

      /* now apply the bias between local time and gmtime to all of the
	 fields that are used by mktime (what a nuisance!) */
      tm.tm_year += (local_tm.tm_year - gmt_tm.tm_year);
      tm.tm_mon  += (local_tm.tm_mon - gmt_tm.tm_mon);
      tm.tm_mday += (local_tm.tm_mday - gmt_tm.tm_mday);
      tm.tm_hour += (local_tm.tm_hour - gmt_tm.tm_hour);
      tm.tm_min  += (local_tm.tm_min - gmt_tm.tm_min);
      tm.tm_sec  += (local_tm.tm_sec - gmt_tm.tm_sec);

      /* Pick up the DST flag from local time, which may be wrong if the
	 user mis-set the timezone, but it is wrong in a way that is
	 consistent with what the behavior of mktime() will be: */
      tm.tm_isdst = local_tm.tm_isdst;

      return mktime(&tm);
    }

    static void
    GetISOTime_s(char *buf)
    {
      struct timeval tv;
      time_t now_secs;
      struct tm *tm_now;

      size_t len = 40;

      /* This is mildly tricky, because we need the microseconds component
	 to deliver a decently accurate time string. Use gettimeofday(2),
	 copy the seconds component over to a time_t value that can be
	 passed to strftime(), and then mangle the resulting string to
	 patch in the decimal seconds fraction per ISO-8601. */

      gettimeofday(&tv, 0);
      now_secs = tv.tv_sec;
      tm_now = gmtime(&now_secs);

      len = 1 + strftime(buf, len, "%Y-%m-%dT%H:%M:%S.", tm_now);
      sprintf(buf + len, "%06luGMT", tv.tv_usec);
    }

    std::string
    GetISOTime(void)
    {
      char buf[40 + 6 + 3 + 1]; /* strftime(,40,,) + "%06lu" + "GMT" + '\0' */
      GetISOTime_s(buf);
      buf[49] = '\0';
      return std::string(buf);
    }

    uint32_t
    GetPid(void)
    {
      pid_t mypid = getpid();
      return mypid;
    }

    static bool
    try_create_local_lockfile(std::string path)
    {
      bool result = false;
      int fd;
      uint32_t mypid = GetPid();
      std::string tmpPath = format("%s.%d", path.c_str(), mypid);
      std::string contents = format("%d\n", mypid);

      fd = ::creat(tmpPath.c_str(), 0666);
      if (fd < 0)
	THROW(excpt::NoObject,
	      format("Could not create temporary file %s for locking (errno %d)", path.c_str(), errno));
  
      if (::write(fd, contents.c_str(), 
		  contents.length()) != (ssize_t) contents.length()) {
	::unlink(tmpPath.c_str());
	THROW(excpt::IoError,
	      format("Could not create temporary file %s for "
		     "locking (errno %d)", path.c_str(), errno));
      }

      ::close(fd);

      if (::link(tmpPath.c_str(), path.c_str()) >= 0)
	result = true;

      ::unlink(tmpPath.c_str());

      return result;
    }

    bool
    os_pid_exists(uint32_t pid)
    {
      /* Send sig==0, which will check to see if the process exists, but no actual signal
	 will be sent to the process */
      int result = kill(pid, 0); /* error check, no real signal */
      if (result < 0 && errno == ESRCH)
	return false;
      return true;
    }

    bool
    validate_local_lockfile(std::string path)
    {
      struct stat statbuf;
      int lfd;

      /* Check if the process allegedly holding the lock file still
	 exists. It may have died leaving an orphaned lock file. Note
	 that we may be running this algorithm in parallel with other
	 applications, so the low-level system calls may fail. This is
	 perfectly okay, as it means that the lock file has been nuked
	 by the other process. */

      if (::stat(path.c_str(), &statbuf) < 0) {
	if (errno == ENOENT)
	  return true;		/* make enclosing loop retry */

	THROW(excpt::LockFail,
	      format("Could not validate lock file \"%s\" (errno %d)",
		     path.c_str(), errno));
      }

      if ((lfd = ::open(path.c_str(), O_RDONLY)) < 0) {
	if (errno == ENOENT)
	  return true;		/* make enclosing loop retry */

	THROW(excpt::LockFail,
	      format("Could not validate lock file \"%s\" (errno %d)",
		     path.c_str(), errno));
      }

      std::string buf;
      buf.resize(statbuf.st_size, ' ');

      if (::read(lfd, (unsigned char *) buf.data(), 
		 statbuf.st_size) != statbuf.st_size)
	THROW(excpt::LockFail,
	      format("Could not validate lock file \"%s\" (errno %d)",
		     path.c_str(), errno));

      ::close(lfd);

      {
	uint32_t lockPid = strtoul(buf.c_str(), 0, 0);

	if (os_pid_exists(lockPid))
	  return true;
	else
	  return false;
      }
    }

    void
    create_local_lockfile(std::string path)
    {
      uint32_t count;

      for(count = 0; count < 400; count++) {	/* MAX 20 seconds */
	if (try_create_local_lockfile(path))
	  return;

	/* Couldn't grab it. Check validity. Sleep if valid */
	if (!validate_local_lockfile(path)) {
	  std::string metapath = path + ".META";
      
	  bool meta = try_create_local_lockfile(metapath);

	  if (meta) {
	    ::unlink(path.c_str());
	    ::unlink(metapath.c_str());
	  }
	  else
	    nap(10);	       /* allow competitor time to clean it */
	}

	nap(50);			/* wait for competitor to finish */
      }

      THROW(excpt::LockFail,
	    format("Could not establish lock file \"%s\" "
		   "(errno %d) Remove by hand?",
		   path.c_str(), errno));
    }

    void
    nap(uint32_t ms)
    {
      struct timeval tv;
      tv.tv_sec = 0;
      tv.tv_usec = ms * 1000;

      ::select(0, 0, 0, 0, &tv);
    }

#ifdef HAVE_SVR4_STATVFS
    bool 
    is_local_path(std::string path)
    {
      struct statvfs sfs;
      statvfs(path.c_str(), &sfs);

      if (strncmp(sfs.f_basetype, "nfs", FSTYPSZ) == 0)
	return false;
      return true;
    }
#elif defined (HAVE_SYS_STATFS_H)
    bool 
    is_local_path(std::string path)
    {
      struct statfs sfs;

      ::statfs(path.c_str(), &sfs);

#ifdef __linux__
      switch(sfs.f_type) {
      case NFS_SUPER_MAGIC:
	return false;
      default:
	return true;
      }
#elif defined(__OpenBSD__)
      if (sfs.f_flags & MNT_LOCAL)
	return true;
      return false;
#else
      return true;
#endif /* __linux __ */
    }
#else /* Neither statfs nor statvfs available. is_local_path() is
         a heuristic anyway, so just return true here. */
    bool 
    is_local_path(std::string path)
    {
      return true;
    }
#endif

    void
    background(void)
    {
      if (setsid() == -1)
	THROW(excpt::Subprocess, 
	      format("Could not establish new session: %s\n",
		     strerror(errno)));
    }

    void
    daemonize(void)
    {
      int fd;
      pid_t pid;

      pid = fork();
      if (pid == -1)
	THROW(excpt::Subprocess, format("Daemon fork(): %s", strerror(errno)));

      if (pid != 0)
	exit(0);

      /*
       * We're the child.
       */

      background();

      /* FIX: This really should be closing stdout, stderr too, but I want
       * to be able to see the error messages until we get a real logging
       * mechanism in place. */

      fd = open("/dev/null", O_RDWR, 0);
      if (fd != -1) {
	close(STDIN_FILENO);
	(void)dup2(fd, STDIN_FILENO);
#if 0
	close(STDOUT_FILENO);
	(void)dup2(fd, STDOUT_FILENO);
	close(STDERR_FILENO);
	(void)dup2(fd, STDERR_FILENO);
#endif
	if (fd != STDIN_FILENO &&
	    fd != STDOUT_FILENO &&
	    fd != STDERR_FILENO)
	  (void)close(fd);
      }
    }
  } /* namespace os */
} /* namespace sherpa */
