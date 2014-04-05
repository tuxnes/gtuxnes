/*    
 * Copyright (C) 2000-2001  Scott Weber  <scott@scottweber.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.  Please see the file COPYING for the
 * full text of the License.
*/

void browse_files(GtkWidget *w, gpointer data);
void entry_edited(GtkWidget *entry, gpointer option);

GtkWidget *create_toggle(char *name, int id);
GtkWidget *create_toggled_entry(char *name, int id, gint width);
GtkWidget *create_toggled_combo(char *name, int id, gint width,
				GList *glist, gboolean editable);
