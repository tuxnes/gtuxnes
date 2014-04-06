/*
 * Copyright (C) 2000-2001  Scott Weber  <scott@scottweber.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.  Please see the file COPYING for the
 * full text of the License.
*/

void end_dlg(GtkWidget *w, gpointer dlg);

GtkWidget *create_file_selection_dlg(const gchar *title);

void create_file_selection_with_ok_handler(const gchar *title,
				GCallback ok_handler, int entry);
