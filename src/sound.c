/*
 * Copyright (C) 2000-2001  Scott Weber  <scott@scottweber.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.  Please see the file COPYING for the
 * full text of the License.
*/

#include "gtuxnes.h"

const gchar *translate_sound_combo(int box)
{
	const char *combo_text;
	if (box == SNDFORMAT) {
		combo_text = gtk_entry_get_text(GTK_ENTRY(GTK_COMBO(widgets[SNDFORMAT])->entry));
		if (combo_text[0] == '8') {
			switch(combo_text[6]) {
			case 'M':
				return "mu8";
			case 'U':
				return "8";
			case 'S':
				return "8s";
			default:
				return NULL;
			}
		} else {
			switch(combo_text[7]) {
			case 'U':
				if (strlen(combo_text) > 15)
					return (combo_text[17] == 'l' ?
								"le16u" : "be16u");
				else
					return "16u";
			case 'S':
				if (strlen(combo_text) > 13)
					return (combo_text[15] == 'l' ?
								"le16" : "be16");
				else
					return "16";
			default:
				return NULL;
			}
		}
	} else {
		return NULL;
	}
}

GtkWidget *create_sound_options_page(void)
{
	GtkWidget *hbox;
	GtkWidget *vbox;
	GtkWidget *button;
	GtkWidget *lbl;
	GList *glist=NULL;


	frame = gtk_frame_new(NULL);

	vbox = gtk_vbox_new(FALSE, 5);

	button = create_toggle("Mute Sound", MUTESOUND);
	gtk_box_pack_start(GTK_BOX(vbox), button, FALSE, FALSE, 0);

	hbox = create_toggled_file("Specify Sound Device:", SNDDEV, 150, "Choose Sound Device");
	gtk_file_chooser_set_filename(GTK_FILE_CHOOSER(widgets[SNDDEV]), "/dev/dsp");
	gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

	glist = g_list_append(glist, "8-bit Mu-Law");
	glist = g_list_append(glist, "8-bit Unsigned");
	glist = g_list_append(glist, "8-bit Signed");
	glist = g_list_append(glist, "16-bit Unsigned");
	glist = g_list_append(glist, "16-bit Signed");
	glist = g_list_append(glist, "16-bit Unsigned (little-endian)");
	glist = g_list_append(glist, "16-bit Signed (little-endian)");
	glist = g_list_append(glist, "16-bit Unsigned (big-endian)");
	glist = g_list_append(glist, "16-bit Signed (big-endian)");
	hbox = create_toggled_combo("Specify Sample Format:", SNDFORMAT, 170, glist);
	g_list_free(glist);
	glist = NULL;
	gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

	glist = g_list_append(glist, "8000");
	glist = g_list_append(glist, "11025");
	glist = g_list_append(glist, "22050");
	glist = g_list_append(glist, "44100");
	hbox = create_toggled_combo("Specify Rate:", SNDRATE, 75, glist);
	gtk_entry_set_editable(GTK_ENTRY(GTK_COMBO(widgets[SNDRATE])->entry), TRUE);
	g_list_free(glist);
	glist = NULL;
	lbl = gtk_label_new("Hz");
	gtk_box_pack_start(GTK_BOX(hbox), lbl, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);
	gtk_entry_set_text(GTK_ENTRY(GTK_COMBO(widgets[SNDRATE])->entry), "44100");

	hbox = create_toggled_entry("Specify Maximum Delay:", SNDDELAY, 30);
	lbl = gtk_label_new("seconds");
	gtk_box_pack_start(GTK_BOX(hbox), lbl, FALSE, FALSE, 0);
	gtk_entry_set_text(GTK_ENTRY(widgets[SNDDELAY]), ".5");
	gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

	gtk_container_add(GTK_CONTAINER(frame), vbox);

	return frame;
}
