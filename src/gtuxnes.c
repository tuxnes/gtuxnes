/*
 * Copyright (C) 2000-2001  Scott Weber  <scott@scottweber.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.  Please see the file COPYING for the
 * full text of the License.
 */

#include "gtuxnes.h"

static char config_file_name[513];
static GtkWidget *main_window;

static void run_tuxnes(GtkWidget *w, gpointer data)
{
	int i = 0;
	gchar **options;
	GError *err;

	options = g_malloc0_n(NUM_OF_TOGGLES + 3, sizeof (gchar *));

	options[i++] = g_strdup("tuxnes");

	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(toggles[JOYREMAP]))) {
		options[i++] = g_strconcat("-J",
			gtk_entry_get_text(GTK_ENTRY(widgets[JOYREMAP])),
			NULL);
	}
	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(toggles[DISPLAY]))) {
		options[i++] = g_strconcat("--display=",
			gtk_entry_get_text(GTK_ENTRY(widgets[DISPLAY])),
			NULL);
	}
	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(toggles[NTSC]))) {
		correct_ntsc_value(widgets[NTSCHUE], NULL);
		correct_ntsc_value(widgets[NTSCTINT], NULL);

		options[i++] = g_strconcat("-N",
			gtk_entry_get_text(GTK_ENTRY(widgets[NTSCHUE])),
			",",
			gtk_entry_get_text(GTK_ENTRY(widgets[NTSCTINT])),
			NULL);
	}
	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(toggles[GEOMETRY]))) {
		options[i++] = g_strconcat("-G",
			gtk_entry_get_text(GTK_ENTRY(widgets[GEOMETRY])),
			NULL);
	}
	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(toggles[SCANLINES]))) {
		options[i++] = g_strconcat("-L",
			gtk_entry_get_text(GTK_ENTRY(widgets[SCANLINES])),
			NULL);
	}
	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(toggles[PALFILE]))) {
		gchar *temp = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(widgets[PALFILE]));
		if (temp != NULL) {
			options[i++] = g_strconcat("-p", temp, NULL);
			g_free(temp);
		}
	}
	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(toggles[BLTINPAL]))) {
		int active = gtk_combo_box_get_active(GTK_COMBO_BOX(widgets[BLTINPAL]));
		const char *temp = bltinpal_from_index(active);
		if (temp != NULL) {
			options[i++] = g_strconcat("-P", temp, NULL);
		}
	}
	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(toggles[MIRROR]))) {
		int active = gtk_combo_box_get_active(GTK_COMBO_BOX(widgets[MIRROR]));
		const char *temp = mirror_from_index(active);
		if (temp != NULL) {
			options[i++] = g_strconcat("-m", temp, NULL);
		}
	}
	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(toggles[RENDERER]))) {
		int active = gtk_combo_box_get_active(GTK_COMBO_BOX(widgets[RENDERER]));
		const char *temp = renderer_from_index(active);
		if (temp != NULL) {
			options[i++] = g_strconcat("-r", temp, NULL);
		}
	}
	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(toggles[MUTESOUND]))) {
		options[i++] = g_strdup("-smute");
	} else {
		if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(toggles[SNDDEV]))) {
			gchar *temp = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(widgets[SNDDEV]));
			if (temp != NULL) {
				options[i++] = g_strconcat("-s", temp, NULL);
				g_free(temp);
			}
		}
		if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(toggles[SNDFORMAT]))) {
			int active = gtk_combo_box_get_active(GTK_COMBO_BOX(widgets[SNDFORMAT]));
			const gchar *temp = sndformat_from_index(active);
			if (temp != NULL) {
				options[i++] = g_strconcat("-F", temp, NULL);
			}
		}
		if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(toggles[SNDDELAY]))) {
			options[i++] = g_strconcat("-D",
				gtk_entry_get_text(GTK_ENTRY(widgets[SNDDELAY])),
				NULL);
		}
		if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(toggles[SNDRATE]))) {
			int active = gtk_combo_box_get_active(GTK_COMBO_BOX(widgets[SNDRATE]));
			const char *temp = sndrate_from_index(active);
			if (temp != NULL) {
				options[i++] = g_strconcat("-R", temp, NULL);
			}
		}
	}
	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(toggles[MAPPER]))) {
		options[i++] = g_strconcat("-M",
			gtk_entry_get_text(GTK_ENTRY(widgets[MAPPER])),
			NULL);
	}
	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(toggles[GAMEGENIE]))) {
		options[i++] = g_strconcat("-g",
			gtk_entry_get_text(GTK_ENTRY(widgets[GAMEGENIE])),
			NULL);
	}
	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(toggles[STICKYKEYS]))) {
		options[i++] = g_strdup("-K");
	}
	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(toggles[SWAPINPUT]))) {
		options[i++] = g_strdup("-X");
	}
	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(toggles[JOY1]))) {
		gchar *temp = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(widgets[JOY1]));
		if (temp != NULL) {
			options[i++] = g_strconcat("-1", temp, NULL);
			g_free(temp);
		}
	}
	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(toggles[JOY2]))) {
		gchar *temp = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(widgets[JOY2]));
		if (temp != NULL) {
			options[i++] = g_strconcat("-2", temp, NULL);
			g_free(temp);
		}
	}
	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(toggles[IGNOREINST]))) {
		options[i++] = g_strdup("-i");
	}
	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(toggles[DISPINROOT]))) {
		options[i++] = g_strdup("-I");
	}
	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(toggles[STATCOLOR]))) {
		options[i++] = g_strdup("-S");
	}
	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(toggles[GRAYSCALE]))) {
		options[i++] = g_strdup("-b");
	}
	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(toggles[ENLARGE]))) {
		options[i++] = g_strconcat("-E",
			gtk_entry_get_text(GTK_ENTRY(widgets[ENLARGE])),
			NULL);
	}
	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(toggles[VERBOSE]))) {
		options[i++] = g_strdup("-v");
	}
	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(toggles[FIXMAPPER]))) {
		options[i++] = g_strdup("-f");
	}
	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(toggles[SHOWHEADER]))) {
		options[i++] = g_strdup("-H");
	}
	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(toggles[DISASM]))) {
		options[i++] = g_strdup("-d");
	}
	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(toggles[LINK]))) {
		options[i++] = g_strdup("-l");
	}
	{
		gchar *temp = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(widgets[ROMNAME]));
		if (temp == NULL) {
			goto fail;
		}
		options[i++] = temp;
	}

	g_printerr("calling:");
	for (i = 0; options[i] != NULL; i++)
		g_printerr(" %s", options[i]);
	g_printerr("\n");

	err = NULL;
	g_spawn_async(NULL, options, NULL, G_SPAWN_SEARCH_PATH, NULL, NULL, NULL, &err);
	if (err != NULL) {
		g_printerr("%s\n", err->message);
		g_error_free(err);
	}

fail:
	g_strfreev(options);
}

static void add_page(GtkWidget *book, GtkWidget *page, const gchar *title)
{
	GtkWidget *frame;
	GtkWidget *label;

	frame = gtk_frame_new(NULL);
	gtk_container_set_border_width(GTK_CONTAINER(frame), PAD_BORDER);
	gtk_container_add(GTK_CONTAINER(frame), page);

	label = gtk_label_new(title);
	gtk_notebook_append_page (GTK_NOTEBOOK(book), frame, label);
}

static gint quit_gtuxnes(GtkWidget *w, gpointer data)
{
	write_config_file(config_file_name);
	gtk_main_quit();
	return(FALSE);
}

int main(int argc, char *argv[])
{
	GtkWidget *button;
	GtkWidget *notebook;
	GtkWidget *vbox;
	GtkWidget *bbox;

	gtk_init (&argc, &argv);

	main_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(main_window), PACKAGE_NAME);
	g_signal_connect(main_window, "delete_event", G_CALLBACK(quit_gtuxnes), NULL);
	gtk_container_set_border_width (GTK_CONTAINER (main_window), PAD_BORDER);

	vbox = gtk_vbox_new(FALSE, PAD_BORDER);


	/* Create the 'notebook' and add the pages to it */
	notebook = gtk_notebook_new ();
	gtk_notebook_set_tab_pos(GTK_NOTEBOOK (notebook), GTK_POS_TOP);
	gtk_box_pack_start(GTK_BOX(vbox), notebook, FALSE, FALSE, 0);

	add_page(notebook, create_general_options_page(), "General");
	add_page(notebook, create_sound_options_page(),   "Sound");
	add_page(notebook, create_video_options_page(),   "Video");
	add_page(notebook, create_palette_options_page(), "Palette");
	add_page(notebook, create_input_options_page(),   "Input");
	add_page(notebook, create_debug_options_page(),   "Debug");


	/* Create the Run and Quit buttons */
	bbox = gtk_hbutton_box_new();
	gtk_box_set_spacing(GTK_BOX(bbox), PAD_BORDER);
	gtk_button_box_set_layout(GTK_BUTTON_BOX(bbox), GTK_BUTTONBOX_END);

	button = gtk_button_new_from_stock(GTK_STOCK_EXECUTE);
	g_signal_connect(button, "clicked", G_CALLBACK(run_tuxnes), NULL);
	gtk_container_add(GTK_CONTAINER(bbox), button);

	button = gtk_button_new_from_stock(GTK_STOCK_QUIT);
	g_signal_connect(button, "clicked", G_CALLBACK(quit_gtuxnes), NULL);
	gtk_container_add(GTK_CONTAINER(bbox), button);

	gtk_box_pack_start(GTK_BOX(vbox), bbox, TRUE, TRUE, 0);

	gtk_container_add(GTK_CONTAINER(main_window), vbox);
	gtk_widget_show_all(main_window);

	strcpy(config_file_name, (char *)g_get_home_dir());
	strcat(config_file_name, "/.gtuxnesrc");

	read_config_file(config_file_name);

	gtk_main();

	return(0);
}
