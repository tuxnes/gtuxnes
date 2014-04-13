/*
 * Copyright (C) 2000-2001  Scott Weber  <scott@scottweber.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.  Please see the file COPYING for the
 * full text of the License.
*/

#include "gtuxnes.h"

static const char *const sndformat[] = {
	"mu8",
	"8",
	"8s",
	"16u",
	"16",
	"le16u",
	"le16",
	"be16u",
	"be16",
	NULL
};

static const char *const sndformat_user[] = {
	"8-bit Mu-Law",
	"8-bit Unsigned",
	"8-bit Signed",
	"16-bit Unsigned",
	"16-bit Signed",
	"16-bit Unsigned (little-endian)",
	"16-bit Signed (little-endian)",
	"16-bit Unsigned (big-endian)",
	"16-bit Signed (big-endian)",
	NULL
};

static const char *const sndrate[] = {
	"8000",
	"11025",
	"22050",
	"44100",
	NULL
};

const char *sndformat_from_index(int index)
{
	int last = (sizeof sndformat / sizeof *sndformat) - 1;

	if (index < 0 || index > last) {
		index = last;
	}
	return sndformat[index];
}

const char *sndrate_from_index(int index)
{
	int last = (sizeof sndrate / sizeof *sndrate) - 1;

	if (index < 0 || index > last) {
		index = last;
	}
	return sndrate[index];
}

GtkWidget *create_sound_options_page(void)
{
	GtkWidget *frame;
	GtkWidget *vbox;
	GtkWidget *hbox;
	GtkWidget *lbl;


	frame = gtk_frame_new(NULL);

	vbox = gtk_vbox_new(FALSE, PAD_LINE);

	hbox = create_toggle("Mute Sound", MUTESOUND);
	gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

	hbox = create_toggled_file("Sound Device:", SNDDEV, 10, "Choose Sound Device");
	gtk_file_chooser_set_filename(GTK_FILE_CHOOSER(widgets[SNDDEV]), "/dev/dsp");
	gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

	hbox = create_toggled_combo("Sample Format:", SNDFORMAT, sndformat_user);
	gtk_combo_box_set_active(GTK_COMBO_BOX(widgets[SNDFORMAT]), 1);
	gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

	hbox = create_toggled_combo("Sample Rate:", SNDRATE, sndrate);
	gtk_combo_box_set_active(GTK_COMBO_BOX(widgets[SNDRATE]), 3);
	lbl = gtk_label_new("Hz");
	gtk_box_pack_start(GTK_BOX(hbox), lbl, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

	hbox = create_toggled_entry("Maximum Delay:", SNDDELAY, 3);
	lbl = gtk_label_new("seconds");
	gtk_box_pack_start(GTK_BOX(hbox), lbl, FALSE, FALSE, 0);
	gtk_entry_set_text(GTK_ENTRY(widgets[SNDDELAY]), ".5");
	gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

	gtk_container_add(GTK_CONTAINER(frame), vbox);

	return frame;
}
