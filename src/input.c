/*
 * Copyright (C) 2000-2001  Scott Weber  <scott@scottweber.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.  Please see the file COPYING for the
 * full text of the License.
*/

#include "gtuxnes.h"

GtkWidget *create_input_options_page(void)
{
	GtkWidget *frame;
	GtkWidget *hbox;
	GtkWidget *vbox;
	GtkWidget *button;


	frame = gtk_frame_new(NULL);

	vbox = gtk_vbox_new(FALSE, 5);

	button = create_toggle("Sticky Keys", STICKYKEYS);
	gtk_box_pack_start(GTK_BOX(vbox), button, FALSE, FALSE, 0);

	button = create_toggle("Swap Inputs", SWAPINPUT);
	gtk_box_pack_start(GTK_BOX(vbox), button, FALSE, FALSE, 0);

	hbox = create_toggled_file("Enable Joystick 1 Device:", JOY1, 150, "Choose Joystick 1");
	gtk_file_chooser_set_filename(GTK_FILE_CHOOSER(widgets[JOY1]), "/dev/js0");
	gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

	hbox = create_toggled_file("Enable Joystick 2 Device:", JOY2, 150, "Choose Joystick 2");
	gtk_file_chooser_set_filename(GTK_FILE_CHOOSER(widgets[JOY2]), "/dev/js1");
	gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

	hbox = create_toggled_entry("Remap Joystick:", JOYREMAP, 200);
	gtk_entry_set_text(GTK_ENTRY(widgets[JOYREMAP]), "1:B0,B1,B2,B3,A0,A1,B4");
	gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

	gtk_container_add(GTK_CONTAINER(frame), vbox);

	return frame;
}
