/*    
 * Copyright (C) 2000-2001  Scott Weber  <scott@scottweber.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.  Please see the file COPYING for the
 * full text of the License.
 *
 * $Id: panels.c,v 1.2 2001/03/05 23:26:49 sdweber Exp $
*/

#include "gtuxnes.h"

void browse_files(GtkWidget *w, gpointer data)
	{
	if ((int)data == ROMNAME)
		create_file_selection_with_ok_handler("Choose ROM File",
					GTK_SIGNAL_FUNC(update_romname),
					ROMNAME );
	else if ((int)data == PALFILE)
		create_file_selection_with_ok_handler("Choose Palette File",
					GTK_SIGNAL_FUNC(update_palfile),
					PALFILE );
	}

void update_romname(GtkWidget *b, gpointer fs)
	{
	gtk_entry_set_text(GTK_ENTRY(widgets[ROMNAME]), 
		gtk_file_selection_get_filename(GTK_FILE_SELECTION(fs)));
	end_dlg(NULL, fs);
	}

void update_palfile(GtkWidget *b, gpointer fs)
	{
	gtk_entry_set_text(GTK_ENTRY(widgets[PALFILE]), 
		gtk_file_selection_get_filename(GTK_FILE_SELECTION(fs)));
	end_dlg(NULL, fs);
	}

void entry_edited(GtkWidget *entry, gpointer option)
	{
	/* 
	g_free();
	g_malloc();
	strcpy();
	*/
	}

void enable_button_toggled(GtkWidget *button, gpointer e)
	{
	if (GTK_TOGGLE_BUTTON(button)->active)
		{
		gtk_widget_set_sensitive(GTK_WIDGET(widgets[(int)e]),
								TRUE);
		num_opts++;
		}
	else
		{
		gtk_widget_set_sensitive(GTK_WIDGET(widgets[(int)e]),
								FALSE);
		num_opts--;
		}
	}

void button_toggled(GtkWidget *button, gpointer option)
	{
	if (GTK_TOGGLE_BUTTON(button)->active)
		{
		num_opts++;
		}
	else
		{
		num_opts--;
		}
	}

GtkWidget *create_toggle(char *name, int id)
	{
	toggles[id] = gtk_check_button_new_with_label(name);
	gtk_signal_connect(GTK_OBJECT(toggles[id]), "toggled", 
				GTK_SIGNAL_FUNC(button_toggled),
				(gpointer) id);

	return toggles[id];
	}

GtkWidget *create_toggled_entry(char *name, int id, gint width)
	{
	GtkWidget *entry;
	GtkWidget *hbox;

	hbox = gtk_hbox_new(FALSE, 3);
	toggles[id] = gtk_check_button_new_with_label(name);
	gtk_signal_connect(GTK_OBJECT(toggles[id]), "toggled", 
				GTK_SIGNAL_FUNC(enable_button_toggled), 
				(gpointer) id);
	gtk_box_pack_start(GTK_BOX(hbox), toggles[id], FALSE, FALSE, 0);
	gtk_widget_show(toggles[id]);
	entry = gtk_entry_new();
	gtk_widget_set_sensitive(entry, FALSE);
	gtk_widget_set_usize(entry, width, 20);
	gtk_signal_connect(GTK_OBJECT(entry), "activate",
				GTK_SIGNAL_FUNC(entry_edited), 
				(gpointer) id);
	gtk_box_pack_start(GTK_BOX(hbox), entry, FALSE, FALSE, 0);
	widgets[id] = entry;
	gtk_widget_show(entry);

	return hbox;
	}

GtkWidget *create_toggled_combo(char *name, int id, gint width, 
				GList *glist, gboolean editable)
	{
	GtkWidget *combo;
	GtkWidget *hbox;

	hbox = gtk_hbox_new(FALSE, 3);
	toggles[id] = gtk_check_button_new_with_label(name);
	gtk_signal_connect(GTK_OBJECT(toggles[id]), "toggled", 
				GTK_SIGNAL_FUNC(enable_button_toggled), 
				(gpointer) id);
	gtk_box_pack_start(GTK_BOX(hbox), toggles[id], FALSE, FALSE, 0);
	gtk_widget_show(toggles[id]);
	combo = gtk_combo_new();
	gtk_combo_set_popdown_strings(GTK_COMBO(combo), glist);
	gtk_entry_set_editable(GTK_ENTRY(GTK_COMBO(combo)->entry), editable);
	gtk_widget_set_sensitive(combo, FALSE);
	gtk_widget_set_usize(combo, width, 20);
	gtk_box_pack_start(GTK_BOX(hbox), combo, FALSE, FALSE, 0);
	widgets[id] = combo;
	gtk_widget_show(combo);

	return hbox;
	}
