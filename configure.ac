m4_define([libnxml_major_version], [0])
m4_define([libnxml_minor_version], [18])
m4_define([libnxml_macro_version], [3])

m4_define([libnxml_version],
          [libnxml_major_version.libnxml_minor_version.libnxml_macro_version])

m4_define([libnxml_version_info],
          [libnxml_minor_version:libnxml_macro_version:libnxml_minor_version])

AC_INIT([libnxml], [libnxml_version])
AC_CONFIG_SRCDIR([src/nxml_parser.c])
AC_CONFIG_MACRO_DIRS([m4])

LT_INIT

AM_INIT_AUTOMAKE([-Wall -Werror subdir-objects foreign])
AM_SANITY_CHECK
AM_CONFIG_HEADER(config.h)
AM_MAINTAINER_MODE
AC_PROG_CC
AC_ISC_POSIX
AC_PROG_LIBTOOL
AC_PROG_INSTALL
AM_PROG_CC_STDC
AC_HEADER_STDC
AC_HEADER_DIRENT
AC_CHECK_HEADER(curl/curl.h,,AC_MSG_ERROR(libcurl is required to compile libnxml))
AC_CHECK_LIB(curl,curl_version,,AC_MSG_ERROR(libcurl is required to compile libnxml))

CFLAGS="$CFLAGS -Wall -DNXML_INTERNAL"

AC_SUBST(LIBNXML_VERSION, [libnxml_version])
AC_SUBST(LIBNXML_VERSION_INFO, [libnxml_version_info])
AC_SUBST(LIBNXML_MAJOR_VERSION, [libnxml_major_version])
AC_SUBST(LIBNXML_MINOR_VERSION, [libnxml_minor_version])
AC_SUBST(LIBNXML_MICRO_VERSION, [libnxml_macro_version])

AC_OUTPUT([
Makefile
src/nxml.h
src/Makefile
test/Makefile 
doc/Makefile 
nxml.pc
doxy.conf
])
