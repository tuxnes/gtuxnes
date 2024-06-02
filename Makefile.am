# SPDX-FileCopyrightText: 2014-2024 Kyle Guinn <elyk03@gmail.com>
# SPDX-License-Identifier: GPL-2.0-or-later

ACLOCAL_AMFLAGS = -I m4

AM_CPPFLAGS = $(GTK_CFLAGS)

bin_PROGRAMS = gtuxnes

gtuxnes_SOURCES = \
	src/gtuxnes.c src/gtuxnes.h \
	src/settings.c src/settings.h \
	src/panels.c src/panels.h \
	src/general.c \
	src/sound.c \
	src/video.c \
	src/palette.c \
	src/input.c \
	src/debug.c
gtuxnes_LDADD = $(GTK_LIBS)

EXTRA_DIST = AUTHORS.md NEWS.md README.md LICENSES
