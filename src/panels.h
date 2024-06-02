// SPDX-FileCopyrightText: 2000-2001 Scott Weber <scott@scottweber.com>
// SPDX-FileCopyrightText: 2014-2024 Kyle Guinn <elyk03@gmail.com>
// SPDX-License-Identifier: GPL-2.0-or-later

void enable_button_toggled(GtkWidget *entry, gpointer e);

GtkWidget *create_toggle(const char *name, int id);
GtkWidget *create_toggled_entry(const char *name, int id, gint width);
GtkWidget *create_toggled_file(const char *name, int id, gint width, const char *dialog_title);
GtkWidget *create_toggled_combo(const char *name, gint width, const char *const list[]);

const char *renderer_from_index(int index);
const char *mirror_from_index(int index);
const char *bltinpal_from_index(int index);
const char *sndformat_from_index(int index);
const char *sndrate_from_index(int index);

void correct_ntsc_value(GtkWidget *entry, gpointer item);
