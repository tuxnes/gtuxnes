/*
 * Copyright (C) 2000-2001  Scott Weber  <scott@scottweber.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.  Please see the file COPYING for the
 * full text of the License.
*/

#include "gtuxnes.h"

GtkWidget *create_general_options_page(void)
{
	GtkWidget *hbox;
	GtkWidget *vbox;
	GtkWidget *button;
	GtkWidget *entry;
	GtkWidget *lbl;


	frame = gtk_frame_new(NULL);

	vbox = gtk_vbox_new(FALSE, 5);

	hbox = gtk_hbox_new(FALSE, 3);
	lbl = gtk_label_new("ROM Name: ");
	gtk_box_pack_start(GTK_BOX(hbox), lbl, FALSE, FALSE, 0);
	entry = gtk_entry_new();
	g_signal_connect(entry, "activate", G_CALLBACK(entry_edited), GINT_TO_POINTER(ROMNAME));
	gtk_box_pack_start(GTK_BOX(hbox), entry, FALSE, FALSE, 0);
	widgets[ROMNAME] = entry;
	button = gtk_button_new_with_label("Browse...");
	g_signal_connect(button, "clicked", G_CALLBACK(browse_files), NULL);
	gtk_box_pack_start(GTK_BOX(hbox), button, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

	button = create_toggle("Fix Mapper", FIXMAPPER);
	gtk_box_pack_start(GTK_BOX(vbox), button, FALSE, FALSE, 0);

	hbox = create_toggled_entry("Use Specific Mapper:", MAPPER, 30);
	gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

	button = create_toggle("Ignore Unknown Instructions", IGNOREINST);
	gtk_box_pack_start(GTK_BOX(vbox), button, FALSE, FALSE, 0);

	button = create_toggle("Link branches", LINK);
	gtk_box_pack_start(GTK_BOX(vbox), button, FALSE, FALSE, 0);

	hbox = create_toggled_entry("Game Genie Code:", GAMEGENIE, 100);
	gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

	gtk_container_add(GTK_CONTAINER(frame), vbox);

	return frame;
}
