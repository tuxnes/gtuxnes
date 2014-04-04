AM_CFLAGS = -std=c99
AM_CPPFLAGS = $(GTK_CFLAGS)

bin_PROGRAMS = gtuxnes

gtuxnes_SOURCES = \
	config.c config.h \
	debug.c debug.h \
	files.c files.h \
	general.c general.h \
	gtuxnes.c gtuxnes.h \
	input.c input.h \
	panels.c panels.h \
	sound.c sound.h \
	video.c video.h
gtuxnes_LDADD = $(GTK_LIBS)
