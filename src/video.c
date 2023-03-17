/*
 * Copyright (C) 2000-2001  Scott Weber  <scott@scottweber.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.  Please see the file COPYING for the
 * full text of the License.
 */

#include "gtuxnes.h"

static const char *const renderer[] = {
	"auto",
	"x11",
	"none",
	NULL
};

static const char *const renderer_user[] = {
	"Automatically Choose",
	"X11 Renderer",
	"No Video Output",
	NULL
};

static const char *const mirror[] = {
	"v",
	"h",
	"s",
	"n",
	NULL
};

static const char *const mirror_user[] = {
	"Vertical",
	"Horizontal",
	"Single-Screen",
	"None",
	NULL
};

const char *renderer_from_index(int index)
{
	int last = (sizeof renderer / sizeof *renderer) - 1;

	if (index < 0 || index > last) {
		index = last;
	}
	return renderer[index];
}

const char *mirror_from_index(int index)
{
	int last = (sizeof mirror / sizeof *mirror) - 1;

	if (index < 0 || index > last) {
		index = last;
	}
	return mirror[index];
}

GtkWidget *create_video_options_page(void)
{
	GtkWidget *vbox;
	GtkWidget *hbox;
	GtkWidget *lbl;

	vbox = gtk_vbox_new(FALSE, PAD_LINE);

	hbox = create_toggled_entry("Enlarge:", ENLARGE, 3);
	gtk_entry_set_text(GTK_ENTRY(widgets[ENLARGE]), "2");
	lbl = gtk_label_new("x");
	gtk_box_pack_start(GTK_BOX(hbox), lbl, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

	hbox = create_toggled_entry("HQX scaling:", HQX, 3);
	gtk_entry_set_text(GTK_ENTRY(widgets[HQX]), "2");
	lbl = gtk_label_new("x");
	gtk_box_pack_start(GTK_BOX(hbox), lbl, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

	hbox = create_toggled_combo("Mirroring", MIRROR, mirror_user);
	gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

	hbox = create_toggled_combo("Renderer", RENDERER, renderer_user);
	gtk_combo_box_set_active(GTK_COMBO_BOX(widgets[RENDERER]), 0);
	gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

	hbox = create_toggled_entry("Window Geometry:", GEOMETRY, 9);
	gtk_entry_set_text(GTK_ENTRY(widgets[GEOMETRY]), "640x480");
	gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

	hbox = create_toggled_entry("Display/Target ID:", DISPLAY, 9);
	gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

	hbox = create_toggle("Display In Root Window", DISPINROOT);
	gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

	return vbox;
}
