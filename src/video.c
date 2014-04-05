/*    
 * Copyright (C) 2000-2001  Scott Weber  <scott@scottweber.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.  Please see the file COPYING for the
 * full text of the License.
*/

#include "gtuxnes.h"

gchar *translate_video_combo(int box)
	{
	char *combo_text;
	combo_text = gtk_entry_get_text(GTK_ENTRY(GTK_COMBO(widgets[box])->entry));
	if (box == RENDERER)
		{
		switch(combo_text[0])
			{
			case 'A':
				return "auto";
				break;
			case 'X':
				return "x11";
				break;
			case 'D':
				return "diff";
				break;
			case 'T':
				return "old";
				break;
			case 'G':
				return "ggi";
				break;
			case 'W':
				return "w";
				break;
			case 'N':
				return "none";
				break;
			default:
				return NULL;
				break;
			}
		}
	else if (box == MIRROR)
		{
		switch(combo_text[0])
			{
			case 'V':
				return "v";
				break;
			case 'H':
				return "h";
				break;
			case 'S':
				return "s";
				break;
			case 'N':
				return "n";
				break;
			default:
				return NULL;
				break;
			}
		}
	else
		return NULL;
	}

void correct_ntsc_value(GtkWidget *entry, gpointer item)
	{
	double entry_val;
	entry_val = atof(gtk_entry_get_text(GTK_ENTRY(entry)));
	
	if ((intptr_t)item == NTSCHUE)
		{
		if (entry_val > 360.0)
			gtk_entry_set_text(GTK_ENTRY(entry), "360.0");
		if (entry_val < 0.0)
			gtk_entry_set_text(GTK_ENTRY(entry), "0.0");
		}
	else /* item == NTSCTINT */
		{
		if (entry_val > 1.0)
			gtk_entry_set_text(GTK_ENTRY(entry), "1.0");
		if (entry_val < 0.0)
			gtk_entry_set_text(GTK_ENTRY(entry), "0.0");
		}
	}

static void ntsc_toggle(GtkWidget *button, gpointer w)
	{
	if (GTK_TOGGLE_BUTTON(button)->active)
		{
		gtk_widget_set_sensitive(widgets[NTSCHUE], TRUE);
		gtk_widget_set_sensitive(widgets[NTSCTINT], TRUE);
		num_opts++;
		}
	else
		{
		gtk_widget_set_sensitive(widgets[NTSCHUE], FALSE);
		gtk_widget_set_sensitive(widgets[NTSCTINT], FALSE);
		num_opts--;
		}
	}
	
static void pal_file_toggle(GtkWidget *button, gpointer w)
	{
	if (GTK_TOGGLE_BUTTON(button)->active)
		{
		gtk_widget_set_sensitive(widgets[PALFILE], TRUE);
		gtk_widget_set_sensitive(GTK_WIDGET(w), TRUE);
		num_opts++;
		}
	else
		{
		gtk_widget_set_sensitive(widgets[PALFILE], FALSE);
		gtk_widget_set_sensitive(GTK_WIDGET(w), FALSE);
		num_opts--;
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
	gtk_widget_show(hbox);

	hbox = create_toggled_entry("Scanlines   Intensity:", SCANLINES, 30);
	gtk_entry_set_text(GTK_ENTRY(widgets[SCANLINES]), "0");
	lbl = gtk_label_new("%");
	gtk_box_pack_start(GTK_BOX(hbox), lbl, FALSE, FALSE, 0);
	gtk_widget_show(lbl);
	gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);
	gtk_widget_show(hbox);

	hbox = create_toggled_entry("Specify Window Geometry:", GEOMETRY, 70);
	gtk_entry_set_text(GTK_ENTRY(widgets[GEOMETRY]), "640x480");
	gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);
	gtk_widget_show(hbox);
	
	hbox = create_toggled_entry("Enlarge:", ENLARGE, 30);
	gtk_entry_set_text(GTK_ENTRY(widgets[ENLARGE]), "2");
	lbl = gtk_label_new("x");
	gtk_box_pack_start(GTK_BOX(hbox), lbl, FALSE, FALSE, 0);
	gtk_widget_show(lbl);
	gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);
	gtk_widget_show(hbox);

	hbox = create_toggled_entry("Specify Display/Target ID:",
							DISPLAY, 125);
	gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);
	gtk_widget_show(hbox);

	glist = g_list_append(glist, "Vertical");
	glist = g_list_append(glist, "Horizontal");
	glist = g_list_append(glist, "Single-Screen");
	glist = g_list_append(glist, "None");
	hbox = create_toggled_combo("Specify Mirroring", MIRROR, 80, 
								glist, FALSE);
	g_list_free(glist);
	glist = NULL;
	gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);
	gtk_widget_show(hbox);
	
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
	gtk_widget_show(hbox);

	hbox = gtk_hbox_new(FALSE, 3);
	toggles[PALFILE] = gtk_check_button_new_with_label("Palette File:");
	gtk_box_pack_start(GTK_BOX(hbox), toggles[PALFILE], FALSE, FALSE, 0);
	gtk_widget_show(toggles[PALFILE]);
	entry = gtk_entry_new();
	gtk_widget_set_sensitive(entry, FALSE);
	gtk_box_pack_start(GTK_BOX(hbox), entry, FALSE, FALSE, 0);
	widgets[PALFILE] = entry;
	gtk_widget_show(entry);
	button2 = gtk_button_new_with_label("Browse...");
	gtk_signal_connect(GTK_OBJECT(toggles[PALFILE]), "clicked",
				GTK_SIGNAL_FUNC(pal_file_toggle),
				(gpointer) button2);
	gtk_signal_connect(GTK_OBJECT(button2), "clicked",
				GTK_SIGNAL_FUNC(browse_files), 
				(gpointer) PALFILE);
	gtk_widget_set_sensitive(button2, FALSE);
	gtk_box_pack_start(GTK_BOX(hbox), button2, FALSE, FALSE, 0);
	gtk_widget_show(button2);
	gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);
	gtk_widget_show(hbox);

	hbox = gtk_hbox_new(FALSE, 3);
	toggles[NTSC] = gtk_check_button_new_with_label("NTSC Palette:");
	toggles[NTSC+1] = toggles[NTSC];
	gtk_box_pack_start(GTK_BOX(hbox), toggles[NTSC], FALSE, FALSE, 0);
	gtk_signal_connect(GTK_OBJECT(toggles[NTSC]), "clicked",
				GTK_SIGNAL_FUNC(ntsc_toggle),
				(gpointer) NULL);
	gtk_widget_show(toggles[NTSC]);
	lbl = gtk_label_new("Hue Angle:");
	gtk_box_pack_start(GTK_BOX(hbox), lbl, FALSE, FALSE, 0);
	gtk_widget_show(lbl);
	entry = gtk_entry_new();
	gtk_widget_set_sensitive(entry, FALSE);
	gtk_widget_set_usize(entry, 50, 20);
	gtk_entry_set_text(GTK_ENTRY(entry), "332.0");
	gtk_box_pack_start(GTK_BOX(hbox), entry, FALSE, FALSE, 0);
	widgets[NTSCHUE] = entry;
	gtk_signal_connect(GTK_OBJECT(entry), "activate",
				GTK_SIGNAL_FUNC(correct_ntsc_value),
				(gpointer) NTSCHUE);
	gtk_widget_show(entry);
	lbl = gtk_label_new("Tint Level:");
	gtk_box_pack_start(GTK_BOX(hbox), lbl, FALSE, FALSE, 0);
	gtk_widget_show(lbl);
	entry = gtk_entry_new();
	gtk_widget_set_sensitive(entry, FALSE);
	gtk_widget_set_usize(entry, 30, 20);
	gtk_entry_set_text(GTK_ENTRY(entry), "0.5");
	gtk_box_pack_start(GTK_BOX(hbox), entry, FALSE, FALSE, 0);
	widgets[NTSCTINT] = entry;
	gtk_signal_connect(GTK_OBJECT(entry), "activate",
				GTK_SIGNAL_FUNC(correct_ntsc_value),
				(gpointer) NTSCTINT);
	gtk_widget_show(entry);
	gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);
	gtk_widget_show(hbox);

	button = create_toggle("Display In Root Window", DISPINROOT);
	gtk_box_pack_start(GTK_BOX(vbox), button, FALSE, FALSE, 0);
	gtk_widget_show(button);

	button = create_toggle("Static Color Allocation", STATCOLOR);
	gtk_box_pack_start(GTK_BOX(vbox), button, FALSE, FALSE, 0);
	gtk_widget_show(button);

	button = create_toggle("Grayscale", GRAYSCALE);
	gtk_box_pack_start(GTK_BOX(vbox), button, FALSE, FALSE, 0);
	gtk_widget_show(button);

	gtk_container_add(GTK_CONTAINER(frame), vbox);
	gtk_widget_show(vbox);
	
	return frame;
	}

