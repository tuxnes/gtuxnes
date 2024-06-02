# SPDX-FileCopyrightText: 2014-2024 Kyle Guinn <elyk03@gmail.com>
# SPDX-License-Identifier: GPL-2.0-or-later

#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([GTuxNES],[0.75],[https://github.com/tuxnes/gtuxnes])
AC_CONFIG_SRCDIR([src/gtuxnes.h])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE([foreign subdir-objects])
AM_SILENT_RULES([yes])

# Checks for programs.
AC_PROG_CC_C99
PKG_PROG_PKG_CONFIG

# Checks for libraries.
PKG_CHECK_MODULES([GTK],[gtk+-2.0],
	[],
	[AC_MSG_ERROR([cannot find gtk+-2.0])])

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h string.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

# Checks for library functions.

AC_CONFIG_FILES([Makefile])
AC_CONFIG_HEADERS([src/config.h])
AC_OUTPUT
