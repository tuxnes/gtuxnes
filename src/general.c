// SPDX-FileCopyrightText: 2000-2001 Scott Weber <scott@scottweber.com>
// SPDX-FileCopyrightText: 2014-2023 Kyle Guinn <elyk03@gmail.com>
// SPDX-License-Identifier: GPL-1.0-or-later

#include "gtuxnes.h"

GtkWidget *create_general_options_page(void)
{
	GtkWidget *vbox;
	GtkWidget *hbox;
	GtkWidget *entry;
	GtkWidget *lbl;

	vbox = gtk_vbox_new(FALSE, PAD_LINE);

	hbox = gtk_hbox_new(FALSE, PAD_SPACE);
	lbl = gtk_label_new("ROM Name:");
	gtk_box_pack_start(GTK_BOX(hbox), lbl, FALSE, FALSE, 0);
	entry = gtk_file_chooser_button_new("Choose ROM File", GTK_FILE_CHOOSER_ACTION_OPEN);
	gtk_file_chooser_button_set_width_chars(GTK_FILE_CHOOSER_BUTTON(entry), 20);
	gtk_box_pack_start(GTK_BOX(hbox), entry, TRUE, TRUE, 0);
	widgets[ROMNAME] = entry;
	gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

	hbox = create_toggle("Fix Mapper", FIXMAPPER);
	gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

	hbox = create_toggled_entry("Use Specific Mapper:", MAPPER, 3);
	gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

	hbox = create_toggle("Ignore Unknown Instructions", IGNOREINST);
	gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

	hbox = create_toggle("Link branches", LINK);
	gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

	hbox = create_toggled_entry("Game Genie Code:", GAMEGENIE, 8);
	gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

	return vbox;
}
