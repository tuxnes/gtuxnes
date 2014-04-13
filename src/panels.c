/*
 * Copyright (C) 2000-2001  Scott Weber  <scott@scottweber.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.  Please see the file COPYING for the
 * full text of the License.
*/

#include "gtuxnes.h"

static void enable_button_toggled(GtkWidget *button, gpointer e)
{
	GtkWidget *entry;

	entry = widgets[GPOINTER_TO_INT(e)];
	if (GTK_TOGGLE_BUTTON(button)->active) {
		gtk_widget_set_sensitive(GTK_WIDGET(entry), TRUE);
	} else {
		gtk_widget_set_sensitive(GTK_WIDGET(entry), FALSE);
	}
}

GtkWidget *create_toggle(const char *name, int id)
{
	toggles[id] = gtk_check_button_new_with_label(name);

	return toggles[id];
}

GtkWidget *create_toggled_entry(const char *name, int id, gint width)
{
	GtkWidget *entry;
	GtkWidget *hbox;

	hbox = gtk_hbox_new(FALSE, 3);
	toggles[id] = gtk_check_button_new_with_label(name);
	g_signal_connect(toggles[id], "toggled", G_CALLBACK(enable_button_toggled), GINT_TO_POINTER(id));
	gtk_box_pack_start(GTK_BOX(hbox), toggles[id], FALSE, FALSE, 0);
	entry = gtk_entry_new();
	gtk_widget_set_sensitive(entry, FALSE);
	gtk_widget_set_size_request(entry, width, 20);
	gtk_box_pack_start(GTK_BOX(hbox), entry, FALSE, FALSE, 0);
	widgets[id] = entry;

	return hbox;
}

GtkWidget *create_toggled_file(const char *name, int id, gint width,
				const char *dialog_title)
{
	GtkWidget *entry;
	GtkWidget *hbox;

	hbox = gtk_hbox_new(FALSE, 3);
	toggles[id] = gtk_check_button_new_with_label(name);
	g_signal_connect(toggles[id], "toggled", G_CALLBACK(enable_button_toggled), GINT_TO_POINTER(id));
	gtk_box_pack_start(GTK_BOX(hbox), toggles[id], FALSE, FALSE, 0);
	entry = gtk_file_chooser_button_new(dialog_title, GTK_FILE_CHOOSER_ACTION_OPEN);
	gtk_widget_set_sensitive(entry, FALSE);
	gtk_widget_set_size_request(entry, width, 20);
	gtk_box_pack_start(GTK_BOX(hbox), entry, FALSE, FALSE, 0);
	widgets[id] = entry;

	return hbox;
}

GtkWidget *create_toggled_combo(const char *name, int id, gint width,
				GList *glist)
{
	GtkWidget *combo;
	GtkWidget *hbox;

	hbox = gtk_hbox_new(FALSE, 3);
	toggles[id] = gtk_check_button_new_with_label(name);
	g_signal_connect(toggles[id], "toggled", G_CALLBACK(enable_button_toggled), GINT_TO_POINTER(id));
	gtk_box_pack_start(GTK_BOX(hbox), toggles[id], FALSE, FALSE, 0);
	combo = gtk_combo_new();
	gtk_combo_set_popdown_strings(GTK_COMBO(combo), glist);
	gtk_entry_set_editable(GTK_ENTRY(GTK_COMBO(combo)->entry), FALSE);
	gtk_widget_set_sensitive(combo, FALSE);
	gtk_widget_set_size_request(combo, width, 20);
	gtk_box_pack_start(GTK_BOX(hbox), combo, FALSE, FALSE, 0);
	widgets[id] = combo;

	return hbox;
}
