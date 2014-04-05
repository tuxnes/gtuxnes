/*
 * Copyright (C) 2000-2001  Scott Weber  <scott@scottweber.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.  Please see the file COPYING for the
 * full text of the License.
*/

#include "gtuxnes.h"

GtkWidget *create_debug_options_page(void)
{
	GtkWidget *vbox;
	GtkWidget *button;


	frame = gtk_frame_new(NULL);

	vbox = gtk_vbox_new(FALSE, 5);

	button = create_toggle("Verbose Output", VERBOSE);
	gtk_box_pack_start(GTK_BOX(vbox), button, FALSE, FALSE, 0);
	gtk_widget_show(button);

	button = create_toggle("Show Header", SHOWHEADER);
	gtk_box_pack_start(GTK_BOX(vbox), button, FALSE, FALSE, 0);
	gtk_widget_show(button);

	button = create_toggle("Disassemble", DISASM);
	gtk_box_pack_start(GTK_BOX(vbox), button, FALSE, FALSE, 0);
	gtk_widget_show(button);

	gtk_container_add(GTK_CONTAINER(frame), vbox);
	gtk_widget_show(vbox);

	return frame;
}
