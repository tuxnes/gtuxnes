#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([GTuxNES],[0.75])
AC_CONFIG_SRCDIR([src/gtuxnes.h])
AC_CONFIG_HEADERS([src/config.h])
AM_INIT_AUTOMAKE

# Checks for programs.
AC_PROG_CC
PKG_PROG_PKG_CONFIG

# Checks for libraries.
PKG_CHECK_MODULES([GTK],[gtk+-2.0],
	[],
	[AC_MSG_ERROR([cannot find gtk+-2.0])])

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h string.h sys/ioctl.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_PID_T

# Checks for library functions.
AC_FUNC_FORK

AC_CONFIG_FILES([Makefile src/Makefile])
AC_OUTPUT
