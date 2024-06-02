// SPDX-FileCopyrightText: 2000-2001 Scott Weber <scott@scottweber.com>
// SPDX-FileCopyrightText: 2014-2024 Kyle Guinn <elyk03@gmail.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "gtuxnes.h"

static const char *const bltinpal[] = {
	"loopy",
	"quor",
	"chris",
	"matt",
	"pasofami",
	"crashman",
	"mess",
	"zaphod-cv",
	"zaphod-smb",
	"vs-drmar",
	"vs-cv",
	"vs-smb",
	NULL
};

static const char *const bltinpal_user[] = {
	"Loopy's NES palette",
	"Quor's palette from Nestra 0.63",
	"Chris Covell's NES palette",
	"Matthew Conte's NES palette",
	"Palette from PasoFami/99",
	"CrashMan's NES palette",
	"palette from the MESS NES driver",
	"Zaphod's VS Castlevania palette",
	"Zaphod's VS SMB palette",
	"VS Dr. Mario palette",
	"VS Castlevania palette",
	"VS SMB/VS Ice Climber palette",
	NULL
};

const char *bltinpal_from_index(int index)
{
	int last = (sizeof bltinpal / sizeof *bltinpal) - 1;

	if (index < 0 || index > last) {
		index = last;
	}
	return bltinpal[index];
}

void correct_ntsc_value(GtkWidget *entry, gpointer item)
{
	double entry_val;
	entry_val = atof(gtk_entry_get_text(GTK_ENTRY(entry)));

	if (entry == widgets[NTSCHUE]) {
		if (entry_val > 360.0)
			gtk_entry_set_text(GTK_ENTRY(entry), "360.0");
		else if (entry_val < 0.0)
			gtk_entry_set_text(GTK_ENTRY(entry), "0.0");
	} else if (entry == widgets[NTSCTINT]) {
		if (entry_val > 1.0)
			gtk_entry_set_text(GTK_ENTRY(entry), "1.0");
		else if (entry_val < 0.0)
			gtk_entry_set_text(GTK_ENTRY(entry), "0.0");
	}
}

GtkWidget *create_palette_options_page(void)
{
	GtkWidget *vbox;
	GtkWidget *hbox;
	GtkWidget *entry;
	GtkWidget *lbl;

	vbox = gtk_vbox_new(FALSE, PAD_LINE);

	hbox = create_toggled_combo("Builtin Palette:", BLTINPAL, bltinpal_user);
	gtk_combo_box_set_active(GTK_COMBO_BOX(widgets[BLTINPAL]), 0);
	gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

	hbox = create_toggled_file("Palette File:", PALFILE, 20, "Choose Palette File");
	gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

	hbox = gtk_hbox_new(FALSE, PAD_SPACE);
	toggles[NTSC] = gtk_check_button_new_with_label("NTSC Palette:");
	toggles[NTSC+1] = toggles[NTSC];
	gtk_box_pack_start(GTK_BOX(hbox), toggles[NTSC], FALSE, FALSE, 0);
	lbl = gtk_label_new("Hue Angle:");
	gtk_box_pack_start(GTK_BOX(hbox), lbl, FALSE, FALSE, 0);
	entry = gtk_entry_new();
	gtk_widget_set_sensitive(entry, FALSE);
	g_signal_connect_swapped(toggles[NTSC], "clicked", G_CALLBACK(enable_button_toggled), entry);
	gtk_entry_set_width_chars(GTK_ENTRY(entry), 5);
	gtk_entry_set_text(GTK_ENTRY(entry), "332.0");
	gtk_box_pack_start(GTK_BOX(hbox), entry, FALSE, FALSE, 0);
	widgets[NTSCHUE] = entry;
	g_signal_connect(entry, "activate", G_CALLBACK(correct_ntsc_value), NULL);
	lbl = gtk_label_new("Tint Level:");
	gtk_box_pack_start(GTK_BOX(hbox), lbl, FALSE, FALSE, 0);
	entry = gtk_entry_new();
	gtk_widget_set_sensitive(entry, FALSE);
	g_signal_connect_swapped(toggles[NTSC], "clicked", G_CALLBACK(enable_button_toggled), entry);
	gtk_entry_set_width_chars(GTK_ENTRY(entry), 3);
	gtk_entry_set_text(GTK_ENTRY(entry), "0.5");
	gtk_box_pack_start(GTK_BOX(hbox), entry, FALSE, FALSE, 0);
	widgets[NTSCTINT] = entry;
	g_signal_connect(entry, "activate", G_CALLBACK(correct_ntsc_value), NULL);
	gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

	hbox = create_toggle("Static Color Allocation", STATCOLOR);
	gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

	hbox = create_toggle("Grayscale", GRAYSCALE);
	gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

	return vbox;
}
