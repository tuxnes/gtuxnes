// SPDX-FileCopyrightText: 2000-2001 Scott Weber <scott@scottweber.com>
// SPDX-FileCopyrightText: 2014-2024 Kyle Guinn <elyk03@gmail.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "gtuxnes.h"

GtkWidget *create_input_options_page(void)
{
	GtkWidget *vbox;
	GtkWidget *hbox;

	vbox = gtk_vbox_new(FALSE, PAD_LINE);

	hbox = create_toggle("Sticky Keys", STICKYKEYS);
	gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

	hbox = create_toggle("Swap Inputs", SWAPINPUT);
	gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

	hbox = create_toggled_file("Enable Joystick 1 Device:", JOY1, 10, "Choose Joystick 1");
	gtk_file_chooser_set_filename(GTK_FILE_CHOOSER(widgets[JOY1]), "/dev/js0");
	gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

	hbox = create_toggled_file("Enable Joystick 2 Device:", JOY2, 10, "Choose Joystick 2");
	gtk_file_chooser_set_filename(GTK_FILE_CHOOSER(widgets[JOY2]), "/dev/js1");
	gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

	hbox = create_toggled_entry("Remap Joystick:", JOYREMAP, 25);
	gtk_entry_set_text(GTK_ENTRY(widgets[JOYREMAP]), "1:B0,B1,B2,B3,A0,A1,B4");
	gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

	return vbox;
}
