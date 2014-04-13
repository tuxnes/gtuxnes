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

static void popup_error_dialog(const char *msg)
{
	GtkWidget *dialog;

	dialog = gtk_message_dialog_new(GTK_WINDOW(main_window),
	                                GTK_DIALOG_DESTROY_WITH_PARENT,
	                                GTK_MESSAGE_ERROR,
	                                GTK_BUTTONS_OK,
	                                msg);
	gtk_dialog_run(GTK_DIALOG(dialog));
	gtk_widget_destroy(dialog);
}

static void cleanup(char *free_me[], int size)
{
	int j;
	for (j = 0; j < size; j++)
		g_free(free_me[j]);
}

static void run_tuxnes(GtkWidget *w, gpointer data)
{
	int i = 0;
	int j = 0;
	int k;
	char *needs_freeing[NUM_OF_ENTRIES];
	const char *options[NUM_OF_TOGGLES+3];
	pid_t tuxnes_pid;

	options[i++] = "tuxnes";

	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(toggles[JOYREMAP]))) {
		needs_freeing[j] = g_strconcat("-J",
			gtk_entry_get_text(GTK_ENTRY(widgets[JOYREMAP])),
			NULL);
		options[i++] = needs_freeing[j++];
	}
	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(toggles[DISPLAY]))) {
		needs_freeing[j] = g_strconcat("--display=",
			gtk_entry_get_text(GTK_ENTRY(widgets[DISPLAY])),
			NULL);
		options[i++] = needs_freeing[j++];
	}
	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(toggles[NTSC]))) {
		correct_ntsc_value(widgets[NTSCHUE], (gpointer) NTSCHUE);
		correct_ntsc_value(widgets[NTSCTINT], (gpointer) NTSCTINT);

		needs_freeing[j] = g_strconcat("-N",
			gtk_entry_get_text(GTK_ENTRY(widgets[NTSCHUE])),
			",",
			gtk_entry_get_text(GTK_ENTRY(widgets[NTSCTINT])),
			NULL);
		options[i++] = needs_freeing[j++];
	}
	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(toggles[GEOMETRY]))) {
		needs_freeing[j] = g_strconcat("-G",
			gtk_entry_get_text(GTK_ENTRY(widgets[GEOMETRY])),
			NULL);
		options[i++] = needs_freeing[j++];
	}
	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(toggles[SCANLINES]))) {
		needs_freeing[j] = g_strconcat("-L",
			gtk_entry_get_text(GTK_ENTRY(widgets[SCANLINES])),
			NULL);
		options[i++] = needs_freeing[j++];
	}
	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(toggles[PALFILE]))) {
		gchar *temp = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(widgets[PALFILE]));
		if (temp != NULL) {
			needs_freeing[j] = g_strconcat("-p", temp, NULL);
			g_free(temp);
			options[i++] = needs_freeing[j++];
		}
	}
	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(toggles[BLTINPAL]))) {
		int active = gtk_combo_box_get_active(GTK_COMBO_BOX(widgets[BLTINPAL]));
		const char *temp = bltinpal_from_index(active);
		if (temp != NULL) {
			needs_freeing[j] = g_strconcat("-P", temp, NULL);
			options[i++] = needs_freeing[j++];
		}
	}
	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(toggles[MIRROR]))) {
		int active = gtk_combo_box_get_active(GTK_COMBO_BOX(widgets[MIRROR]));
		const char *temp = mirror_from_index(active);
		if (temp != NULL) {
			needs_freeing[j] = g_strconcat("-m", temp, NULL);
			options[i++] = needs_freeing[j++];
		}
	}
	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(toggles[RENDERER]))) {
		int active = gtk_combo_box_get_active(GTK_COMBO_BOX(widgets[RENDERER]));
		const char *temp = renderer_from_index(active);
		if (temp != NULL) {
			needs_freeing[j] = g_strconcat("-r", temp, NULL);
			options[i++] = needs_freeing[j++];
		}
	}
	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(toggles[MUTESOUND]))) {
		options[i++] = "-smute";
	} else {
		if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(toggles[SNDDEV]))) {
			gchar *temp = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(widgets[SNDDEV]));
			if (temp != NULL) {
				needs_freeing[j] = g_strconcat("-s", temp, NULL);
				g_free(temp);
				options[i++] = needs_freeing[j++];
			}
		}
		if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(toggles[SNDFORMAT]))) {
			int active = gtk_combo_box_get_active(GTK_COMBO_BOX(widgets[SNDFORMAT]));
			const gchar *temp = sndformat_from_index(active);
			if (temp != NULL) {
				needs_freeing[j] = g_strconcat("-F", temp, NULL);
				options[i++] = needs_freeing[j++];
			}
		}
		if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(toggles[SNDDELAY]))) {
			needs_freeing[j] = g_strconcat("-D",
				gtk_entry_get_text(GTK_ENTRY(widgets[SNDDELAY])),
				NULL);
			options[i++] = needs_freeing[j++];
		}
		if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(toggles[SNDRATE]))) {
			int active = gtk_combo_box_get_active(GTK_COMBO_BOX(widgets[SNDRATE]));
			const char *temp = sndrate_from_index(active);
			if (temp != NULL) {
				needs_freeing[j] = g_strconcat("-R", temp, NULL);
				options[i++] = needs_freeing[j++];
			}
		}
	}
	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(toggles[MAPPER]))) {
		needs_freeing[j] = g_strconcat("-M",
			gtk_entry_get_text(GTK_ENTRY(widgets[MAPPER])),
			NULL);
		options[i++] = needs_freeing[j++];
	}
	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(toggles[GAMEGENIE]))) {
		needs_freeing[j] = g_strconcat("-g",
			gtk_entry_get_text(GTK_ENTRY(widgets[GAMEGENIE])),
			NULL);
		options[i++] = needs_freeing[j++];
	}
	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(toggles[STICKYKEYS]))) {
		options[i++] = "-K";
	}
	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(toggles[SWAPINPUT]))) {
		options[i++] = "-X";
	}
	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(toggles[JOY1]))) {
		gchar *temp = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(widgets[JOY1]));
		if (temp != NULL) {
			needs_freeing[j] = g_strconcat("-1", temp, NULL);
			g_free(temp);
			options[i++] = needs_freeing[j++];
		}
	}
	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(toggles[JOY2]))) {
		gchar *temp = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(widgets[JOY2]));
		if (temp != NULL) {
			needs_freeing[j] = g_strconcat("-2", temp, NULL);
			g_free(temp);
			options[i++] = needs_freeing[j++];
		}
	}
	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(toggles[IGNOREINST]))) {
		options[i++] = "-i";
	}
	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(toggles[DISPINROOT]))) {
		options[i++] = "-I";
	}
	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(toggles[STATCOLOR]))) {
		options[i++] = "-S";
	}
	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(toggles[GRAYSCALE]))) {
		options[i++] = "-b";
	}
	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(toggles[ENLARGE]))) {
		needs_freeing[j] = g_strconcat("-E",
			gtk_entry_get_text(GTK_ENTRY(widgets[ENLARGE])),
			NULL);
		options[i++] = needs_freeing[j++];
	}
	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(toggles[VERBOSE]))) {
		options[i++] = "-v";
	}
	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(toggles[FIXMAPPER]))) {
		options[i++] = "-f";
	}
	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(toggles[SHOWHEADER]))) {
		options[i++] = "-H";
	}
	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(toggles[DISASM]))) {
		options[i++] = "-d";
	}
	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(toggles[LINK]))) {
		options[i++] = "-l";
	}

	needs_freeing[j] = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(widgets[ROMNAME]));
	if (needs_freeing[j] == NULL) {
		goto fail;
	}
	options[i++] = needs_freeing[j++];

	options[i++] = NULL;

	g_print("calling:");
	for (k = 0; options[k] != NULL; k++)
		g_print(" %s", options[k]);
	g_print("\n");

	if ((tuxnes_pid = fork()) == 0) {
		/* TuxNES child */
		execvp(options[0], (char *const *)options);
		exit(1);
	} else {
		/* GTuxNES Parent */
		if (tuxnes_pid < 0)
			popup_error_dialog("Couldn't fork!");
	}

fail:
	cleanup(needs_freeing, j);
}

static void add_page(GtkWidget *book, GtkWidget *page, const gchar *title)
{
	GtkWidget *label;
	gtk_container_set_border_width(GTK_CONTAINER(page), PAD_BORDER);
	label = gtk_label_new(title);
	gtk_notebook_append_page (GTK_NOTEBOOK(book), page, label);
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

	button = gtk_button_new_with_label("Run");
	g_signal_connect(button, "clicked", G_CALLBACK(run_tuxnes), NULL);
	gtk_container_add(GTK_CONTAINER(bbox), button);

	button = gtk_button_new_with_label("Quit");
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
