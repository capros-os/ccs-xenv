dnl IRIX puts things in /usr/freeware, and the libs in /usr/freeware/lib32 just
dnl to be a pain.
AC_DEFUN([CHECK_SSL], [
  AC_CACHE_CHECK([for OpenSSL library],
                 vl_cv_lib_ssl, [
    ssl_dirs="/usr/local/ssl /usr/lib/ssl /usr/ssl /usr/plg /usr/local /usr /usr/freeware"
    if test -n "$try_ssldir"; then
      ssl_dirs="$try_ssldir $ssl_dirs"
    fi
    for dir in $ssl_dirs; do
      dnl if dir does not exist, skip it
      if test ! -d "$dir" ; then
        continue;
      fi
      if test -f "$dir/include/openssl/ssl.h"; then
        vl_cv_lib_ssl="$dir"
        break;
      fi
    done
    if test -z "$vl_cv_lib_ssl"; then
      vl_cv_lib_ssl="no"
    fi
  ])
  if test "$vl_cv_lib_ssl" != "no"; then
    ssldir="$vl_cv_lib_ssl"
    SSL_LIBS="-lssl -lcrypto"
    if test "$ssldir" = "/usr/freeware"; then
      SSL_INC="-I$ssldir/include"
      SSL_LDFLAGS="-L$ssldir/lib32";
    elif test "$ssldir" != "/usr"; then
      SSL_INC="-I$ssldir/include"
      SSL_LDFLAGS="-L$ssldir/lib"
    fi
    AC_DEFINE(HAVE_OPENSSL, 1,
              [Define if you have the OpenSSL library])
  else
    AC_MSG_ERROR([You must have OpenSSL installed to build coytools])
  fi
])dnl
