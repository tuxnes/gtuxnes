/*
 * Copyright (C) 2000-2001  Scott Weber  <scott@scottweber.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.  Please see the file COPYING for the
 * full text of the License.
*/

/* Config File Format:
 *   Line 1: /full/path/to/rom
 *   Line X: KEY0000000[=VALUE]
 *
 *  All keys are exactly 10 characters long (padded with '0's if necessary).
 *  A key with no value is assumed to have the value 1 or 'on'.  A key which
 *  does not appear in the file is assumed to have the value 0 or 'off'.
*/

#include "gtuxnes.h"

const char *option_names[NUM_OF_TOGGLES] = {
	"VERBOSE000","MAPPERNUM0","GAMEGENIE0","SOUNDDEV00","SNDFORMAT0","SOUNDRATE0","SOUNDDELAY",
	"RENDERER00","MIRROR0000","BUILTINPAL","PALFILE000","GEOMETRY00","SCANLINES0","ENLARGE000",
	"JOY1000000","JOY2000000","DISPLAY000","JOYREMAP00","NTSCHUE000","NTSCTINT00","FIXMAPPER0",
	"SHOWHEADER","DISASM0000","LINK000000","MUTESOUND0","DISPINROOT","STATCOLOR0","GRAYSCALE0",
	"STICKYKEYS","SWAPINPUT0","IGNOREINST"
};


void read_config_file(void)
{
	gchar *raw_data;
	gchar **lines, **line;

	if (!g_file_get_contents(config_file_name, &raw_data, NULL, NULL))
		return;

	lines = g_strsplit(raw_data, "\n", 0);
	g_free(raw_data);

	line = lines;
	if (*line != NULL)
		gtk_entry_set_text(GTK_ENTRY(widgets[ROMNAME]), *line++);

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

			if (GTK_TOGGLE_BUTTON(toggles[NTSC])->active == TRUE)
				continue;
			else
				toggle_id = NTSC;
		} else if (toggle_id == NTSCTINT) {
			gtk_widget_set_sensitive(widgets[NTSCHUE], TRUE);
			gtk_widget_set_sensitive(widgets[NTSCTINT], TRUE);
			gtk_entry_set_text(GTK_ENTRY(widgets[NTSCTINT]), value);

			if (GTK_TOGGLE_BUTTON(toggles[NTSC])->active == TRUE)
				continue;
			else
				toggle_id = NTSC;
		}

		GTK_TOGGLE_BUTTON(toggles[toggle_id])->active = TRUE;
		if (toggle_id > 0 && toggle_id < NUM_OF_ENTRIES) {
			gtk_widget_set_sensitive(widgets[toggle_id], TRUE);
			if (value != NULL) {
				if (GTK_IS_COMBO(widgets[toggle_id]))
					gtk_entry_set_text(GTK_ENTRY(GTK_COMBO(widgets[toggle_id])->entry), value);
				else
					gtk_entry_set_text(GTK_ENTRY(widgets[toggle_id]), value);
			}
		}
	}

	g_strfreev(lines);
}

void write_config_file(void)
{
	FILE *config_file;
	int i;

	config_file = fopen(config_file_name, "w");

	if (config_file == NULL) {
		g_print("Error: Could not open '%s' for writing.\n"
			"Changes will not be saved.\n", config_file_name);
		return;
	}

	fprintf(config_file, "%s\n", gtk_entry_get_text(GTK_ENTRY(widgets[ROMNAME])));

	i = 0;
	while (i < NUM_OF_TOGGLES) {
		if (GTK_TOGGLE_BUTTON(toggles[i])->active == TRUE) {
			fprintf(config_file, "%s", option_names[i]);
			if (i < NUM_OF_ENTRIES && i > 0) {
				fprintf(config_file, "=");
				if (GTK_IS_COMBO(widgets[i]))
					fprintf(config_file, "%s",
							gtk_entry_get_text(GTK_ENTRY(GTK_COMBO(widgets[i])->entry))
						);
				else
					fprintf(config_file, "%s",
							gtk_entry_get_text(GTK_ENTRY(widgets[i]))
						);
			}
			fprintf(config_file, "\n");
		}
		i++;
	}

	fclose(config_file);
}
