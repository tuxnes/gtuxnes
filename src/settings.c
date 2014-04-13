/*
 * Copyright (C) 2000-2001  Scott Weber  <scott@scottweber.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.  Please see the file COPYING for the
 * full text of the License.
 */

/*
 * Config File Format:
 *   Line 1: /full/path/to/rom
 *   Line X: KEY0000000[=VALUE]
 *
 *  All keys are exactly 10 characters long (padded with '0's if necessary).
 *  A key with no value is assumed to have the value 1 or 'on'.  A key which
 *  does not appear in the file is assumed to have the value 0 or 'off'.
 */

#include "gtuxnes.h"

static const char *const option_names[NUM_OF_TOGGLES] = {
	"VERBOSE000","MAPPERNUM0","GAMEGENIE0","SOUNDDEV00","SNDFORMAT0","SOUNDRATE0","SOUNDDELAY",
	"RENDERER00","MIRROR0000","BUILTINPAL","PALFILE000","GEOMETRY00","SCANLINES0","ENLARGE000",
	"JOY1000000","JOY2000000","DISPLAY000","JOYREMAP00","NTSCHUE000","NTSCTINT00","FIXMAPPER0",
	"SHOWHEADER","DISASM0000","LINK000000","MUTESOUND0","DISPINROOT","STATCOLOR0","GRAYSCALE0",
	"STICKYKEYS","SWAPINPUT0","IGNOREINST"
};

static int read_int(const char *str, int otherwise)
{
	int i;
	char *end;

	i = (int)g_ascii_strtoll(str, &end, 10);
	return (end != str) ? i : otherwise;
}

void read_config_file(const char *filename)
{
	gchar *raw_data;
	gchar **lines, **line;

	if (!g_file_get_contents(filename, &raw_data, NULL, NULL))
		return;

	lines = g_strsplit(raw_data, "\n", 0);
	g_free(raw_data);

	line = lines;
	if (*line != NULL)
		gtk_file_chooser_set_filename(GTK_FILE_CHOOSER(widgets[ROMNAME]), *line++);

	while (*line != NULL) {
		gchar *key = *line++;
		gchar *value = NULL;
		size_t len = strlen(key);
		int toggle_id;

		if (len < 10)
			break;
		else if (len > 10) {
			if (key[10] != '=')
				break;
			key[10] = '\0';
			value = &key[11];
		}

		for(toggle_id = 0; toggle_id < NUM_OF_TOGGLES; ++toggle_id)
			if (strcmp(key, option_names[toggle_id]) == 0)
				goto found;
		break;
found:

		if (toggle_id == NTSCHUE) {
			gtk_widget_set_sensitive(widgets[NTSCHUE], TRUE);
			gtk_widget_set_sensitive(widgets[NTSCTINT], TRUE);
			gtk_entry_set_text(GTK_ENTRY(widgets[NTSCHUE]), value);

			if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(toggles[NTSC])))
				continue;
			else
				toggle_id = NTSC;
		} else if (toggle_id == NTSCTINT) {
			gtk_widget_set_sensitive(widgets[NTSCHUE], TRUE);
			gtk_widget_set_sensitive(widgets[NTSCTINT], TRUE);
			gtk_entry_set_text(GTK_ENTRY(widgets[NTSCTINT]), value);

			if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(toggles[NTSC])))
				continue;
			else
				toggle_id = NTSC;
		}

		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(toggles[toggle_id]), TRUE);
		if (toggle_id > 0 && toggle_id < NUM_OF_ENTRIES) {
			gtk_widget_set_sensitive(widgets[toggle_id], TRUE);
			if (value != NULL) {
				if (GTK_IS_COMBO_BOX_TEXT(widgets[toggle_id])) {
					int active = read_int(value, -1);
					gtk_combo_box_set_active(GTK_COMBO_BOX(widgets[toggle_id]), active);
				} else if (GTK_IS_FILE_CHOOSER_BUTTON(widgets[toggle_id])) {
					gtk_file_chooser_set_filename(GTK_FILE_CHOOSER(widgets[toggle_id]), value);
				} else if (GTK_IS_ENTRY(widgets[toggle_id])) {
					gtk_entry_set_text(GTK_ENTRY(widgets[toggle_id]), value);
				}
			}
		}
	}

	g_strfreev(lines);
}

void write_config_file(const char *filename)
{
	FILE *config_file;
	int i;
	gchar *value;

	config_file = fopen(filename, "w");

	if (config_file == NULL) {
		g_print("Error: Could not open '%s' for writing.\n"
			"Changes will not be saved.\n", filename);
		return;
	}

	value = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(widgets[ROMNAME]));
	if (value != NULL) {
		fprintf(config_file, "%s\n", value);
		g_free(value);

		for (i = 0; i < NUM_OF_TOGGLES; ++i) {
			if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(toggles[i]))) {
				fprintf(config_file, "%s", option_names[i]);
				if (i > 0 && i < NUM_OF_ENTRIES) {
					if (GTK_IS_COMBO_BOX_TEXT(widgets[i])) {
						fprintf(config_file, "=%d",
								gtk_combo_box_get_active(GTK_COMBO_BOX(widgets[i]))
							);
					} else if (GTK_IS_FILE_CHOOSER_BUTTON(widgets[i])) {
						value = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(widgets[i]));
						if (value != NULL) {
							fprintf(config_file, "=%s", value);
							g_free(value);
						}
					} else if (GTK_IS_ENTRY(widgets[i])) {
						fprintf(config_file, "=%s",
								gtk_entry_get_text(GTK_ENTRY(widgets[i]))
							);
					}
				}
				fprintf(config_file, "\n");
			}
		}
	}

	fclose(config_file);
}
