// SPDX-FileCopyrightText: 2000-2001 Scott Weber <scott@scottweber.com>
// SPDX-FileCopyrightText: 2014-2023 Kyle Guinn <elyk03@gmail.com>
// SPDX-License-Identifier: GPL-1.0-or-later

#include "gtuxnes.h"

void enable_button_toggled(GtkWidget *entry, gpointer e)
{
	gboolean active;

	active = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(e));
	gtk_widget_set_sensitive(entry, active);
}

GtkWidget *create_toggle(const char *name, int id)
{
	toggles[id] = gtk_check_button_new_with_label(name);

	return toggles[id];
}

GtkWidget *create_toggled_entry(const char *name, int id, gint width)
{
	GtkWidget *hbox;
	GtkWidget *toggle;
	GtkWidget *entry;

	hbox = gtk_hbox_new(FALSE, PAD_SPACE);

	toggle = gtk_check_button_new_with_label(name);
	gtk_box_pack_start(GTK_BOX(hbox), toggle, FALSE, FALSE, 0);
	toggles[id] = toggle;

	entry = gtk_entry_new();
	gtk_widget_set_sensitive(entry, FALSE);
	g_signal_connect_swapped(toggle, "toggled", G_CALLBACK(enable_button_toggled), entry);
	gtk_entry_set_width_chars(GTK_ENTRY(entry), width);
	gtk_box_pack_start(GTK_BOX(hbox), entry, FALSE, FALSE, 0);
	widgets[id] = entry;

	return hbox;
}

GtkWidget *create_toggled_file(const char *name, int id, gint width, const char *dialog_title)
{
	GtkWidget *hbox;
	GtkWidget *toggle;
	GtkWidget *entry;

	hbox = gtk_hbox_new(FALSE, PAD_SPACE);

	toggle = gtk_check_button_new_with_label(name);
	gtk_box_pack_start(GTK_BOX(hbox), toggle, FALSE, FALSE, 0);
	toggles[id] = toggle;

	entry = gtk_file_chooser_button_new(dialog_title, GTK_FILE_CHOOSER_ACTION_OPEN);
	gtk_widget_set_sensitive(entry, FALSE);
	g_signal_connect_swapped(toggle, "toggled", G_CALLBACK(enable_button_toggled), entry);
	gtk_file_chooser_button_set_width_chars(GTK_FILE_CHOOSER_BUTTON(entry), width);
	gtk_box_pack_start(GTK_BOX(hbox), entry, FALSE, FALSE, 0);
	widgets[id] = entry;

	return hbox;
}

GtkWidget *create_toggled_combo(const char *name, int id, const char *const list[])
{
	GtkWidget *hbox;
	GtkWidget *toggle;
	GtkWidget *entry;

	hbox = gtk_hbox_new(FALSE, PAD_SPACE);

	toggle = gtk_check_button_new_with_label(name);
	gtk_box_pack_start(GTK_BOX(hbox), toggle, FALSE, FALSE, 0);
	toggles[id] = toggle;

	entry = gtk_combo_box_text_new();
	gtk_widget_set_sensitive(entry, FALSE);
	g_signal_connect_swapped(toggle, "toggled", G_CALLBACK(enable_button_toggled), entry);
	while (*list != NULL) {
		gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(entry), *list++);
	}
	gtk_box_pack_start(GTK_BOX(hbox), entry, FALSE, FALSE, 0);
	widgets[id] = entry;

	return hbox;
}
