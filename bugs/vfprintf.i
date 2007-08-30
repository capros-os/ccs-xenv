# 1 "../../../../../../newlib-1.13.0/newlib/libc/stdio/vfprintf.c"
# 1 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/build-newlib-m68k/m68k-unknown-coyotos/m68000/newlib/libc/stdio//"
# 1 "<built-in>"
# 1 "<command line>"
# 1 "../../../../../../newlib-1.13.0/newlib/libc/stdio/vfprintf.c"
# 160 "../../../../../../newlib-1.13.0/newlib/libc/stdio/vfprintf.c"
# 1 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/build-newlib-m68k/m68k-unknown-coyotos/m68000/newlib/targ-include/newlib.h" 1 3 4
# 161 "../../../../../../newlib-1.13.0/newlib/libc/stdio/vfprintf.c" 2
# 178 "../../../../../../newlib-1.13.0/newlib/libc/stdio/vfprintf.c"
# 1 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/_ansi.h" 1 3 4
# 16 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/_ansi.h" 3 4
# 1 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/sys/config.h" 1 3 4



# 1 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/machine/ieeefp.h" 1 3 4
# 5 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/sys/config.h" 2 3 4
# 17 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/_ansi.h" 2 3 4
# 179 "../../../../../../newlib-1.13.0/newlib/libc/stdio/vfprintf.c" 2
# 1 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/reent.h" 1 3 4
# 48 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/reent.h" 3 4
# 1 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/sys/reent.h" 1 3 4
# 14 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/sys/reent.h" 3 4
# 1 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/sys/_types.h" 1 3 4
# 12 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/sys/_types.h" 3 4
# 1 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/sys/lock.h" 1 3 4





typedef int _LOCK_T;
typedef int _LOCK_RECURSIVE_T;
# 13 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/sys/_types.h" 2 3 4

typedef long _off_t;
__extension__ typedef long long _off64_t;


typedef int _ssize_t;





# 1 "/coyotos68k/host/lib/gcc/m68k-unknown-coyotos/4.0.2/include/stddef.h" 1 3 4
# 355 "/coyotos68k/host/lib/gcc/m68k-unknown-coyotos/4.0.2/include/stddef.h" 3 4
typedef unsigned int wint_t;
# 25 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/sys/_types.h" 2 3 4


typedef struct
{
  int __count;
  union
  {
    wint_t __wch;
    unsigned char __wchb[4];
  } __value;
} _mbstate_t;

typedef _LOCK_RECURSIVE_T _flock_t;


typedef void *_iconv_t;
# 15 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/sys/reent.h" 2 3 4




typedef unsigned long __ULong;
# 40 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/sys/reent.h" 3 4
struct _Bigint
{
  struct _Bigint *_next;
  int _k, _maxwds, _sign, _wds;
  __ULong _x[1];
};


struct __tm
{
  int __tm_sec;
  int __tm_min;
  int __tm_hour;
  int __tm_mday;
  int __tm_mon;
  int __tm_year;
  int __tm_wday;
  int __tm_yday;
  int __tm_isdst;
};







struct _on_exit_args {
 void * _fnargs[32];
 void * _dso_handle[32];

 __ULong _fntypes;


 __ULong _is_cxa;
};
# 85 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/sys/reent.h" 3 4
struct _atexit {
 struct _atexit *_next;
 int _ind;

 void (*_fns[32])(void);
        struct _on_exit_args _on_exit_args;
};
# 101 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/sys/reent.h" 3 4
struct __sbuf {
 unsigned char *_base;
 int _size;
};






typedef long _fpos_t;
# 166 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/sys/reent.h" 3 4
struct __sFILE {
  unsigned char *_p;
  int _r;
  int _w;
  short _flags;
  short _file;
  struct __sbuf _bf;
  int _lbfsize;






  void * _cookie;

  int (*_read) (void * _cookie, char *_buf, int _n);
  int (*_write) (void * _cookie, const char *_buf, int _n);

  _fpos_t (*_seek) (void * _cookie, _fpos_t _offset, int _whence);
  int (*_close) (void * _cookie);


  struct __sbuf _ub;
  unsigned char *_up;
  int _ur;


  unsigned char _ubuf[3];
  unsigned char _nbuf[1];


  struct __sbuf _lb;


  int _blksize;
  int _offset;


  struct _reent *_data;



  _flock_t _lock;

};
# 259 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/sys/reent.h" 3 4
typedef struct __sFILE __FILE;


struct _glue
{
  struct _glue *_next;
  int _niobs;
  __FILE *_iobs;
};
# 290 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/sys/reent.h" 3 4
struct _rand48 {
  unsigned short _seed[3];
  unsigned short _mult[3];
  unsigned short _add;




};
# 565 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/sys/reent.h" 3 4
struct _reent
{
  int _errno;




  __FILE *_stdin, *_stdout, *_stderr;

  int _inc;
  char _emergency[25];

  int _current_category;
  const char *_current_locale;

  int __sdidinit;

  void (*__cleanup) (struct _reent *);


  struct _Bigint *_result;
  int _result_k;
  struct _Bigint *_p5s;
  struct _Bigint **_freelist;


  int _cvtlen;
  char *_cvtbuf;

  union
    {
      struct
        {
          unsigned int _unused_rand;
          char * _strtok_last;
          char _asctime_buf[26];
          struct __tm _localtime_buf;
          int _gamma_signgam;
          __extension__ unsigned long long _rand_next;
          struct _rand48 _r48;
          _mbstate_t _mblen_state;
          _mbstate_t _mbtowc_state;
          _mbstate_t _wctomb_state;
          char _l64a_buf[8];
          char _signal_buf[24];
          int _getdate_err;
          _mbstate_t _mbrlen_state;
          _mbstate_t _mbrtowc_state;
          _mbstate_t _mbsrtowcs_state;
          _mbstate_t _wcrtomb_state;
          _mbstate_t _wcsrtombs_state;
        } _reent;



      struct
        {

          unsigned char * _nextf[30];
          unsigned int _nmalloc[30];
        } _unused;
    } _new;


  struct _atexit *_atexit;
  struct _atexit _atexit0;


  void (**(_sig_func))(int);




  struct _glue __sglue;
  __FILE __sf[3];
};
# 799 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/sys/reent.h" 3 4
extern struct _reent *_impure_ptr ;
extern struct _reent *const _global_impure_ptr ;

void _reclaim_reent (struct _reent *);
# 49 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/reent.h" 2 3 4

# 1 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/machine/types.h" 1 3 4
# 19 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/machine/types.h" 3 4
typedef long int __off_t;
typedef int __pid_t;

__extension__ typedef long long int __loff_t;
# 51 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/reent.h" 2 3 4



# 1 "/coyotos68k/host/lib/gcc/m68k-unknown-coyotos/4.0.2/include/stddef.h" 1 3 4
# 152 "/coyotos68k/host/lib/gcc/m68k-unknown-coyotos/4.0.2/include/stddef.h" 3 4
typedef long int ptrdiff_t;
# 214 "/coyotos68k/host/lib/gcc/m68k-unknown-coyotos/4.0.2/include/stddef.h" 3 4
typedef long unsigned int size_t;
# 55 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/reent.h" 2 3 4


struct stat;
struct tms;
struct timeval;
struct timezone;



extern int _close_r (struct _reent *, int);
extern int _execve_r (struct _reent *, char *, char **, char **);
extern int _fcntl_r (struct _reent *, int, int, int);
extern int _fork_r (struct _reent *);
extern int _fstat_r (struct _reent *, int, struct stat *);
extern int _getpid_r (struct _reent *);
extern int _kill_r (struct _reent *, int, int);
extern int _link_r (struct _reent *, const char *, const char *);
extern _off_t _lseek_r (struct _reent *, int, _off_t, int);
extern int _open_r (struct _reent *, const char *, int, int);
extern _ssize_t _read_r (struct _reent *, int, void *, size_t);
extern void *_sbrk_r (struct _reent *, ptrdiff_t);
extern int _stat_r (struct _reent *, const char *, struct stat *);
extern unsigned long _times_r (struct _reent *, struct tms *);
extern int _unlink_r (struct _reent *, const char *);
extern int _wait_r (struct _reent *, int *);
extern _ssize_t _write_r (struct _reent *, int, const void *, size_t);


extern int _gettimeofday_r (struct _reent *, struct timeval *tp, struct timezone *tzp);
# 180 "../../../../../../newlib-1.13.0/newlib/libc/stdio/vfprintf.c" 2
# 1 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/stdio.h" 1 3 4
# 29 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/stdio.h" 3 4
# 1 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/_ansi.h" 1 3 4
# 30 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/stdio.h" 2 3 4




# 1 "/coyotos68k/host/lib/gcc/m68k-unknown-coyotos/4.0.2/include/stddef.h" 1 3 4
# 35 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/stdio.h" 2 3 4


# 1 "/coyotos68k/host/lib/gcc/m68k-unknown-coyotos/4.0.2/include/stdarg.h" 1 3 4
# 43 "/coyotos68k/host/lib/gcc/m68k-unknown-coyotos/4.0.2/include/stdarg.h" 3 4
typedef __builtin_va_list __gnuc_va_list;
# 38 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/stdio.h" 2 3 4
# 46 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/stdio.h" 3 4
# 1 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/sys/types.h" 1 3 4
# 25 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/sys/types.h" 3 4
# 1 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/machine/_types.h" 1 3 4
# 22 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/machine/_types.h" 3 4
# 1 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/limits.h" 1 3 4
# 125 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/limits.h" 3 4
# 1 "/coyotos68k/host/lib/gcc/m68k-unknown-coyotos/4.0.2/include/limits.h" 1 3 4
# 126 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/limits.h" 2 3 4
# 23 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/machine/_types.h" 2 3 4



typedef signed char __int8_t ;
typedef unsigned char __uint8_t ;
# 36 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/machine/_types.h" 3 4
typedef signed short __int16_t;
typedef unsigned short __uint16_t;
# 46 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/machine/_types.h" 3 4
typedef __int16_t __int_least16_t;
typedef __uint16_t __uint_least16_t;
# 58 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/machine/_types.h" 3 4
typedef signed int __int32_t;
typedef unsigned int __uint32_t;
# 76 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/machine/_types.h" 3 4
typedef __int32_t __int_least32_t;
typedef __uint32_t __uint_least32_t;
# 99 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/machine/_types.h" 3 4
typedef signed long long __int64_t;
typedef unsigned long long __uint64_t;
# 26 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/sys/types.h" 2 3 4
# 69 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/sys/types.h" 3 4
# 1 "/coyotos68k/host/lib/gcc/m68k-unknown-coyotos/4.0.2/include/stddef.h" 1 3 4
# 326 "/coyotos68k/host/lib/gcc/m68k-unknown-coyotos/4.0.2/include/stddef.h" 3 4
typedef long int wchar_t;
# 70 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/sys/types.h" 2 3 4
# 92 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/sys/types.h" 3 4
typedef unsigned char u_char;
typedef unsigned short u_short;
typedef unsigned int u_int;
typedef unsigned long u_long;



typedef unsigned short ushort;
typedef unsigned int uint;



typedef unsigned long clock_t;




typedef long time_t;




struct timespec {
  time_t tv_sec;
  long tv_nsec;
};

struct itimerspec {
  struct timespec it_interval;
  struct timespec it_value;
};


typedef long daddr_t;
typedef char * caddr_t;
# 135 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/sys/types.h" 3 4
typedef unsigned short ino_t;
# 169 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/sys/types.h" 3 4
typedef short dev_t;




typedef long off_t;

typedef unsigned short uid_t;
typedef unsigned short gid_t;


typedef int pid_t;

typedef long key_t;

typedef _ssize_t ssize_t;
# 198 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/sys/types.h" 3 4
typedef unsigned int mode_t __attribute__ ((__mode__ (__SI__)));




typedef unsigned short nlink_t;
# 225 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/sys/types.h" 3 4
typedef long fd_mask;







typedef struct _types_fd_set {
 fd_mask fds_bits[(((64)+(((sizeof (fd_mask) * 8))-1))/((sizeof (fd_mask) * 8)))];
} _types_fd_set;
# 47 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/stdio.h" 2 3 4



typedef __FILE FILE;
# 59 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/stdio.h" 3 4
typedef _fpos_t fpos_t;





# 1 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/sys/stdio.h" 1 3 4
# 66 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/stdio.h" 2 3 4
# 170 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/stdio.h" 3 4
FILE * tmpfile (void);
char * tmpnam (char *);
int fclose (FILE *);
int fflush (FILE *);
FILE * freopen (const char *, const char *, FILE *);
void setbuf (FILE *, char *);
int setvbuf (FILE *, char *, int, size_t);
int fprintf (FILE *, const char *, ...);
int fscanf (FILE *, const char *, ...);
int printf (const char *, ...);
int scanf (const char *, ...);
int sscanf (const char *, const char *, ...);
int vfprintf (FILE *, const char *, __gnuc_va_list);
int vprintf (const char *, __gnuc_va_list);
int vsprintf (char *, const char *, __gnuc_va_list);
int fgetc (FILE *);
char * fgets (char *, int, FILE *);
int fputc (int, FILE *);
int fputs (const char *, FILE *);
int getc (FILE *);
int getchar (void);
char * gets (char *);
int putc (int, FILE *);
int putchar (int);
int puts (const char *);
int ungetc (int, FILE *);
size_t fread (void *, size_t _size, size_t _n, FILE *);
size_t fwrite (const void * , size_t _size, size_t _n, FILE *);



int fgetpos (FILE *, fpos_t *);

int fseek (FILE *, long, int);



int fsetpos (FILE *, const fpos_t *);

long ftell ( FILE *);
void rewind (FILE *);
void clearerr (FILE *);
int feof (FILE *);
int ferror (FILE *);
void perror (const char *);

FILE * fopen (const char *_name, const char *_type);
int sprintf (char *, const char *, ...);
int remove (const char *);
int rename (const char *, const char *);






int fseeko (FILE *, off_t, int);
off_t ftello ( FILE *);


int asiprintf (char **, const char *, ...);
int asprintf (char **, const char *, ...);
int fcloseall (void);
int fiprintf (FILE *, const char *, ...);
int iprintf (const char *, ...);
int siprintf (char *, const char *, ...);
int snprintf (char *, size_t, const char *, ...);
int sniprintf (char *, size_t, const char *, ...);
char * tempnam (const char *, const char *);
int vasiprintf (char **, const char *, __gnuc_va_list);
int vasprintf (char **, const char *, __gnuc_va_list);
int vsniprintf (char *, size_t, const char *, __gnuc_va_list);
int vsnprintf (char *, size_t, const char *, __gnuc_va_list);
int vfiprintf (FILE *, const char *, __gnuc_va_list);
int vfiscanf (FILE *, const char *, __gnuc_va_list);
int vfscanf (FILE *, const char *, __gnuc_va_list);
int viprintf (const char *, __gnuc_va_list);
int viscanf (const char *, __gnuc_va_list);
int vscanf (const char *, __gnuc_va_list);
int vsiscanf (const char *, const char *, __gnuc_va_list);
int vsscanf (const char *, const char *, __gnuc_va_list);
# 260 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/stdio.h" 3 4
FILE * fdopen (int, const char *);

int fileno (FILE *);
int getw (FILE *);
int pclose (FILE *);
FILE * popen (const char *, const char *);
int putw (int, FILE *);
void setbuffer (FILE *, char *, int);
int setlinebuf (FILE *);
int getc_unlocked (FILE *);
int getchar_unlocked (void);
void flockfile (FILE *);
int ftrylockfile (FILE *);
void funlockfile (FILE *);
int putc_unlocked (int, FILE *);
int putchar_unlocked (int);






int _asiprintf_r (struct _reent *, char **, const char *, ...);
int _asprintf_r (struct _reent *, char **, const char *, ...);
int _fcloseall_r (struct _reent *);
FILE * _fdopen_r (struct _reent *, int, const char *);
FILE * _fopen_r (struct _reent *, const char *, const char *);
int _fclose_r (struct _reent *, FILE *);
int _fiscanf_r (struct _reent *, FILE *, const char *, ...);
int _fscanf_r (struct _reent *, FILE *, const char *, ...);
int _fseek_r (struct _reent *, FILE *, long, int);
long _ftell_r (struct _reent *, FILE *);
int _getchar_r (struct _reent *);
char * _gets_r (struct _reent *, char *);
int _iprintf_r (struct _reent *, const char *, ...);
int _iscanf_r (struct _reent *, const char *, ...);
int _mkstemp_r (struct _reent *, char *);
char * _mktemp_r (struct _reent *, char *);
void _perror_r (struct _reent *, const char *);
int _printf_r (struct _reent *, const char *, ...);
int _putchar_r (struct _reent *, int);
int _puts_r (struct _reent *, const char *);
int _remove_r (struct _reent *, const char *);
int _rename_r (struct _reent *, const char *_old, const char *_new);

int _scanf_r (struct _reent *, const char *, ...);
int _siprintf_r (struct _reent *, char *, const char *, ...);
int _siscanf_r (struct _reent *, const char *, const char *, ...);
int _sniprintf_r (struct _reent *, char *, size_t, const char *, ...);
int _snprintf_r (struct _reent *, char *, size_t, const char *, ...);
int _sprintf_r (struct _reent *, char *, const char *, ...);
int _sscanf_r (struct _reent *, const char *, const char *, ...);
char * _tempnam_r (struct _reent *, const char *, const char *);
FILE * _tmpfile_r (struct _reent *);
char * _tmpnam_r (struct _reent *, char *);
int _ungetc_r (struct _reent *, int, FILE *);
int _vasiprintf_r (struct _reent *, char **, const char *, __gnuc_va_list);
int _vasprintf_r (struct _reent *, char **, const char *, __gnuc_va_list);
int _vfiprintf_r (struct _reent *, FILE *, const char *, __gnuc_va_list);
int _vfprintf_r (struct _reent *, FILE *, const char *, __gnuc_va_list);
int _viprintf_r (struct _reent *, const char *, __gnuc_va_list);
int _vprintf_r (struct _reent *, const char *, __gnuc_va_list);
int _vsiprintf_r (struct _reent *, char *, const char *, __gnuc_va_list);
int _vsprintf_r (struct _reent *, char *, const char *, __gnuc_va_list);
int _vsniprintf_r (struct _reent *, char *, size_t, const char *, __gnuc_va_list);
int _vsnprintf_r (struct _reent *, char *, size_t, const char *, __gnuc_va_list);
int _vfiscanf_r (struct _reent *, FILE *, const char *, __gnuc_va_list);
int _vfscanf_r (struct _reent *, FILE *, const char *, __gnuc_va_list);
int _viscanf_r (struct _reent *, const char *, __gnuc_va_list);
int _vscanf_r (struct _reent *, const char *, __gnuc_va_list);
int _vsscanf_r (struct _reent *, const char *, const char *, __gnuc_va_list);
int _vsiscanf_r (struct _reent *, const char *, const char *, __gnuc_va_list);

ssize_t __getdelim (char **, size_t *, int, FILE *);
ssize_t __getline (char **, size_t *, FILE *);
# 360 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/stdio.h" 3 4
int __srget (FILE *);
int __swbuf (int, FILE *);






FILE *funopen (const void * _cookie, int (*readfn)(void * _cookie, char *_buf, int _n), int (*writefn)(void * _cookie, const char *_buf, int _n), fpos_t (*seekfn)(void * _cookie, fpos_t _off, int _whence), int (*closefn)(void * _cookie));
# 467 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/stdio.h" 3 4

# 181 "../../../../../../newlib-1.13.0/newlib/libc/stdio/vfprintf.c" 2
# 1 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/stdlib.h" 1 3 4
# 14 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/stdlib.h" 3 4
# 1 "/coyotos68k/host/lib/gcc/m68k-unknown-coyotos/4.0.2/include/stddef.h" 1 3 4
# 15 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/stdlib.h" 2 3 4


# 1 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/machine/stdlib.h" 1 3 4
# 18 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/stdlib.h" 2 3 4

# 1 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/alloca.h" 1 3 4
# 20 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/stdlib.h" 2 3 4




typedef struct
{
  int quot;
  int rem;
} div_t;

typedef struct
{
  long quot;
  long rem;
} ldiv_t;


typedef struct
{
  long long int quot;
  long long int rem;
} lldiv_t;
# 53 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/stdlib.h" 3 4
extern int __mb_cur_max;



void abort (void) __attribute__ ((noreturn));
int abs (int);
int atexit (void (*__func)(void));
double atof (const char *__nptr);

float atoff (const char *__nptr);

int atoi (const char *__nptr);
int _atoi_r (struct _reent *, const char *__nptr);
long atol (const char *__nptr);
long _atol_r (struct _reent *, const char *__nptr);
void * bsearch (const void * __key, const void * __base, size_t __nmemb, size_t __size, int (* _compar) (const void *, const void *));




void * calloc (size_t __nmemb, size_t __size);
div_t div (int __numer, int __denom);
void exit (int __status) __attribute__ ((noreturn));
void free (void *);
char * getenv (const char *__string);
char * _getenv_r (struct _reent *, const char *__string);



char * _findenv (const char *, int *);
char * _findenv_r (struct _reent *, const char *, int *);
long labs (long);
ldiv_t ldiv (long __numer, long __denom);
void * malloc (size_t __size);
int mblen (const char *, size_t);
int _mblen_r (struct _reent *, const char *, size_t, _mbstate_t *);
int mbtowc (wchar_t *, const char *, size_t);
int _mbtowc_r (struct _reent *, wchar_t *, const char *, size_t, _mbstate_t *);
int wctomb (char *, wchar_t);
int _wctomb_r (struct _reent *, char *, wchar_t, _mbstate_t *);
size_t mbstowcs (wchar_t *, const char *, size_t);
size_t _mbstowcs_r (struct _reent *, wchar_t *, const char *, size_t, _mbstate_t *);
size_t wcstombs (char *, const wchar_t *, size_t);
size_t _wcstombs_r (struct _reent *, char *, const wchar_t *, size_t, _mbstate_t *);


int mkstemp (char *);
char * mktemp (char *);


void qsort (void * __base, size_t __nmemb, size_t __size, int(*_compar)(const void *, const void *));
int rand (void);
void * realloc (void * __r, size_t __size);



void srand (unsigned __seed);
double strtod (const char *__n, char **__end_PTR);
double _strtod_r (struct _reent *,const char *__n, char **__end_PTR);
float strtof (const char *__n, char **__end_PTR);






long strtol (const char *__n, char **__end_PTR, int __base);
long _strtol_r (struct _reent *,const char *__n, char **__end_PTR, int __base);
unsigned long strtoul (const char *__n, char **__end_PTR, int __base);
unsigned long _strtoul_r (struct _reent *,const char *__n, char **__end_PTR, int __base);

int system (const char *__string);


long a64l (const char *__input);
char * l64a (long __input);
char * _l64a_r (struct _reent *,long __input);
int on_exit (void (*__func)(int, void *),void * __arg);
void _Exit (int __status) __attribute__ ((noreturn));
int putenv (char *__string);
int _putenv_r (struct _reent *, char *__string);
int setenv (const char *__string, const char *__value, int __overwrite);
int _setenv_r (struct _reent *, const char *__string, const char *__value, int __overwrite);

char * gcvt (double,int,char *);
char * gcvtf (float,int,char *);
char * fcvt (double,int,int *,int *);
char * fcvtf (float,int,int *,int *);
char * ecvt (double,int,int *,int *);
char * ecvtbuf (double, int, int*, int*, char *);
char * fcvtbuf (double, int, int*, int*, char *);
char * ecvtf (float,int,int *,int *);
char * dtoa (double, int, int, int *, int*, char**);
int rand_r (unsigned *__seed);

double drand48 (void);
double _drand48_r (struct _reent *);
double erand48 (unsigned short [3]);
double _erand48_r (struct _reent *, unsigned short [3]);
long jrand48 (unsigned short [3]);
long _jrand48_r (struct _reent *, unsigned short [3]);
void lcong48 (unsigned short [7]);
void _lcong48_r (struct _reent *, unsigned short [7]);
long lrand48 (void);
long _lrand48_r (struct _reent *);
long mrand48 (void);
long _mrand48_r (struct _reent *);
long nrand48 (unsigned short [3]);
long _nrand48_r (struct _reent *, unsigned short [3]);
unsigned short *
       seed48 (unsigned short [3]);
unsigned short *
       _seed48_r (struct _reent *, unsigned short [3]);
void srand48 (long);
void _srand48_r (struct _reent *, long);
long long atoll (const char *__nptr);
long long _atoll_r (struct _reent *, const char *__nptr);
long long llabs (long long);
lldiv_t lldiv (long long __numer, long long __denom);
long long strtoll (const char *__n, char **__end_PTR, int __base);
long long _strtoll_r (struct _reent *, const char *__n, char **__end_PTR, int __base);
unsigned long long strtoull (const char *__n, char **__end_PTR, int __base);
unsigned long long _strtoull_r (struct _reent *, const char *__n, char **__end_PTR, int __base);


void cfree (void *);
# 192 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/stdlib.h" 3 4
char * _dtoa_r (struct _reent *, double, int, int, int *, int*, char**);

void * _malloc_r (struct _reent *, size_t);
void * _calloc_r (struct _reent *, size_t, size_t);
void _free_r (struct _reent *, void *);
void * _realloc_r (struct _reent *, void *, size_t);
void _mstats_r (struct _reent *, char *);

int _system_r (struct _reent *, const char *);

void __eprintf (const char *, const char *, unsigned int, const char *);
# 233 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/stdlib.h" 3 4

# 182 "../../../../../../newlib-1.13.0/newlib/libc/stdio/vfprintf.c" 2
# 1 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/string.h" 1 3 4
# 14 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/string.h" 3 4
# 1 "/coyotos68k/host/lib/gcc/m68k-unknown-coyotos/4.0.2/include/stddef.h" 1 3 4
# 15 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/string.h" 2 3 4







void * memchr (const void *, int, size_t);
int memcmp (const void *, const void *, size_t);
void * memcpy (void *, const void *, size_t);
void * memmove (void *, const void *, size_t);
void * memset (void *, int, size_t);
char *strcat (char *, const char *);
char *strchr (const char *, int);
int strcmp (const char *, const char *);
int strcoll (const char *, const char *);
char *strcpy (char *, const char *);
size_t strcspn (const char *, const char *);
char *strerror (int);
size_t strlen (const char *);
char *strncat (char *, const char *, size_t);
int strncmp (const char *, const char *, size_t);
char *strncpy (char *, const char *, size_t);
char *strpbrk (const char *, const char *);
char *strrchr (const char *, int);
size_t strspn (const char *, const char *);
char *strstr (const char *, const char *);


char *strtok (char *, const char *);


size_t strxfrm (char *, const char *, size_t);


char *strtok_r (char *, const char *, char **);

int bcmp (const void *, const void *, size_t);
void bcopy (const void *, void *, size_t);
void bzero (void *, size_t);
int ffs (int);
char *index (const char *, int);
void * memccpy (void *, const void *, int, size_t);
void * mempcpy (void *, const void *, size_t);
char *rindex (const char *, int);
int strcasecmp (const char *, const char *);
char *strdup (const char *);
char *_strdup_r (struct _reent *, const char *);
char *strndup (const char *, size_t);
char *_strndup_r (struct _reent *, const char *, size_t);
char *strerror_r (int, char *, size_t);
size_t strlcat (char *, const char *, size_t);
size_t strlcpy (char *, const char *, size_t);
int strncasecmp (const char *, const char *, size_t);
size_t strnlen (const char *, size_t);
char *strsep (char **, const char *);
char *strlwr (char *);
char *strupr (char *);
# 96 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/string.h" 3 4
# 1 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/sys/string.h" 1 3 4
# 97 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/string.h" 2 3 4


# 183 "../../../../../../newlib-1.13.0/newlib/libc/stdio/vfprintf.c" 2
# 1 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/limits.h" 1 3 4
# 184 "../../../../../../newlib-1.13.0/newlib/libc/stdio/vfprintf.c" 2
# 1 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/wchar.h" 1 3 4
# 11 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/wchar.h" 3 4
# 1 "/coyotos68k/host/lib/gcc/m68k-unknown-coyotos/4.0.2/include/stddef.h" 1 3 4
# 12 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/wchar.h" 2 3 4
# 36 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/wchar.h" 3 4




typedef _mbstate_t mbstate_t;


wint_t btowc (int);
int wctob (wint_t);
size_t mbrlen (const char * , size_t, mbstate_t *);
size_t mbrtowc (wchar_t * , const char * , size_t, mbstate_t *);
size_t _mbrtowc_r (struct _reent *, wchar_t * , const char * , size_t, mbstate_t *);

int mbsinit (const mbstate_t *);
size_t mbsrtowcs (wchar_t * , const char ** , size_t, mbstate_t *);
size_t wcrtomb (char * , wchar_t, mbstate_t *);
size_t _wcrtomb_r (struct _reent *, char * , wchar_t, mbstate_t *);
size_t wcsrtombs (char * , const wchar_t ** , size_t, mbstate_t *);
size_t _wcsrtombs_r (struct _reent *, char * , const wchar_t ** , size_t, mbstate_t *);

wchar_t *wcscat (wchar_t * , const wchar_t *);
wchar_t *wcschr (const wchar_t *, wchar_t);
int wcscmp (const wchar_t *, const wchar_t *);
int wcscoll (const wchar_t *, const wchar_t *);
wchar_t *wcscpy (wchar_t * , const wchar_t *);
size_t wcscspn (const wchar_t *, const wchar_t *);
size_t wcslcat (wchar_t *, const wchar_t *, size_t);
size_t wcslcpy (wchar_t *, const wchar_t *, size_t);
size_t wcslen (const wchar_t *);
wchar_t *wcsncat (wchar_t * , const wchar_t * , size_t);
int wcsncmp (const wchar_t *, const wchar_t *, size_t);
wchar_t *wcsncpy (wchar_t * , const wchar_t * , size_t);
size_t wcsnlen (const wchar_t *, size_t);
wchar_t *wcspbrk (const wchar_t *, const wchar_t *);
wchar_t *wcsrchr (const wchar_t *, wchar_t);
size_t wcsspn (const wchar_t *, const wchar_t *);
wchar_t *wcsstr (const wchar_t *, const wchar_t *);
int wcswidth (const wchar_t *, size_t);
int wcwidth (const wchar_t);
wchar_t *wmemchr (const wchar_t *, wchar_t, size_t);
int wmemcmp (const wchar_t *, const wchar_t *, size_t);
wchar_t *wmemcpy (wchar_t * , const wchar_t * , size_t);
wchar_t *wmemmove (wchar_t *, const wchar_t *, size_t);
wchar_t *wmemset (wchar_t *, wchar_t, size_t);


# 185 "../../../../../../newlib-1.13.0/newlib/libc/stdio/vfprintf.c" 2



# 1 "/coyotos68k/host/lib/gcc/m68k-unknown-coyotos/4.0.2/include/stdarg.h" 1 3 4
# 105 "/coyotos68k/host/lib/gcc/m68k-unknown-coyotos/4.0.2/include/stdarg.h" 3 4
typedef __gnuc_va_list va_list;
# 189 "../../../../../../newlib-1.13.0/newlib/libc/stdio/vfprintf.c" 2



# 1 "../../../../../../newlib-1.13.0/newlib/libc/stdio/local.h" 1
# 30 "../../../../../../newlib-1.13.0/newlib/libc/stdio/local.h"
# 1 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/unistd.h" 1 3 4



# 1 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/sys/unistd.h" 1 3 4
# 13 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/sys/unistd.h" 3 4
# 1 "/coyotos68k/host/lib/gcc/m68k-unknown-coyotos/4.0.2/include/stddef.h" 1 3 4
# 14 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/sys/unistd.h" 2 3 4

extern char **environ;

void _exit (int __status ) __attribute__ ((noreturn));

int access (const char *__path, int __amode );
unsigned alarm (unsigned __secs );
int chdir (const char *__path );
int chmod (const char *__path, mode_t __mode );

int chown (const char *__path, uid_t __owner, gid_t __group );




int close (int __fildes );
char *ctermid (char *__s );
char *cuserid (char *__s );



int dup (int __fildes );
int dup2 (int __fildes, int __fildes2 );



int execl (const char *__path, const char *, ... );
int execle (const char *__path, const char *, ... );
int execlp (const char *__file, const char *, ... );
int execv (const char *__path, char * const __argv[] );
int execve (const char *__path, char * const __argv[], char * const __envp[] );
int execvp (const char *__file, char * const __argv[] );



int fchmod (int __fildes, mode_t __mode );

int fchown (int __fildes, uid_t __owner, gid_t __group );

pid_t fork (void );
long fpathconf (int __fd, int __name );
int fsync (int __fd);
int fdatasync (int __fd);
char *getcwd (char *__buf, size_t __size );




gid_t getegid (void );
uid_t geteuid (void );
gid_t getgid (void );

int getgroups (int __gidsetsize, gid_t __grouplist[] );



char *getlogin (void );



char *getpass (const char *__prompt);
size_t getpagesize (void);



pid_t getpgid (pid_t);
pid_t getpgrp (void );
pid_t getpid (void );
pid_t getppid (void );




uid_t getuid (void );






int isatty (int __fildes );

int lchown (const char *__path, uid_t __owner, gid_t __group );

int link (const char *__path1, const char *__path2 );
int nice (int __nice_value );

off_t lseek (int __fildes, off_t __offset, int __whence );

long pathconf (const char *__path, int __name );
int pause (void );



int pipe (int __fildes[2] );
ssize_t pread (int __fd, void *__buf, size_t __nbytes, off_t __offset);
ssize_t pwrite (int __fd, const void *__buf, size_t __nbytes, off_t __offset);
int read (int __fd, void *__buf, size_t __nbyte );




int rmdir (const char *__path );



void * sbrk (ptrdiff_t __incr);





int setgid (gid_t __gid );




int setpgid (pid_t __pid, pid_t __pgid );
int setpgrp (void );




pid_t setsid (void );

int setuid (uid_t __uid );




unsigned sleep (unsigned int __seconds );
void swab (const void *, void *, ssize_t);
long sysconf (int __name );
pid_t tcgetpgrp (int __fildes );
int tcsetpgrp (int __fildes, pid_t __pgrp_id );
char *ttyname (int __fildes );



int unlink (const char *__path );
int vhangup (void );
int write (int __fd, const void *__buf, size_t __nbyte );






extern char *optarg;
extern int optind, opterr, optopt;
int getopt(int, char * const [], const char *);
extern int optreset;



pid_t vfork (void );

extern char *suboptarg;
int getsubopt(char **, char * const *, char **);
# 227 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/sys/unistd.h" 3 4
# 1 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/sys/features.h" 1 3 4
# 228 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/sys/unistd.h" 2 3 4
# 5 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/unistd.h" 2 3 4
# 31 "../../../../../../newlib-1.13.0/newlib/libc/stdio/local.h" 2

extern int __svfscanf_r (struct _reent *,FILE *, const char *,va_list);
extern int __svfiscanf_r (struct _reent *,FILE *, const char *,va_list);
extern FILE *__sfp (struct _reent *);
extern int __sflags (struct _reent *,const char*, int*);
extern int __srefill (FILE *);
extern int __sread (void *, char *, int);
extern int __swrite (void *, char const *, int);
extern _fpos_t __sseek (void *, _fpos_t, int);
extern int __sclose (void *);
extern int __stextmode (int);
extern void __sinit (struct _reent *);
extern void _cleanup_r (struct _reent *);
extern void __smakebuf (FILE *);
extern int _fwalk (struct _reent *, int (*)(FILE *));
extern int _fwalk_reent (struct _reent *, int (*)(struct _reent *, FILE *));
struct _glue * __sfmoreglue (struct _reent *,int n);
extern int __srefill (FILE *fp);
# 83 "../../../../../../newlib-1.13.0/newlib/libc/stdio/local.h"
char *_dcvt (struct _reent *, char *, double, int, int, char, int);
char *_sicvt (char *, short, char);
char *_icvt (char *, int, char);
char *_licvt (char *, long, char);

char *_llicvt (char *, long long, char);
# 101 "../../../../../../newlib-1.13.0/newlib/libc/stdio/local.h"
void __sfp_lock_acquire (void);
void __sfp_lock_release (void);
void __sinit_lock_acquire (void);
void __sinit_lock_release (void);
# 193 "../../../../../../newlib-1.13.0/newlib/libc/stdio/vfprintf.c" 2
# 1 "../../../../../../newlib-1.13.0/newlib/libc/stdio/fvwrite.h" 1
# 24 "../../../../../../newlib-1.13.0/newlib/libc/stdio/fvwrite.h"
struct __siov {
 const void * iov_base;
 size_t iov_len;
};
struct __suio {
 struct __siov *uio_iov;
 int uio_iovcnt;
 int uio_resid;
};


extern int __sfvwrite (FILE *, struct __suio *);
extern int __swsetup (FILE *);
# 194 "../../../../../../newlib-1.13.0/newlib/libc/stdio/vfprintf.c" 2
# 1 "../../../../../../newlib-1.13.0/newlib/libc/stdio/vfieeefp.h" 1
# 33 "../../../../../../newlib-1.13.0/newlib/libc/stdio/vfieeefp.h"
# 1 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/ieeefp.h" 1 3 4
# 16 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/ieeefp.h" 3 4
typedef union
{
  double value;
  struct
  {
    unsigned int sign : 1;
    unsigned int exponent: 11;
    unsigned int fraction0:4;
    unsigned int fraction1:16;
    unsigned int fraction2:16;
    unsigned int fraction3:16;

  } number;
  struct
  {
    unsigned int sign : 1;
    unsigned int exponent: 11;
    unsigned int quiet:1;
    unsigned int function0:3;
    unsigned int function1:16;
    unsigned int function2:16;
    unsigned int function3:16;
  } nan;
  struct
  {
    unsigned long msw;
    unsigned long lsw;
  } parts;
    long aslong[2];
} __ieee_double_shape_type;
# 97 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/ieeefp.h" 3 4
typedef union
{
  float value;
  struct
  {
    unsigned int sign : 1;
    unsigned int exponent: 8;
    unsigned int fraction0: 7;
    unsigned int fraction1: 16;
  } number;
  struct
  {
    unsigned int sign:1;
    unsigned int exponent:8;
    unsigned int quiet:1;
    unsigned int function0:6;
    unsigned int function1:16;
  } nan;
  long p1;

} __ieee_float_shape_type;
# 153 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/ieeefp.h" 3 4
typedef int fp_rnd;





fp_rnd fpgetround (void);
fp_rnd fpsetround (fp_rnd);



typedef int fp_except;






fp_except fpgetmask (void);
fp_except fpsetmask (fp_except);
fp_except fpgetsticky (void);
fp_except fpsetsticky (fp_except);



typedef int fp_rdi;



fp_rdi fpgetroundtoi (void);
fp_rdi fpsetroundtoi (fp_rdi);

int isnan (double);
int isinf (double);
int finite (double);



int isnanf (float);
int isinff (float);
int finitef (float);
# 34 "../../../../../../newlib-1.13.0/newlib/libc/stdio/vfieeefp.h" 2
# 1 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/math.h" 1 3 4
# 10 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/math.h" 3 4







union __dmath
{
  __ULong i[2];
  double d;
};




extern const union __dmath __infinity[];
# 35 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/math.h" 3 4
extern double atan (double);
extern double cos (double);
extern double sin (double);
extern double tan (double);
extern double tanh (double);
extern double frexp (double, int *);
extern double modf (double, double *);
extern double ceil (double);
extern double fabs (double);
extern double floor (double);






extern double acos (double);
extern double asin (double);
extern double atan2 (double, double);
extern double cosh (double);
extern double sinh (double);
extern double exp (double);
extern double ldexp (double, int);
extern double log (double);
extern double log10 (double);
extern double pow (double, double);
extern double sqrt (double);
extern double fmod (double, double);
# 72 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/math.h" 3 4
typedef float float_t;
typedef double double_t;
# 82 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/math.h" 3 4
extern int __fpclassifyf (float x);
extern int __fpclassifyd (double x);
extern int __signbitf (float x);
extern int __signbitd (double x);
# 123 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/math.h" 3 4
extern double infinity (void);
extern double nan (const char *);
extern int isnan (double);
extern int isinf (double);
extern int finite (double);
extern double copysign (double, double);
extern int ilogb (double);

extern double asinh (double);
extern double cbrt (double);
extern double nextafter (double, double);
extern double rint (double);
extern double scalbn (double, int);

extern double exp2 (double);
extern double scalbln (double, long int);
extern double tgamma (double);
extern double nearbyint (double);
extern long int lrint (double);
extern double round (double);
extern long int lround (double);
extern double trunc (double);
extern double remquo (double, double, int *);
extern double copysign (double, double);
extern double fdim (double, double);
extern double fmax (double, double);
extern double fmin (double, double);
extern double fma (double, double, double);
extern void sincos (double, double *, double *);


extern double log1p (double);
extern double expm1 (double);



extern double acosh (double);
extern double atanh (double);
extern double remainder (double, double);
extern double gamma (double);
extern double gamma_r (double, int *);
extern double lgamma (double);
extern double lgamma_r (double, int *);
extern double erf (double);
extern double erfc (double);
extern double y0 (double);
extern double y1 (double);
extern double yn (int, double);
extern double j0 (double);
extern double j1 (double);
extern double jn (int, double);



extern double hypot (double, double);


extern double cabs();
extern double drem (double, double);
# 191 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/math.h" 3 4
extern float atanf (float);
extern float cosf (float);
extern float sinf (float);
extern float tanf (float);
extern float tanhf (float);
extern float frexpf (float, int *);
extern float modff (float, float *);
extern float ceilf (float);
extern float fabsf (float);
extern float floorf (float);


extern float acosf (float);
extern float asinf (float);
extern float atan2f (float, float);
extern float coshf (float);
extern float sinhf (float);
extern float expf (float);
extern float ldexpf (float, int);
extern float logf (float);
extern float log10f (float);
extern float powf (float, float);
extern float sqrtf (float);
extern float fmodf (float, float);
# 223 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/math.h" 3 4
extern float exp2f (float);
extern float scalblnf (float, long int);
extern float tgammaf (float);
extern float nearbyintf (float);
extern long int lrintf (float);
extern float roundf (float);
extern long int lroundf (float);
extern float truncf (float);
extern float remquof (float, float, int *);
extern float copysignf (float, float);
extern float fdimf (float, float);
extern float fmaxf (float, float);
extern float fminf (float, float);
extern float fmaf (float, float, float);

extern float infinityf (void);
extern float nanf (const char *);
extern int isnanf (float);
extern int isinff (float);
extern int finitef (float);
extern float copysignf (float, float);
extern int ilogbf (float);

extern float asinhf (float);
extern float cbrtf (float);
extern float nextafterf (float, float);
extern float rintf (float);
extern float scalbnf (float, int);
extern float log1pf (float);
extern float expm1f (float);
extern void sincosf (float, float *, float *);


extern float acoshf (float);
extern float atanhf (float);
extern float remainderf (float, float);
extern float gammaf (float);
extern float gammaf_r (float, int *);
extern float lgammaf (float);
extern float lgammaf_r (float, int *);
extern float erff (float);
extern float erfcf (float);
extern float y0f (float);
extern float y1f (float);
extern float ynf (int, float);
extern float j0f (float);
extern float j1f (float);
extern float jnf (int, float);

extern float hypotf (float, float);

extern float cabsf();
extern float dremf (float, float);






extern int *__signgam (void);
# 292 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/math.h" 3 4
struct exception

{
  int type;
  char *name;
  double arg1;
  double arg2;
  double retval;
  int err;
};




extern int matherr (struct exception *e);
# 347 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/math.h" 3 4
enum __fdlibm_version
{
  __fdlibm_ieee = -1,
  __fdlibm_svid,
  __fdlibm_xopen,
  __fdlibm_posix
};




extern const enum __fdlibm_version __fdlib_version;
# 367 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/math.h" 3 4

# 35 "../../../../../../newlib-1.13.0/newlib/libc/stdio/vfieeefp.h" 2
# 1 "/coyotos68k/host/lib/gcc/m68k-unknown-coyotos/4.0.2/include/float.h" 1 3 4
# 36 "../../../../../../newlib-1.13.0/newlib/libc/stdio/vfieeefp.h" 2
# 1 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/errno.h" 1 3 4




typedef int error_t;



# 1 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/sys/errno.h" 1 3 4
# 15 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/sys/errno.h" 3 4
extern int *__errno (void);




extern const char * const _sys_errlist[];
extern int _sys_nerr;
# 10 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/errno.h" 2 3 4
# 37 "../../../../../../newlib-1.13.0/newlib/libc/stdio/vfieeefp.h" 2
# 119 "../../../../../../newlib-1.13.0/newlib/libc/stdio/vfieeefp.h"
struct ldieee
{
  unsigned sign:1;
  unsigned exp:15;
  unsigned manh:32;
  unsigned manl:32;
};
# 144 "../../../../../../newlib-1.13.0/newlib/libc/stdio/vfieeefp.h"
union double_union
{
  double d;
  __uint32_t i[2];
};
# 195 "../../../../../../newlib-1.13.0/newlib/libc/stdio/vfprintf.c" 2
# 213 "../../../../../../newlib-1.13.0/newlib/libc/stdio/vfprintf.c"
static int
__sprint(FILE *fp , register struct __suio *uio)


{
 register int err;

 if (uio->uio_resid == 0) {
  uio->uio_iovcnt = 0;
  return (0);
 }
 err = __sfvwrite(fp, uio);
 uio->uio_resid = 0;
 uio->uio_iovcnt = 0;
 return (err);
}






static int
__sbprintf(struct _reent *rptr , register FILE *fp , const char *fmt , va_list ap)




{
 int ret;
 FILE fake;
 unsigned char buf[1024];


 fake._flags = fp->_flags & ~0x0002;
 fake._file = fp->_file;
 fake._cookie = fp->_cookie;
 fake._write = fp->_write;


 fake._bf._base = fake._p = buf;
 fake._bf._size = fake._w = sizeof (buf);
 fake._lbfsize = 0;

 (0);



 ret = _vfprintf_r (rptr, &fake, fmt, ap);
 if (ret >= 0 && fflush(&fake))
  ret = (-1);
 if (fake._flags & 0x0040)
  fp->_flags |= 0x0040;


 (0);

 return (ret);
}



# 1 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/locale.h" 1 3 4
# 24 "/home/shap/WORK/old-schema/coyotos/src/ccs-xenv/BUILD/newlib-1.13.0/newlib/libc/include/locale.h" 3 4


struct lconv
{
  char *decimal_point;
  char *thousands_sep;
  char *grouping;
  char *int_curr_symbol;
  char *currency_symbol;
  char *mon_decimal_point;
  char *mon_thousands_sep;
  char *mon_grouping;
  char *positive_sign;
  char *negative_sign;
  char int_frac_digits;
  char frac_digits;
  char p_cs_precedes;
  char p_sep_by_space;
  char n_cs_precedes;
  char n_sep_by_space;
  char p_sign_posn;
  char n_sign_posn;
};


char *setlocale (int category, const char *locale);
struct lconv *localeconv (void);


struct _reent;
char *_setlocale_r (struct _reent *, int category, const char *locale);
struct lconv *_localeconv_r (struct _reent *);


# 276 "../../../../../../newlib-1.13.0/newlib/libc/stdio/vfprintf.c" 2

# 1 "../../../../../../newlib-1.13.0/newlib/libc/stdio/floatio.h" 1
# 278 "../../../../../../newlib-1.13.0/newlib/libc/stdio/vfprintf.c" 2
# 291 "../../../../../../newlib-1.13.0/newlib/libc/stdio/vfprintf.c"
static char *
cvt (struct _reent *, long double, int, int, char *, int *, int, int *);
extern int _ldcheck (long double *);


static int exponent (char *, int, int);
# 312 "../../../../../../newlib-1.13.0/newlib/libc/stdio/vfprintf.c"
typedef long long * quad_ptr_t;
typedef void * void_ptr_t;
typedef char * char_ptr_t;
typedef long * long_ptr_t;
typedef int * int_ptr_t;
typedef short * short_ptr_t;




union arg_val
{
  int val_int;
  u_int val_u_int;
  long val_long;
  u_long val_u_long;
  float val_float;
  double val_double;
  long double val__LONG_DOUBLE;
  int_ptr_t val_int_ptr_t;
  short_ptr_t val_short_ptr_t;
  long_ptr_t val_long_ptr_t;
  char_ptr_t val_char_ptr_t;
  quad_ptr_t val_quad_ptr_t;
  void_ptr_t val_void_ptr_t;
  long long val_quad_t;
  unsigned long long val_u_quad_t;
  wint_t val_wint_t;
};

static union arg_val *
get_arg (struct _reent *data, int n, char *fmt, va_list *ap, int *numargs, union arg_val *args, int *arg_type, char **last_fmt);
# 374 "../../../../../../newlib-1.13.0/newlib/libc/stdio/vfprintf.c"
int _vfprintf_r (struct _reent *, FILE *, const char *, va_list);

int
vfprintf(FILE * fp , const char *fmt0 , va_list ap)



{
  int result;
  result = _vfprintf_r (_impure_ptr, fp, fmt0, ap);
  return result;
}

int
_vfprintf_r(struct _reent *data , FILE * fp , const char *fmt0 , va_list ap)




{
 register char *fmt;
 register int ch;
 register int n, m;
 register char *cp;
 register struct __siov *iovp;
 register int flags;
 char *fmt_anchor;
 int N;
 int arg_index;

 int numargs;
 char *saved_fmt;
 union arg_val args[32];
 int arg_type[32];
 int is_pos_arg;
 int old_is_pos_arg;

 int ret;
 int width;
 int prec;
 char sign;

 char *decimal_point = localeconv()->decimal_point;
 char softsign;




 union { int i; long double ld; } _long_double_ = {0};

 int tmp;

 int expt;
 int expsize = 0;
 int ndig;
 char expstr[7];

 unsigned long long _uquad;
 enum { OCT, DEC, HEX } base;
 int dprec;
 int realsz;
 int size;
 char *xdigs = ((void *)0);

 struct __suio uio;
 struct __siov iov[8];
 char buf[(4932 +39 +1)];
 char ox[2];




 char *malloc_buf = ((void *)0);







 static const char blanks[16] =
  {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};
 static const char zeroes[16] =
  {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'};
# 535 "../../../../../../newlib-1.13.0/newlib/libc/stdio/vfprintf.c"
 do { if ((data) && !(data)->__sdidinit) __sinit (data); } while (0);
 (((fp)->_flags & 0x0200) ? 0 : (0));


 if (((((fp)->_flags & 0x0008) == 0 || (fp)->_bf._base == ((void *)0)) && __swsetup(fp))) {
  (((fp)->_flags & 0x0200) ? 0 : (0));
  return ((-1));
 }


 if ((fp->_flags & (0x0002|0x0008|0x0010)) == (0x0002|0x0008) &&
     fp->_file >= 0) {
  (((fp)->_flags & 0x0200) ? 0 : (0));
  return (__sbprintf (data, fp, fmt0, ap));
 }

 fmt = (char *)fmt0;
 uio.uio_iov = iovp = iov;
 uio.uio_resid = 0;
 uio.uio_iovcnt = 0;
 ret = 0;
 arg_index = 0;

 saved_fmt = ((void *)0);
 arg_type[0] = -1;
 numargs = 0;
 is_pos_arg = 0;





 for (;;) {
         cp = fmt;







                while (*fmt != '\0' && *fmt != '%')
                    fmt += 1;

  if ((m = fmt - cp) != 0) {
   { iovp->iov_base = (cp); iovp->iov_len = (m); uio.uio_resid += (m); iovp++; if (++uio.uio_iovcnt >= 8) { if (__sprint(fp, &uio)) goto error; iovp = iov; } };
   ret += m;
  }




                if (*fmt == '\0')
                    goto done;

  fmt_anchor = fmt;
  fmt++;

  flags = 0;
  dprec = 0;
  width = 0;
  prec = -1;
  sign = '\0';
  N = arg_index;

  is_pos_arg = 0;


rflag: ch = *fmt++;
reswitch: switch (ch) {
  case ' ':





   if (!sign)
    sign = ' ';
   goto rflag;
  case '#':
   flags |= 0x001;
   goto rflag;
  case '*':
   n = N;


   old_is_pos_arg = is_pos_arg;
   is_pos_arg = 0;
   if (((unsigned)((*fmt) - '0') <= 9)) {
    char *old_fmt = fmt;

    n = 0;
    ch = *fmt++;
    do {
     n = 10 * n + ((ch) - '0');
     ch = *fmt++;
    } while (((unsigned)((ch) - '0') <= 9));

    if (ch == '$') {
     if (n <= 32) {
      n -= 1;
      is_pos_arg = 1;
     }
     else
      goto error;
    }
    else {
     fmt = old_fmt;
     goto rflag;
    }
   }
# 654 "../../../../../../newlib-1.13.0/newlib/libc/stdio/vfprintf.c"
   width = ( is_pos_arg ? n < numargs ? args[n].val_int : get_arg (data, n, fmt_anchor, &ap, &numargs, args, arg_type, &saved_fmt)->val_int : arg_index++ < numargs ? args[n].val_int : numargs < 32 ? args[numargs++].val_int = __builtin_va_arg(ap,int) : __builtin_va_arg(ap,int) );

   is_pos_arg = old_is_pos_arg;

   if (width >= 0)
    goto rflag;
   width = -width;

  case '-':
   flags |= 0x004;
   goto rflag;
  case '+':
   sign = '+';
   goto rflag;
  case '.':
   if ((ch = *fmt++) == '*') {
    n = N;


    old_is_pos_arg = is_pos_arg;
    is_pos_arg = 0;
    if (((unsigned)((*fmt) - '0') <= 9)) {
     char *old_fmt = fmt;

     n = 0;
     ch = *fmt++;
     do {
      n = 10 * n + ((ch) - '0');
      ch = *fmt++;
     } while (((unsigned)((ch) - '0') <= 9));

     if (ch == '$') {
      if (n <= 32) {
       n -= 1;
       is_pos_arg = 1;
      }
      else
       goto error;
     }
     else {
      fmt = old_fmt;
      goto rflag;
     }
    }

    prec = ( is_pos_arg ? n < numargs ? args[n].val_int : get_arg (data, n, fmt_anchor, &ap, &numargs, args, arg_type, &saved_fmt)->val_int : arg_index++ < numargs ? args[n].val_int : numargs < 32 ? args[numargs++].val_int = __builtin_va_arg(ap,int) : __builtin_va_arg(ap,int) );

    is_pos_arg = old_is_pos_arg;

    if (prec < 0)
     prec = -1;
    goto rflag;
   }
   n = 0;
   while (((unsigned)((ch) - '0') <= 9)) {
    n = 10 * n + ((ch) - '0');
    ch = *fmt++;
   }
   prec = n < 0 ? -1 : n;
   goto reswitch;
  case '0':





   flags |= 0x080;
   goto rflag;
  case '1': case '2': case '3': case '4':
  case '5': case '6': case '7': case '8': case '9':
   n = 0;
   do {
    n = 10 * n + ((ch) - '0');
    ch = *fmt++;
   } while (((unsigned)((ch) - '0') <= 9));

   if (ch == '$') {
    if (n <= 32) {
     N = n - 1;
     is_pos_arg = 1;
     goto rflag;
    }
    else
     goto error;
   }

   width = n;
   goto reswitch;

  case 'L':
   flags |= 0x008;
   goto rflag;

  case 'h':
   flags |= 0x040;
   goto rflag;
  case 'l':
   if (*fmt == 'l') {
    fmt++;
    flags |= 0x020;
   } else {
    flags |= 0x010;
   }
   goto rflag;
  case 'q':
   flags |= 0x020;
   goto rflag;
  case 'c':
  case 'C':
   cp = buf;
   if (ch == 'C' || (flags & 0x010)) {
    mbstate_t ps;

    memset ((void *)&ps, '\0', sizeof (mbstate_t));
    if ((size = (int)_wcrtomb_r (data, cp,
                (wchar_t)( is_pos_arg ? N < numargs ? args[N].val_wint_t : get_arg (data, N, fmt_anchor, &ap, &numargs, args, arg_type, &saved_fmt)->val_wint_t : arg_index++ < numargs ? args[N].val_wint_t : numargs < 32 ? args[numargs++].val_wint_t = __builtin_va_arg(ap,wint_t) : __builtin_va_arg(ap,wint_t) ),
             &ps)) == -1) {
     fp->_flags |= 0x0040;
     goto error;
    }
   }
   else {
    *cp = ( is_pos_arg ? N < numargs ? args[N].val_int : get_arg (data, N, fmt_anchor, &ap, &numargs, args, arg_type, &saved_fmt)->val_int : arg_index++ < numargs ? args[N].val_int : numargs < 32 ? args[numargs++].val_int = __builtin_va_arg(ap,int) : __builtin_va_arg(ap,int) );
    size = 1;
   }
   sign = '\0';
   break;
  case 'D':
   flags |= 0x010;

  case 'd':
  case 'i':
   _uquad = (flags&0x020 ? ( is_pos_arg ? N < numargs ? args[N].val_quad_t : get_arg (data, N, fmt_anchor, &ap, &numargs, args, arg_type, &saved_fmt)->val_quad_t : arg_index++ < numargs ? args[N].val_quad_t : numargs < 32 ? args[numargs++].val_quad_t = __builtin_va_arg(ap,long long) : __builtin_va_arg(ap,long long) ) : flags&0x010 ? ( is_pos_arg ? N < numargs ? args[N].val_long : get_arg (data, N, fmt_anchor, &ap, &numargs, args, arg_type, &saved_fmt)->val_long : arg_index++ < numargs ? args[N].val_long : numargs < 32 ? args[numargs++].val_long = __builtin_va_arg(ap,long) : __builtin_va_arg(ap,long) ) : flags&0x040 ? (long)(short)( is_pos_arg ? N < numargs ? args[N].val_int : get_arg (data, N, fmt_anchor, &ap, &numargs, args, arg_type, &saved_fmt)->val_int : arg_index++ < numargs ? args[N].val_int : numargs < 32 ? args[numargs++].val_int = __builtin_va_arg(ap,int) : __builtin_va_arg(ap,int) ) : (long)( is_pos_arg ? N < numargs ? args[N].val_int : get_arg (data, N, fmt_anchor, &ap, &numargs, args, arg_type, &saved_fmt)->val_int : arg_index++ < numargs ? args[N].val_int : numargs < 32 ? args[numargs++].val_int = __builtin_va_arg(ap,int) : __builtin_va_arg(ap,int) ));

   if ((long long)_uquad < 0)



   {

    _uquad = -_uquad;
    sign = '-';
   }
   base = DEC;
   goto number;

  case 'e':
  case 'E':
  case 'f':
  case 'g':
  case 'G':
   if (prec == -1) {
    prec = 6;
   } else if ((ch == 'g' || ch == 'G') && prec == 0) {
    prec = 1;
   }
# 834 "../../../../../../newlib-1.13.0/newlib/libc/stdio/vfprintf.c"
   if (flags & 0x008) {
    (_long_double_.ld) = ( is_pos_arg ? N < numargs ? args[N].val__LONG_DOUBLE : get_arg (data, N, fmt_anchor, &ap, &numargs, args, arg_type, &saved_fmt)->val__LONG_DOUBLE : arg_index++ < numargs ? args[N].val__LONG_DOUBLE : numargs < 32 ? args[numargs++].val__LONG_DOUBLE = __builtin_va_arg(ap,long double) : __builtin_va_arg(ap,long double) );
   } else {
    (_long_double_.ld) = (long double)( is_pos_arg ? N < numargs ? args[N].val_double : get_arg (data, N, fmt_anchor, &ap, &numargs, args, arg_type, &saved_fmt)->val_double : arg_index++ < numargs ? args[N].val_double : numargs < 32 ? args[numargs++].val_double = __builtin_va_arg(ap,double) : __builtin_va_arg(ap,double) );
   }


   tmp = _ldcheck (&(_long_double_.ld));
   if (tmp == 2) {
    if ((_long_double_.ld) < 0)
     sign = '-';
    cp = "Inf";
    size = 3;
    break;
   }
   if (tmp == 1) {
    cp = "NaN";
    size = 3;
    break;
   }


   flags |= 0x100;

   cp = cvt (data, (_long_double_.ld), prec, flags, &softsign,
    &expt, ch, &ndig);

   if (ch == 'g' || ch == 'G') {
    if (expt <= -4 || expt > prec)
     ch = (ch == 'g') ? 'e' : 'E';
    else
     ch = 'g';
   }
   if (ch <= 'e') {
    --expt;
    expsize = exponent (expstr, expt, ch);
    size = expsize + ndig;
    if (ndig > 1 || flags & 0x001)
     ++size;
   } else if (ch == 'f') {
    if (expt > 0) {
     size = expt;
     if (prec || flags & 0x001)
      size += prec + 1;
    } else
     size = (prec || flags & 0x001)
        ? prec + 2
        : 1;
   } else if (expt >= ndig) {
    size = expt;
    if (flags & 0x001)
     ++size;
   } else
    size = ndig + (expt > 0 ?
     1 : 2 - expt);

   if (softsign)
    sign = '-';
   break;

  case 'n':

   if (flags & 0x020)
    *( is_pos_arg ? N < numargs ? args[N].val_quad_ptr_t : get_arg (data, N, fmt_anchor, &ap, &numargs, args, arg_type, &saved_fmt)->val_quad_ptr_t : arg_index++ < numargs ? args[N].val_quad_ptr_t : numargs < 32 ? args[numargs++].val_quad_ptr_t = __builtin_va_arg(ap,quad_ptr_t) : __builtin_va_arg(ap,quad_ptr_t) ) = ret;
   else

   if (flags & 0x010)
    *( is_pos_arg ? N < numargs ? args[N].val_long_ptr_t : get_arg (data, N, fmt_anchor, &ap, &numargs, args, arg_type, &saved_fmt)->val_long_ptr_t : arg_index++ < numargs ? args[N].val_long_ptr_t : numargs < 32 ? args[numargs++].val_long_ptr_t = __builtin_va_arg(ap,long_ptr_t) : __builtin_va_arg(ap,long_ptr_t) ) = ret;
   else if (flags & 0x040)
    *( is_pos_arg ? N < numargs ? args[N].val_short_ptr_t : get_arg (data, N, fmt_anchor, &ap, &numargs, args, arg_type, &saved_fmt)->val_short_ptr_t : arg_index++ < numargs ? args[N].val_short_ptr_t : numargs < 32 ? args[numargs++].val_short_ptr_t = __builtin_va_arg(ap,short_ptr_t) : __builtin_va_arg(ap,short_ptr_t) ) = ret;
   else
    *( is_pos_arg ? N < numargs ? args[N].val_int_ptr_t : get_arg (data, N, fmt_anchor, &ap, &numargs, args, arg_type, &saved_fmt)->val_int_ptr_t : arg_index++ < numargs ? args[N].val_int_ptr_t : numargs < 32 ? args[numargs++].val_int_ptr_t = __builtin_va_arg(ap,int_ptr_t) : __builtin_va_arg(ap,int_ptr_t) ) = ret;
   continue;
  case 'O':
   flags |= 0x010;

  case 'o':
   _uquad = (flags&0x020 ? ( is_pos_arg ? N < numargs ? args[N].val_u_quad_t : get_arg (data, N, fmt_anchor, &ap, &numargs, args, arg_type, &saved_fmt)->val_u_quad_t : arg_index++ < numargs ? args[N].val_u_quad_t : numargs < 32 ? args[numargs++].val_u_quad_t = __builtin_va_arg(ap,unsigned long long) : __builtin_va_arg(ap,unsigned long long) ) : flags&0x010 ? ( is_pos_arg ? N < numargs ? args[N].val_u_long : get_arg (data, N, fmt_anchor, &ap, &numargs, args, arg_type, &saved_fmt)->val_u_long : arg_index++ < numargs ? args[N].val_u_long : numargs < 32 ? args[numargs++].val_u_long = __builtin_va_arg(ap,u_long) : __builtin_va_arg(ap,u_long) ) : flags&0x040 ? (u_long)(u_short)( is_pos_arg ? N < numargs ? args[N].val_int : get_arg (data, N, fmt_anchor, &ap, &numargs, args, arg_type, &saved_fmt)->val_int : arg_index++ < numargs ? args[N].val_int : numargs < 32 ? args[numargs++].val_int = __builtin_va_arg(ap,int) : __builtin_va_arg(ap,int) ) : (u_long)( is_pos_arg ? N < numargs ? args[N].val_u_int : get_arg (data, N, fmt_anchor, &ap, &numargs, args, arg_type, &saved_fmt)->val_u_int : arg_index++ < numargs ? args[N].val_u_int : numargs < 32 ? args[numargs++].val_u_int = __builtin_va_arg(ap,u_int) : __builtin_va_arg(ap,u_int) ));
   base = OCT;
   goto nosign;
  case 'p':
# 923 "../../../../../../newlib-1.13.0/newlib/libc/stdio/vfprintf.c"
   _uquad = (u_long)(unsigned long)( is_pos_arg ? N < numargs ? args[N].val_void_ptr_t : get_arg (data, N, fmt_anchor, &ap, &numargs, args, arg_type, &saved_fmt)->val_void_ptr_t : arg_index++ < numargs ? args[N].val_void_ptr_t : numargs < 32 ? args[numargs++].val_void_ptr_t = __builtin_va_arg(ap,void_ptr_t) : __builtin_va_arg(ap,void_ptr_t) );
   base = HEX;
   xdigs = "0123456789abcdef";
   flags |= 0x002;
   ch = 'x';
   goto nosign;
  case 's':
  case 'S':
   sign = '\0';
   if ((cp = ( is_pos_arg ? N < numargs ? args[N].val_char_ptr_t : get_arg (data, N, fmt_anchor, &ap, &numargs, args, arg_type, &saved_fmt)->val_char_ptr_t : arg_index++ < numargs ? args[N].val_char_ptr_t : numargs < 32 ? args[numargs++].val_char_ptr_t = __builtin_va_arg(ap,char_ptr_t) : __builtin_va_arg(ap,char_ptr_t) )) == ((void *)0)) {
    cp = "(null)";
    size = 6;
   }
   else if (ch == 'S' || (flags & 0x010)) {
    mbstate_t ps;
    const wchar_t *wcp;

    wcp = (const wchar_t *)cp;
    size = m = 0;
    memset ((void *)&ps, '\0', sizeof (mbstate_t));




      if (prec >= 0) {
     while (1) {
      if (wcp[m] == L'\0')
       break;
      if ((n = (int)_wcrtomb_r (data,
                                                     buf, wcp[m], &ps)) == -1) {
       fp->_flags |= 0x0040;
       goto error;
      }
      if (n + size > prec)
       break;
      m += 1;
      size += n;
      if (size == prec)
       break;
     }
    }
    else {
     if ((size = (int)_wcsrtombs_r (data,
                                                   ((void *)0), &wcp, 0, &ps)) == -1) {
      fp->_flags |= 0x0040;
      goto error;
     }
     wcp = (const wchar_t *)cp;
    }

    if (size == 0)
     break;

    if ((malloc_buf =
        (char *)_malloc_r (data, size + 1)) == ((void *)0)) {
     fp->_flags |= 0x0040;
     goto error;
    }


    memset ((void *)&ps, '\0', sizeof (mbstate_t));
    if (_wcsrtombs_r (data, malloc_buf,
                                                 &wcp, size, &ps) != size) {
     fp->_flags |= 0x0040;
     goto error;
    }
    cp = malloc_buf;
    cp[size] = '\0';
   }
   else if (prec >= 0) {





    char *p = memchr (cp, 0, prec);

    if (p != ((void *)0)) {
     size = p - cp;
     if (size > prec)
      size = prec;
    } else
     size = prec;
   } else
    size = strlen (cp);

   break;
  case 'U':
   flags |= 0x010;

  case 'u':
   _uquad = (flags&0x020 ? ( is_pos_arg ? N < numargs ? args[N].val_u_quad_t : get_arg (data, N, fmt_anchor, &ap, &numargs, args, arg_type, &saved_fmt)->val_u_quad_t : arg_index++ < numargs ? args[N].val_u_quad_t : numargs < 32 ? args[numargs++].val_u_quad_t = __builtin_va_arg(ap,unsigned long long) : __builtin_va_arg(ap,unsigned long long) ) : flags&0x010 ? ( is_pos_arg ? N < numargs ? args[N].val_u_long : get_arg (data, N, fmt_anchor, &ap, &numargs, args, arg_type, &saved_fmt)->val_u_long : arg_index++ < numargs ? args[N].val_u_long : numargs < 32 ? args[numargs++].val_u_long = __builtin_va_arg(ap,u_long) : __builtin_va_arg(ap,u_long) ) : flags&0x040 ? (u_long)(u_short)( is_pos_arg ? N < numargs ? args[N].val_int : get_arg (data, N, fmt_anchor, &ap, &numargs, args, arg_type, &saved_fmt)->val_int : arg_index++ < numargs ? args[N].val_int : numargs < 32 ? args[numargs++].val_int = __builtin_va_arg(ap,int) : __builtin_va_arg(ap,int) ) : (u_long)( is_pos_arg ? N < numargs ? args[N].val_u_int : get_arg (data, N, fmt_anchor, &ap, &numargs, args, arg_type, &saved_fmt)->val_u_int : arg_index++ < numargs ? args[N].val_u_int : numargs < 32 ? args[numargs++].val_u_int = __builtin_va_arg(ap,u_int) : __builtin_va_arg(ap,u_int) ));
   base = DEC;
   goto nosign;
  case 'X':
   xdigs = "0123456789ABCDEF";
   goto hex;
  case 'x':
   xdigs = "0123456789abcdef";
hex: _uquad = (flags&0x020 ? ( is_pos_arg ? N < numargs ? args[N].val_u_quad_t : get_arg (data, N, fmt_anchor, &ap, &numargs, args, arg_type, &saved_fmt)->val_u_quad_t : arg_index++ < numargs ? args[N].val_u_quad_t : numargs < 32 ? args[numargs++].val_u_quad_t = __builtin_va_arg(ap,unsigned long long) : __builtin_va_arg(ap,unsigned long long) ) : flags&0x010 ? ( is_pos_arg ? N < numargs ? args[N].val_u_long : get_arg (data, N, fmt_anchor, &ap, &numargs, args, arg_type, &saved_fmt)->val_u_long : arg_index++ < numargs ? args[N].val_u_long : numargs < 32 ? args[numargs++].val_u_long = __builtin_va_arg(ap,u_long) : __builtin_va_arg(ap,u_long) ) : flags&0x040 ? (u_long)(u_short)( is_pos_arg ? N < numargs ? args[N].val_int : get_arg (data, N, fmt_anchor, &ap, &numargs, args, arg_type, &saved_fmt)->val_int : arg_index++ < numargs ? args[N].val_int : numargs < 32 ? args[numargs++].val_int = __builtin_va_arg(ap,int) : __builtin_va_arg(ap,int) ) : (u_long)( is_pos_arg ? N < numargs ? args[N].val_u_int : get_arg (data, N, fmt_anchor, &ap, &numargs, args, arg_type, &saved_fmt)->val_u_int : arg_index++ < numargs ? args[N].val_u_int : numargs < 32 ? args[numargs++].val_u_int = __builtin_va_arg(ap,u_int) : __builtin_va_arg(ap,u_int) ));
   base = HEX;

   if (flags & 0x001 && _uquad != 0)
    flags |= 0x002;


nosign: sign = '\0';





number: if ((dprec = prec) >= 0)
    flags &= ~0x080;






   cp = buf + (4932 +39 +1);
   if (_uquad != 0 || prec != 0) {





    switch (base) {
    case OCT:
     do {
      *--cp = ((_uquad & 7) + '0');
      _uquad >>= 3;
     } while (_uquad);

     if (flags & 0x001 && *cp != '0')
      *--cp = '0';
     break;

    case DEC:

     while (_uquad >= 10) {
      *--cp = ((_uquad % 10) + '0');
      _uquad /= 10;
     }
     *--cp = ((_uquad) + '0');
     break;

    case HEX:
     do {
      *--cp = xdigs[_uquad & 15];
      _uquad >>= 4;
     } while (_uquad);
     break;

    default:
     cp = "bug in vfprintf: bad base";
     size = strlen (cp);
     goto skipsize;
    }
   }
# 1092 "../../../../../../newlib-1.13.0/newlib/libc/stdio/vfprintf.c"
                       else if (base == OCT && (flags & 0x001))
                         *--cp = '0';

   size = buf + (4932 +39 +1) - cp;
  skipsize:
   break;
  default:
   if (ch == '\0')
    goto done;

   cp = buf;
   *cp = ch;
   size = 1;
   sign = '\0';
   break;
  }
# 1123 "../../../../../../newlib-1.13.0/newlib/libc/stdio/vfprintf.c"
  realsz = dprec > size ? dprec : size;
  if (sign)
   realsz++;
  else if (flags & 0x002)
   realsz+= 2;


  if ((flags & (0x004|0x080)) == 0)
   { if ((n = (width - realsz)) > 0) { while (n > 16) { { iovp->iov_base = (blanks); iovp->iov_len = (16); uio.uio_resid += (16); iovp++; if (++uio.uio_iovcnt >= 8) { if (__sprint(fp, &uio)) goto error; iovp = iov; } }; n -= 16; } { iovp->iov_base = (blanks); iovp->iov_len = (n); uio.uio_resid += (n); iovp++; if (++uio.uio_iovcnt >= 8) { if (__sprint(fp, &uio)) goto error; iovp = iov; } }; } };


  if (sign) {
   { iovp->iov_base = (&sign); iovp->iov_len = (1); uio.uio_resid += (1); iovp++; if (++uio.uio_iovcnt >= 8) { if (__sprint(fp, &uio)) goto error; iovp = iov; } };
  } else if (flags & 0x002) {
   ox[0] = '0';
   ox[1] = ch;
   { iovp->iov_base = (ox); iovp->iov_len = (2); uio.uio_resid += (2); iovp++; if (++uio.uio_iovcnt >= 8) { if (__sprint(fp, &uio)) goto error; iovp = iov; } };
  }


  if ((flags & (0x004|0x080)) == 0x080)
   { if ((n = (width - realsz)) > 0) { while (n > 16) { { iovp->iov_base = (zeroes); iovp->iov_len = (16); uio.uio_resid += (16); iovp++; if (++uio.uio_iovcnt >= 8) { if (__sprint(fp, &uio)) goto error; iovp = iov; } }; n -= 16; } { iovp->iov_base = (zeroes); iovp->iov_len = (n); uio.uio_resid += (n); iovp++; if (++uio.uio_iovcnt >= 8) { if (__sprint(fp, &uio)) goto error; iovp = iov; } }; } };


  { if ((n = (dprec - size)) > 0) { while (n > 16) { { iovp->iov_base = (zeroes); iovp->iov_len = (16); uio.uio_resid += (16); iovp++; if (++uio.uio_iovcnt >= 8) { if (__sprint(fp, &uio)) goto error; iovp = iov; } }; n -= 16; } { iovp->iov_base = (zeroes); iovp->iov_len = (n); uio.uio_resid += (n); iovp++; if (++uio.uio_iovcnt >= 8) { if (__sprint(fp, &uio)) goto error; iovp = iov; } }; } };



  if ((flags & 0x100) == 0) {
   { iovp->iov_base = (cp); iovp->iov_len = (size); uio.uio_resid += (size); iovp++; if (++uio.uio_iovcnt >= 8) { if (__sprint(fp, &uio)) goto error; iovp = iov; } };
  } else {
   if (ch >= 'f') {
    if ((_long_double_.ld) == 0) {

     { iovp->iov_base = ("0"); iovp->iov_len = (1); uio.uio_resid += (1); iovp++; if (++uio.uio_iovcnt >= 8) { if (__sprint(fp, &uio)) goto error; iovp = iov; } };
     if (expt < ndig || (flags & 0x001) != 0) {
      { iovp->iov_base = (decimal_point); iovp->iov_len = (1); uio.uio_resid += (1); iovp++; if (++uio.uio_iovcnt >= 8) { if (__sprint(fp, &uio)) goto error; iovp = iov; } };
      { if ((n = (ndig - 1)) > 0) { while (n > 16) { { iovp->iov_base = (zeroes); iovp->iov_len = (16); uio.uio_resid += (16); iovp++; if (++uio.uio_iovcnt >= 8) { if (__sprint(fp, &uio)) goto error; iovp = iov; } }; n -= 16; } { iovp->iov_base = (zeroes); iovp->iov_len = (n); uio.uio_resid += (n); iovp++; if (++uio.uio_iovcnt >= 8) { if (__sprint(fp, &uio)) goto error; iovp = iov; } }; } };
     }
    } else if (expt <= 0) {
     { iovp->iov_base = ("0"); iovp->iov_len = (1); uio.uio_resid += (1); iovp++; if (++uio.uio_iovcnt >= 8) { if (__sprint(fp, &uio)) goto error; iovp = iov; } };
     if(expt || ndig) {
      { iovp->iov_base = (decimal_point); iovp->iov_len = (1); uio.uio_resid += (1); iovp++; if (++uio.uio_iovcnt >= 8) { if (__sprint(fp, &uio)) goto error; iovp = iov; } };
      { if ((n = (-expt)) > 0) { while (n > 16) { { iovp->iov_base = (zeroes); iovp->iov_len = (16); uio.uio_resid += (16); iovp++; if (++uio.uio_iovcnt >= 8) { if (__sprint(fp, &uio)) goto error; iovp = iov; } }; n -= 16; } { iovp->iov_base = (zeroes); iovp->iov_len = (n); uio.uio_resid += (n); iovp++; if (++uio.uio_iovcnt >= 8) { if (__sprint(fp, &uio)) goto error; iovp = iov; } }; } };
      { iovp->iov_base = (cp); iovp->iov_len = (ndig); uio.uio_resid += (ndig); iovp++; if (++uio.uio_iovcnt >= 8) { if (__sprint(fp, &uio)) goto error; iovp = iov; } };
     }
    } else if (expt >= ndig) {
     { iovp->iov_base = (cp); iovp->iov_len = (ndig); uio.uio_resid += (ndig); iovp++; if (++uio.uio_iovcnt >= 8) { if (__sprint(fp, &uio)) goto error; iovp = iov; } };
     { if ((n = (expt - ndig)) > 0) { while (n > 16) { { iovp->iov_base = (zeroes); iovp->iov_len = (16); uio.uio_resid += (16); iovp++; if (++uio.uio_iovcnt >= 8) { if (__sprint(fp, &uio)) goto error; iovp = iov; } }; n -= 16; } { iovp->iov_base = (zeroes); iovp->iov_len = (n); uio.uio_resid += (n); iovp++; if (++uio.uio_iovcnt >= 8) { if (__sprint(fp, &uio)) goto error; iovp = iov; } }; } };
     if (flags & 0x001)
      { iovp->iov_base = ("."); iovp->iov_len = (1); uio.uio_resid += (1); iovp++; if (++uio.uio_iovcnt >= 8) { if (__sprint(fp, &uio)) goto error; iovp = iov; } };
    } else {
     { iovp->iov_base = (cp); iovp->iov_len = (expt); uio.uio_resid += (expt); iovp++; if (++uio.uio_iovcnt >= 8) { if (__sprint(fp, &uio)) goto error; iovp = iov; } };
     cp += expt;
     { iovp->iov_base = ("."); iovp->iov_len = (1); uio.uio_resid += (1); iovp++; if (++uio.uio_iovcnt >= 8) { if (__sprint(fp, &uio)) goto error; iovp = iov; } };
     { iovp->iov_base = (cp); iovp->iov_len = (ndig-expt); uio.uio_resid += (ndig-expt); iovp++; if (++uio.uio_iovcnt >= 8) { if (__sprint(fp, &uio)) goto error; iovp = iov; } };
    }
   } else {
    if (ndig > 1 || flags & 0x001) {
     ox[0] = *cp++;
     ox[1] = '.';
     { iovp->iov_base = (ox); iovp->iov_len = (2); uio.uio_resid += (2); iovp++; if (++uio.uio_iovcnt >= 8) { if (__sprint(fp, &uio)) goto error; iovp = iov; } };
                                       if ((_long_double_.ld)) {
      { iovp->iov_base = (cp); iovp->iov_len = (ndig-1); uio.uio_resid += (ndig-1); iovp++; if (++uio.uio_iovcnt >= 8) { if (__sprint(fp, &uio)) goto error; iovp = iov; } };
     } else

      { if ((n = (ndig - 1)) > 0) { while (n > 16) { { iovp->iov_base = (zeroes); iovp->iov_len = (16); uio.uio_resid += (16); iovp++; if (++uio.uio_iovcnt >= 8) { if (__sprint(fp, &uio)) goto error; iovp = iov; } }; n -= 16; } { iovp->iov_base = (zeroes); iovp->iov_len = (n); uio.uio_resid += (n); iovp++; if (++uio.uio_iovcnt >= 8) { if (__sprint(fp, &uio)) goto error; iovp = iov; } }; } };
    } else
     { iovp->iov_base = (cp); iovp->iov_len = (1); uio.uio_resid += (1); iovp++; if (++uio.uio_iovcnt >= 8) { if (__sprint(fp, &uio)) goto error; iovp = iov; } };
    { iovp->iov_base = (expstr); iovp->iov_len = (expsize); uio.uio_resid += (expsize); iovp++; if (++uio.uio_iovcnt >= 8) { if (__sprint(fp, &uio)) goto error; iovp = iov; } };
   }
  }




  if (flags & 0x004)
   { if ((n = (width - realsz)) > 0) { while (n > 16) { { iovp->iov_base = (blanks); iovp->iov_len = (16); uio.uio_resid += (16); iovp++; if (++uio.uio_iovcnt >= 8) { if (__sprint(fp, &uio)) goto error; iovp = iov; } }; n -= 16; } { iovp->iov_base = (blanks); iovp->iov_len = (n); uio.uio_resid += (n); iovp++; if (++uio.uio_iovcnt >= 8) { if (__sprint(fp, &uio)) goto error; iovp = iov; } }; } };


  ret += width > realsz ? width : realsz;

  { if (uio.uio_resid && __sprint(fp, &uio)) goto error; uio.uio_iovcnt = 0; iovp = iov; };

                if (malloc_buf != ((void *)0)) {
   _free_r (data, malloc_buf);
   malloc_buf = ((void *)0);
  }
 }
done:
 { if (uio.uio_resid && __sprint(fp, &uio)) goto error; uio.uio_iovcnt = 0; iovp = iov; };
error:
 if (malloc_buf != ((void *)0))
  _free_r (data, malloc_buf);
 (((fp)->_flags & 0x0200) ? 0 : (0));
 return ((((fp)->_flags & 0x0040) != 0) ? (-1) : ret);

}







extern char *_ldtoa_r (struct _reent *, long double, int, int, int *, int *, char **);
# 1246 "../../../../../../newlib-1.13.0/newlib/libc/stdio/vfprintf.c"
static char *
cvt(struct _reent *data , long double value , int ndigits , int flags , char *sign , int *decpt , int ch , int *length)
# 1257 "../../../../../../newlib-1.13.0/newlib/libc/stdio/vfprintf.c"
{
 int mode, dsgn;
 char *digits, *bp, *rve;



 union
 {
   struct ldieee ieee;
   long double val;
 } ld;


 if (ch == 'f') {
  mode = 3;
 } else {




  if (ch == 'e' || ch == 'E') {
   ndigits++;
  }
  mode = 2;
 }
# 1294 "../../../../../../newlib-1.13.0/newlib/libc/stdio/vfprintf.c"
 ld.val = value;
 if (ld.ieee.sign) {
  value = -value;
  *sign = '-';
        } else
  *sign = '\000';

 digits = _ldtoa_r (data, value, mode, ndigits, decpt, &dsgn, &rve);


 if ((ch != 'g' && ch != 'G') || flags & 0x001) {
  bp = digits + ndigits;
  if (ch == 'f') {
   if (*digits == '0' && value)
    *decpt = -ndigits + 1;
   bp += *decpt;
  }
  if (value == 0)
   rve = bp;
  while (rve < bp)
   *rve++ = '0';
 }
 *length = rve - digits;
 return (digits);
}

static int
exponent(char *p0 , int exp , int fmtch)



{
 register char *p, *t;
 char expbuf[40];

 p = p0;
 *p++ = fmtch;
 if (exp < 0) {
  exp = -exp;
  *p++ = '-';
 }
 else
  *p++ = '+';
 t = expbuf + 40;
 if (exp > 9) {
  do {
   *--t = ((exp % 10) + '0');
  } while ((exp /= 10) > 9);
  *--t = ((exp) + '0');
  for (; t < expbuf + 40; *p++ = *t++);
 }
 else {
  *p++ = '0';
  *p++ = ((exp) + '0');
 }
 return (p - p0);
}
# 1387 "../../../../../../newlib-1.13.0/newlib/libc/stdio/vfprintf.c"
typedef enum {
  ZERO,
  DIGIT,
  DOLLAR,
  MODFR,
  SPEC,
  DOT,
  STAR,
  FLAG,
  OTHER,
  MAX_CH_CLASS
} CH_CLASS;

typedef enum {
  START,
  SFLAG,
  WDIG,
  WIDTH,
  SMOD,
  SDOT,
  VARW,
  VARP,
  PREC,
  VWDIG,
  VPDIG,
  DONE,
  MAX_STATE,
} STATE;

typedef enum {
  NOOP,
  NUMBER,
  SKIPNUM,
  GETMOD,
  GETARG,
  GETPW,
  GETPWB,
  GETPOS,
  PWPOS,
} ACTION;

const static CH_CLASS chclass[256] = {
               OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER,
               OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER,
               OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER,
               OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER,
               FLAG, OTHER, OTHER, FLAG, DOLLAR, OTHER, OTHER, OTHER,
               OTHER, OTHER, STAR, FLAG, OTHER, FLAG, DOT, OTHER,
               ZERO, DIGIT, DIGIT, DIGIT, DIGIT, DIGIT, DIGIT, DIGIT,
               DIGIT, DIGIT, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER,
               OTHER, OTHER, OTHER, SPEC, SPEC, SPEC, OTHER, SPEC,
               OTHER, OTHER, OTHER, OTHER, MODFR, OTHER, OTHER, SPEC,
               OTHER, OTHER, OTHER, SPEC, OTHER, SPEC, OTHER, SPEC,
               OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER,
               OTHER, OTHER, OTHER, SPEC, SPEC, SPEC, SPEC, SPEC,
               MODFR, SPEC, OTHER, OTHER, MODFR, OTHER, OTHER, SPEC,
               SPEC, MODFR, OTHER, SPEC, OTHER, SPEC, OTHER, OTHER,
               SPEC, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER,
               OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER,
               OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER,
               OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER,
               OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER,
               OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER,
               OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER,
               OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER,
               OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER,
               OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER,
               OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER,
               OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER,
               OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER,
               OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER,
               OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER,
               OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER,
               OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER,
};

const static STATE state_table[MAX_STATE][MAX_CH_CLASS] = {

               { SFLAG, WDIG, DONE, SMOD, DONE, SDOT, VARW, SFLAG, DONE },
               { SFLAG, WDIG, DONE, SMOD, DONE, SDOT, VARW, SFLAG, DONE },
               { DONE, DONE, WIDTH, SMOD, DONE, SDOT, DONE, DONE, DONE },
               { DONE, DONE, DONE, SMOD, DONE, SDOT, DONE, DONE, DONE },
               { DONE, DONE, DONE, DONE, DONE, DONE, DONE, DONE, DONE },
               { SDOT, PREC, DONE, SMOD, DONE, DONE, VARP, DONE, DONE },
               { DONE, VWDIG, DONE, SMOD, DONE, SDOT, DONE, DONE, DONE },
               { DONE, VPDIG, DONE, SMOD, DONE, DONE, DONE, DONE, DONE },
               { DONE, DONE, DONE, SMOD, DONE, DONE, DONE, DONE, DONE },
               { DONE, DONE, WIDTH, DONE, DONE, DONE, DONE, DONE, DONE },
               { DONE, DONE, PREC, DONE, DONE, DONE, DONE, DONE, DONE },
};

const static ACTION action_table[MAX_STATE][MAX_CH_CLASS] = {

               { NOOP, NUMBER, NOOP, GETMOD, GETARG, NOOP, NOOP, NOOP, NOOP },
               { NOOP, NUMBER, NOOP, GETMOD, GETARG, NOOP, NOOP, NOOP, NOOP },
               { NOOP, NOOP, GETPOS, GETMOD, GETARG, NOOP, NOOP, NOOP, NOOP },
               { NOOP, NOOP, NOOP, GETMOD, GETARG, NOOP, NOOP, NOOP, NOOP },
               { NOOP, NOOP, NOOP, NOOP, GETARG, NOOP, NOOP, NOOP, NOOP },
               { NOOP, SKIPNUM, NOOP, GETMOD, GETARG, NOOP, NOOP, NOOP, NOOP },
               { NOOP, NUMBER, NOOP, GETPW, GETPWB, GETPW, NOOP, NOOP, NOOP },
               { NOOP, NUMBER, NOOP, GETPW, GETPWB, NOOP, NOOP, NOOP, NOOP },
               { NOOP, NOOP, NOOP, GETMOD, GETARG, NOOP, NOOP, NOOP, NOOP },
               { NOOP, NOOP, PWPOS, NOOP, NOOP, NOOP, NOOP, NOOP, NOOP },
               { NOOP, NOOP, PWPOS, NOOP, NOOP, NOOP, NOOP, NOOP, NOOP },
};


static union arg_val *
get_arg(struct _reent *data , int n , char *fmt , va_list *ap , int *numargs_p , union arg_val *args , int *arg_type , char **last_fmt)
# 1504 "../../../../../../newlib-1.13.0/newlib/libc/stdio/vfprintf.c"
{
  int ch;
  int number, flags;
  int spec_type;
  int numargs = *numargs_p;
  CH_CLASS chtype;
  STATE state, next_state;
  ACTION action;
  int pos, last_arg;
  int max_pos_arg = n;
  enum types { INT, LONG_INT, SHORT_INT, QUAD_INT, CHAR, CHAR_PTR, DOUBLE, LONG_DOUBLE, WIDE_CHAR };







  if (*last_fmt != ((void *)0))
    fmt = *last_fmt;







  while (*fmt && n >= numargs)
    {
# 1544 "../../../../../../newlib-1.13.0/newlib/libc/stdio/vfprintf.c"
      while (*fmt != '\0' && *fmt != '%')
 fmt += 1;

      if (*fmt == '\0')
 break;

      state = START;
      flags = 0;
      pos = -1;
      number = 0;
      spec_type = INT;




      while (state != DONE)
 {
   ch = *fmt++;
   chtype = chclass[ch];
   next_state = state_table[state][chtype];
   action = action_table[state][chtype];
   state = next_state;

   switch (action)
     {
     case GETMOD:
       switch (ch)
  {
  case 'h':
    flags |= 0x040;
    break;
  case 'L':
    flags |= 0x008;
    break;
  case 'q':
    flags |= 0x020;
    break;
  case 'l':
  default:
    if (*fmt == 'l')
      {
        flags |= 0x020;
        ++fmt;
      }
    else
      flags |= 0x010;
    break;
  }
       break;
     case GETARG:
       {
  numargs &= (32 - 1);

  switch (ch)
    {
    case 'd':
    case 'i':
    case 'o':
    case 'x':
    case 'X':
    case 'u':
      if (flags & 0x010)
        spec_type = LONG_INT;
      else if (flags & 0x040)
        spec_type = SHORT_INT;

      else if (flags & 0x020)
        spec_type = QUAD_INT;

      else
        spec_type = INT;
      break;
    case 'D':
    case 'U':
    case 'O':
      spec_type = LONG_INT;
      break;
    case 'f':
    case 'g':
    case 'G':
    case 'E':
    case 'e':

      if (flags & 0x008)
        spec_type = LONG_DOUBLE;
      else

        spec_type = DOUBLE;
      break;
    case 's':
    case 'S':
    case 'p':
      spec_type = CHAR_PTR;
      break;
    case 'c':
      spec_type = CHAR;
      break;
    case 'C':
      spec_type = WIDE_CHAR;
      break;
    }



  if (pos != -1)
    arg_type[pos] = spec_type;
  else
    {
      switch (spec_type)
        {
        case LONG_INT:
   args[numargs++].val_long = __builtin_va_arg(*ap,long);
   break;
        case QUAD_INT:
   args[numargs++].val_quad_t = __builtin_va_arg(*ap,long long);
   break;
        case WIDE_CHAR:
   args[numargs++].val_wint_t = __builtin_va_arg(*ap,wint_t);
   break;
        case CHAR:
        case SHORT_INT:
        case INT:
   args[numargs++].val_int = __builtin_va_arg(*ap,int);
   break;
        case CHAR_PTR:
   args[numargs++].val_char_ptr_t = __builtin_va_arg(*ap,char *);
   break;
        case DOUBLE:
   args[numargs++].val_double = __builtin_va_arg(*ap,double);
   break;
        case LONG_DOUBLE:
   args[numargs++].val__LONG_DOUBLE = __builtin_va_arg(*ap,long double);
   break;
        }
    }
       }
       break;
     case GETPOS:
       if (arg_type[0] == -1)
  memset (arg_type, 0, sizeof (int) * 32);
       pos = number - 1;
       max_pos_arg = (max_pos_arg > pos ? max_pos_arg : pos);
       break;
     case PWPOS:
       if (arg_type[0] == -1)
  memset (arg_type, 0, sizeof (int) * 32);
       number -= 1;
       arg_type[number] = INT;
       max_pos_arg = (max_pos_arg > number ? max_pos_arg : number);
       break;
     case GETPWB:
       --fmt;

     case GETPW:
       args[numargs++].val_int = __builtin_va_arg(*ap,int);
       break;
     case NUMBER:
       number = (ch - '0');
       while ((ch = *fmt) != '\0' && ((unsigned)((ch) - '0') <= 9))
  {
    number = number * 10 + (ch - '0');
    ++fmt;
  }
       break;
     case SKIPNUM:
       while ((ch = *fmt) != '\0' && ((unsigned)((ch) - '0') <= 9))
  ++fmt;
       break;
     case NOOP:
     default:
       break;
     }
 }
    }



  if (*fmt == '\0')
    last_arg = max_pos_arg;
  else
    last_arg = n;

  while (numargs <= last_arg)
    {
      switch (arg_type[numargs])
 {
 case LONG_INT:
   args[numargs++].val_long = __builtin_va_arg(*ap,long);
   break;
 case QUAD_INT:
   args[numargs++].val_quad_t = __builtin_va_arg(*ap,long long);
   break;
 case CHAR_PTR:
   args[numargs++].val_char_ptr_t = __builtin_va_arg(*ap,char *);
   break;
 case DOUBLE:
   args[numargs++].val_double = __builtin_va_arg(*ap,double);
   break;
 case LONG_DOUBLE:
   args[numargs++].val__LONG_DOUBLE = __builtin_va_arg(*ap,long double);
   break;
 case WIDE_CHAR:
   args[numargs++].val_wint_t = __builtin_va_arg(*ap,wint_t);
   break;
 case INT:
 case SHORT_INT:
 case CHAR:
 default:
   args[numargs++].val_int = __builtin_va_arg(*ap,int);
   break;
 }
    }



  *numargs_p = numargs;
  *last_fmt = fmt;
  return &args[n];
}
