// SPDX-FileCopyrightText: 2000-2001 Scott Weber <scott@scottweber.com>
// SPDX-FileCopyrightText: 2014-2023 Kyle Guinn <elyk03@gmail.com>
// SPDX-License-Identifier: GPL-1.0-or-later

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
