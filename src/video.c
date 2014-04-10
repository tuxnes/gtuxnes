/*
 * Copyright (C) 2000-2001  Scott Weber  <scott@scottweber.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.  Please see the file COPYING for the
 * full text of the License.
*/

#include "gtuxnes.h"

const gchar *translate_video_combo(int box)
{
	const char *combo_text;
	combo_text = gtk_entry_get_text(GTK_ENTRY(GTK_COMBO(widgets[box])->entry));
	if (box == RENDERER) {
		switch(combo_text[0]) {
		case 'A':
			return "auto";
		case 'X':
			return "x11";
		case 'D':
			return "diff";
		case 'T':
			return "old";
		case 'G':
			return "ggi";
		case 'W':
			return "w";
		case 'N':
			return "none";
		default:
			return NULL;
		}
	} else if (box == MIRROR) {
		switch(combo_text[0]) {
		case 'V':
			return "v";
		case 'H':
			return "h";
		case 'S':
			return "s";
		case 'N':
			return "n";
		default:
			return NULL;
		}
	} else {
		return NULL;
	}
}

void correct_ntsc_value(GtkWidget *entry, gpointer item)
{
	double entry_val;
	entry_val = atof(gtk_entry_get_text(GTK_ENTRY(entry)));

	if (GPOINTER_TO_INT(item) == NTSCHUE) {
		if (entry_val > 360.0)
			gtk_entry_set_text(GTK_ENTRY(entry), "360.0");
		if (entry_val < 0.0)
			gtk_entry_set_text(GTK_ENTRY(entry), "0.0");
	} else /* item == NTSCTINT */ {
		if (entry_val > 1.0)
			gtk_entry_set_text(GTK_ENTRY(entry), "1.0");
		if (entry_val < 0.0)
			gtk_entry_set_text(GTK_ENTRY(entry), "0.0");
	}
}

static void ntsc_toggle(GtkWidget *button, gpointer w)
{
	if (GTK_TOGGLE_BUTTON(button)->active) {
		gtk_widget_set_sensitive(widgets[NTSCHUE], TRUE);
		gtk_widget_set_sensitive(widgets[NTSCTINT], TRUE);
	} else {
		gtk_widget_set_sensitive(widgets[NTSCHUE], FALSE);
		gtk_widget_set_sensitive(widgets[NTSCTINT], FALSE);
	}
}

static void pal_file_toggle(GtkWidget *button, gpointer w)
{
	if (GTK_TOGGLE_BUTTON(button)->active) {
		gtk_widget_set_sensitive(widgets[PALFILE], TRUE);
		gtk_widget_set_sensitive(GTK_WIDGET(w), TRUE);
	} else {
		gtk_widget_set_sensitive(widgets[PALFILE], FALSE);
		gtk_widget_set_sensitive(GTK_WIDGET(w), FALSE);
	}
}

GtkWidget *create_video_options_page(void)
{
	GtkWidget *hbox;
	GtkWidget *vbox;
	GtkWidget *button;
	GtkWidget *button2;
	GtkWidget *entry;
	GtkWidget *lbl;
	GList *glist = NULL;

	frame = gtk_frame_new(NULL);

	vbox = gtk_vbox_new(FALSE, 5);

	glist = g_list_append(glist, "Automatically Choose");
	glist = g_list_append(glist, "X11 Renderer");
	glist = g_list_append(glist, "Differential X11 Renderer");
	glist = g_list_append(glist, "Tile-based X11 Renderer");
	glist = g_list_append(glist, "GGI Renderer");
	glist = g_list_append(glist, "W Window System Renderer");
	glist = g_list_append(glist, "No Video Output");
	hbox = create_toggled_combo("Specify Renderer", RENDERER, 150,
								glist, FALSE);
	g_list_free(glist);
	glist = NULL;
	gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

	hbox = create_toggled_entry("Scanlines   Intensity:", SCANLINES, 30);
	gtk_entry_set_text(GTK_ENTRY(widgets[SCANLINES]), "0");
	lbl = gtk_label_new("%");
	gtk_box_pack_start(GTK_BOX(hbox), lbl, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

	hbox = create_toggled_entry("Specify Window Geometry:", GEOMETRY, 70);
	gtk_entry_set_text(GTK_ENTRY(widgets[GEOMETRY]), "640x480");
	gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

	hbox = create_toggled_entry("Enlarge:", ENLARGE, 30);
	gtk_entry_set_text(GTK_ENTRY(widgets[ENLARGE]), "2");
	lbl = gtk_label_new("x");
	gtk_box_pack_start(GTK_BOX(hbox), lbl, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

	hbox = create_toggled_entry("Specify Display/Target ID:",
							DISPLAY, 125);
	gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

	glist = g_list_append(glist, "Vertical");
	glist = g_list_append(glist, "Horizontal");
	glist = g_list_append(glist, "Single-Screen");
	glist = g_list_append(glist, "None");
	hbox = create_toggled_combo("Specify Mirroring", MIRROR, 80,
								glist, FALSE);
	g_list_free(glist);
	glist = NULL;
	gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

	glist = g_list_append(glist, "loopy");
	glist = g_list_append(glist, "quor");
	glist = g_list_append(glist, "chris");
	glist = g_list_append(glist, "matt");
	glist = g_list_append(glist, "pasofami");
	glist = g_list_append(glist, "crashman");
	glist = g_list_append(glist, "mess");
	glist = g_list_append(glist, "zaphod-cv");
	glist = g_list_append(glist, "zaphod-smb");
	glist = g_list_append(glist, "vs-drmar");
	glist = g_list_append(glist, "vs-cv");
	glist = g_list_append(glist, "vs-smb");
	hbox = create_toggled_combo("Builtin Palette:", BLTINPAL, 90,
								glist, FALSE);
	g_list_free(glist);
	glist = NULL;
	gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

	hbox = gtk_hbox_new(FALSE, 3);
	toggles[PALFILE] = gtk_check_button_new_with_label("Palette File:");
	gtk_box_pack_start(GTK_BOX(hbox), toggles[PALFILE], FALSE, FALSE, 0);
	entry = gtk_entry_new();
	gtk_widget_set_sensitive(entry, FALSE);
	gtk_box_pack_start(GTK_BOX(hbox), entry, FALSE, FALSE, 0);
	widgets[PALFILE] = entry;
	button2 = gtk_button_new_with_label("Browse...");
	g_signal_connect(toggles[PALFILE], "clicked", G_CALLBACK(pal_file_toggle), button2);
	g_signal_connect(button2, "clicked", G_CALLBACK(browse_files), GINT_TO_POINTER(PALFILE));
	gtk_widget_set_sensitive(button2, FALSE);
	gtk_box_pack_start(GTK_BOX(hbox), button2, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

	hbox = gtk_hbox_new(FALSE, 3);
	toggles[NTSC] = gtk_check_button_new_with_label("NTSC Palette:");
	toggles[NTSC+1] = toggles[NTSC];
	gtk_box_pack_start(GTK_BOX(hbox), toggles[NTSC], FALSE, FALSE, 0);
	g_signal_connect(toggles[NTSC], "clicked", G_CALLBACK(ntsc_toggle), NULL);
	lbl = gtk_label_new("Hue Angle:");
	gtk_box_pack_start(GTK_BOX(hbox), lbl, FALSE, FALSE, 0);
	entry = gtk_entry_new();
	gtk_widget_set_sensitive(entry, FALSE);
	gtk_widget_set_usize(entry, 50, 20);
	gtk_entry_set_text(GTK_ENTRY(entry), "332.0");
	gtk_box_pack_start(GTK_BOX(hbox), entry, FALSE, FALSE, 0);
	widgets[NTSCHUE] = entry;
	g_signal_connect(entry, "activate", G_CALLBACK(correct_ntsc_value), GINT_TO_POINTER(NTSCHUE));
	lbl = gtk_label_new("Tint Level:");
	gtk_box_pack_start(GTK_BOX(hbox), lbl, FALSE, FALSE, 0);
	entry = gtk_entry_new();
	gtk_widget_set_sensitive(entry, FALSE);
	gtk_widget_set_usize(entry, 30, 20);
	gtk_entry_set_text(GTK_ENTRY(entry), "0.5");
	gtk_box_pack_start(GTK_BOX(hbox), entry, FALSE, FALSE, 0);
	widgets[NTSCTINT] = entry;
	g_signal_connect(entry, "activate", G_CALLBACK(correct_ntsc_value), GINT_TO_POINTER(NTSCTINT));
	gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

	button = create_toggle("Display In Root Window", DISPINROOT);
	gtk_box_pack_start(GTK_BOX(vbox), button, FALSE, FALSE, 0);

	button = create_toggle("Static Color Allocation", STATCOLOR);
	gtk_box_pack_start(GTK_BOX(vbox), button, FALSE, FALSE, 0);

	button = create_toggle("Grayscale", GRAYSCALE);
	gtk_box_pack_start(GTK_BOX(vbox), button, FALSE, FALSE, 0);

	gtk_container_add(GTK_CONTAINER(frame), vbox);

	return frame;
}
