/*
 * Copyright (C) 2000-2001  Scott Weber  <scott@scottweber.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.  Please see the file COPYING for the
 * full text of the License.
*/

#include "gtuxnes.h"

void end_dlg(GtkWidget *w, gpointer dlg)
{
	gtk_widget_destroy(GTK_WIDGET( dlg ));
}

GtkWidget *create_file_selection_dlg(const gchar *title)
{
	GtkWidget *temp;

	temp = gtk_file_selection_new(title);

	g_signal_connect(temp, "destroy", G_CALLBACK(end_dlg), temp);
	g_signal_connect(GTK_FILE_SELECTION(temp)->cancel_button, "clicked", G_CALLBACK(end_dlg), temp);

	/* TODO: connect help button? */

	return temp;
}

void create_file_selection_with_ok_handler(const gchar *title,
				GCallback ok_handler, int entry)
{
	GtkWidget *file_dlg;

	file_dlg = create_file_selection_dlg(title);
	gtk_file_selection_set_filename(GTK_FILE_SELECTION(file_dlg),
					gtk_entry_get_text(GTK_ENTRY(widgets[entry])) );
	g_signal_connect(GTK_FILE_SELECTION(file_dlg)->ok_button, "clicked", ok_handler, file_dlg);
	gtk_widget_show(file_dlg);
}
