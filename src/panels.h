/*
 * Copyright (C) 2000-2001  Scott Weber  <scott@scottweber.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.  Please see the file COPYING for the
 * full text of the License.
*/

GtkWidget *create_toggle(const char *name, int id);
GtkWidget *create_toggled_entry(const char *name, int id, gint width);
GtkWidget *create_toggled_file(const char *name, int id, gint width,
				const char *dialog_title);
GtkWidget *create_toggled_combo(const char *name, gint width, const char *const list[]);

const char *renderer_from_index(int index);
const char *mirror_from_index(int index);
const char *bltinpal_from_index(int index);
const char *sndformat_from_index(int index);
const char *sndrate_from_index(int index);

void correct_ntsc_value(GtkWidget *entry, gpointer item);
