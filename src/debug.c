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
	GtkWidget *hbox;

	vbox = gtk_vbox_new(FALSE, PAD_LINE);

	hbox = create_toggle("Verbose Output", VERBOSE);
	gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

	hbox = create_toggle("Show Header", SHOWHEADER);
	gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

	hbox = create_toggle("Disassemble", DISASM);
	gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

	return vbox;
}
