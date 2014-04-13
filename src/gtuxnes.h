/* GTuxNES - A GUI launcher built for TuxNES.
 * version: 0.3.0
 * tuxnes version: devel (3/5/2001)
 *
 * Please see the file AUTHORS.
 *
 * cmd-line options implemented:
 * v f M g H d l i m G E L S r I K X s F R D p P b 1 2 N J
 * --display=
 *
 * cmd-line options not yet implemented:
 *
 *
 * Copyright (C) 2000-2001  Scott Weber  <scott@scottweber.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.  Please see the file COPYING for the
 * full text of the License.
 */

#ifndef GTUXNES_H
#define GTUXNES_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gtk/gtk.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include "panels.h"
#include "settings.h"

#define PAD_BORDER       8
#define PAD_LINE         4
#define PAD_SPACE        4

#define NUM_OF_TOGGLES  31      /* = lastnum + 1 */
#define VERBOSE          0
/* 1 reserved for MAPPER (see below) */
/* 2 reserved for GAMEGENIE (see below) */
/* 3 reserved for SNDDEV (see below) */
/* 4 reserved for SNDFORMAT (see below) */
/* 5 reserved for SNDRATE (see below) */
/* 6 reserved for SNDDELAY (see below) */
/* 7 reserved for RENDERER (see below) */
/* 8 reserved for MIRROR (see below) */
/* 9 reserved for BLTINPAL (see below) */
/* 10 reserved for PALFILE (see below) */
/* 11 reserved for GEOMETRY (see below) */
/* 12 reserved for SCANLINES (see below) */
/* 13 reserved for ENLARGE (see below) */
/* 14 reserved for JOY1 (see below) */
/* 15 reserved for JOY2 (see below) */
/* 16 reserved for DISPLAY (see below) */
/* 17 reserved for JOYREMAP (see below) */
#define NTSC            18
/* 19 reserved for NTSCTINT (see below) */
#define FIXMAPPER       20
#define SHOWHEADER      21
#define DISASM          22
#define LINK            23
#define MUTESOUND       24
#define DISPINROOT      25
#define STATCOLOR       26
#define GRAYSCALE       27
#define STICKYKEYS      28
#define SWAPINPUT       29
#define IGNOREINST      30


#define NUM_OF_ENTRIES  20      /* = lastnum + 1 */
#define ROMNAME          0
#define MAPPER           1
#define GAMEGENIE        2
#define SNDDEV           3
#define SNDFORMAT        4
#define SNDRATE          5
#define SNDDELAY         6
#define RENDERER         7
#define MIRROR           8
#define BLTINPAL         9
#define PALFILE         10
#define GEOMETRY        11
#define SCANLINES       12
#define ENLARGE         13
#define JOY1            14
#define JOY2            15
#define DISPLAY         16
#define JOYREMAP        17
#define NTSCHUE         18
#define NTSCTINT        19

GtkWidget *toggles[NUM_OF_TOGGLES];
GtkWidget *widgets[NUM_OF_ENTRIES];

GtkWidget *create_general_options_page(void);
GtkWidget *create_sound_options_page(void);
GtkWidget *create_video_options_page(void);
GtkWidget *create_palette_options_page(void);
GtkWidget *create_input_options_page(void);
GtkWidget *create_debug_options_page(void);

#endif /* GTUXNES_H */
