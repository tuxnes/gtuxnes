/*
 * Copyright (C) 2000-2001  Scott Weber  <scott@scottweber.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.  Please see the file COPYING for the
 * full text of the License.
*/

#include "gtuxnes.h"

char config_file_name[513];
GtkWidget *main_window;
GtkWidget *wait_dlg;

static void popup_info_dialog(const char *msg)
{
	GtkWidget *dlg;
	GtkWidget *lbl;
	GtkWidget *button;

	dlg = gtk_dialog_new();
	lbl = gtk_label_new(msg);
	gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dlg)->vbox), lbl, TRUE, TRUE, 0);
	button = gtk_button_new_with_label("Okay");
	g_signal_connect(button, "clicked", G_CALLBACK(end_dlg), dlg);
	gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dlg)->action_area), button,
				TRUE, TRUE, 0);

	gtk_widget_show_all(dlg);
}

static gint update_wait_progress(gpointer progress)
{
	gint curr_val;

	curr_val = gtk_progress_get_value(GTK_PROGRESS(progress));
	gtk_progress_set_value(GTK_PROGRESS(progress), curr_val+1);

	curr_val++;

	if (curr_val == 100) {
		gtk_widget_destroy(wait_dlg);
	}

	return (curr_val < 100);
}

static void create_wait_dialog(void)
{
	GtkWidget *lbl;
	GtkWidget *progress;

	progress = gtk_progress_bar_new();
	lbl = gtk_label_new("Executing TuxNES...");
	wait_dlg = gtk_dialog_new();
	gtk_box_pack_start(GTK_BOX(GTK_DIALOG(wait_dlg)->action_area),
				progress, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(GTK_DIALOG(wait_dlg)->vbox), lbl,
				TRUE, TRUE, 0);
	gtk_widget_show_all(wait_dlg);
	gtk_progress_set_value(GTK_PROGRESS(progress), 0);
	gtk_timeout_add(10, update_wait_progress, progress);
}

static void cleanup(char *free_me[], int size, gboolean was_error)
{
	int j;
	if (was_error)
		popup_info_dialog("ERROR: couldn't allocate space for string\n");
	for (j = 0; j < size; j++)
		g_free(free_me[j]);
}

static void run_tuxnes( GtkWidget *w, gpointer data )
{
	int i = 0;
	int j = 0;
	int k;
	char *needs_freeing[NUM_OF_ENTRIES];
	const char *options[NUM_OF_TOGGLES+3];
	pid_t tuxnes_pid;
	gboolean alloc_error = FALSE;

	options[i++] = "tuxnes";

	if (GTK_TOGGLE_BUTTON(toggles[JOYREMAP])->active) {
		needs_freeing[j] = g_strconcat("-J",
			gtk_entry_get_text(GTK_ENTRY(widgets[JOYREMAP])),
			NULL);
		if (needs_freeing[j] == NULL) {
			alloc_error = TRUE;
			goto fail;
		}
		options[i++] = needs_freeing[j++];
	}
	if (GTK_TOGGLE_BUTTON(toggles[DISPLAY])->active) {
		needs_freeing[j] = g_strconcat("--display=",
			gtk_entry_get_text(GTK_ENTRY(widgets[DISPLAY])),
			NULL);
		if (needs_freeing[j] == NULL) {
			alloc_error = TRUE;
			goto fail;
		}
		options[i++] = needs_freeing[j++];
	}
	if (GTK_TOGGLE_BUTTON(toggles[NTSC])->active) {
		correct_ntsc_value(widgets[NTSCHUE], (gpointer) NTSCHUE);
		correct_ntsc_value(widgets[NTSCTINT], (gpointer) NTSCTINT);

		needs_freeing[j] = g_strconcat("-N",
			gtk_entry_get_text(GTK_ENTRY(widgets[NTSCHUE])),
			",",
			gtk_entry_get_text(GTK_ENTRY(widgets[NTSCTINT])),
			NULL);
		if (needs_freeing[j] == NULL) {
			alloc_error = TRUE;
			goto fail;
		}
		options[i++] = needs_freeing[j++];
	}
	if (GTK_TOGGLE_BUTTON(toggles[GEOMETRY])->active) {
		needs_freeing[j] = g_strconcat("-G",
			gtk_entry_get_text(GTK_ENTRY(widgets[GEOMETRY])),
			NULL);
		if (needs_freeing[j] == NULL) {
			alloc_error = TRUE;
			goto fail;
		}
		options[i++] = needs_freeing[j++];
	}
	if (GTK_TOGGLE_BUTTON(toggles[SCANLINES])->active) {
		needs_freeing[j] = g_strconcat("-L",
			gtk_entry_get_text(GTK_ENTRY(widgets[SCANLINES])),
			NULL);
		if (needs_freeing[j] == NULL) {
			alloc_error = TRUE;
			goto fail;
		}
		options[i++] = needs_freeing[j++];
	}
	if (GTK_TOGGLE_BUTTON(toggles[PALFILE])->active) {
		needs_freeing[j] = g_strconcat("-p",
			gtk_entry_get_text(GTK_ENTRY(widgets[PALFILE])),
			NULL);
		if (needs_freeing[j] == NULL) {
			alloc_error = TRUE;
			goto fail;
		}
		options[i++] = needs_freeing[j++];
	}
	if (GTK_TOGGLE_BUTTON(toggles[BLTINPAL])->active) {
		needs_freeing[j] = g_strconcat("-P",
			gtk_entry_get_text(GTK_ENTRY(GTK_COMBO(widgets[BLTINPAL])->entry)),
			NULL);
		if (needs_freeing[j] == NULL) {
			alloc_error = TRUE;
			goto fail;
		}
		options[i++] = needs_freeing[j++];
	}
	if (GTK_TOGGLE_BUTTON(toggles[MIRROR])->active) {
		const char *temp = translate_video_combo(MIRROR);
		if (temp == NULL) {
			goto fail;
		}
		needs_freeing[j] = g_strconcat("-m", temp, NULL);
		if (needs_freeing[j] == NULL) {
			alloc_error = TRUE;
			goto fail;
		}
		options[i++] = needs_freeing[j++];
	}
	if (GTK_TOGGLE_BUTTON(toggles[RENDERER])->active) {
		const char *temp = translate_video_combo(RENDERER);
		if (temp == NULL) {
			goto fail;
		}
		needs_freeing[j] = g_strconcat("-r", temp, NULL);
		if (needs_freeing[j] == NULL) {
			alloc_error = TRUE;
			goto fail;
		}
		options[i++] = needs_freeing[j++];
	}
	if (GTK_TOGGLE_BUTTON(toggles[MUTESOUND])->active) {
		options[i++] = "-smute";
	} else {
		if (GTK_TOGGLE_BUTTON(toggles[SNDDEV])->active) {
			needs_freeing[j] = g_strconcat("-s",
				gtk_entry_get_text(GTK_ENTRY(GTK_COMBO(widgets[SNDDEV])->entry)),
				NULL);
			if (needs_freeing[j] == NULL) {
				alloc_error = TRUE;
				goto fail;
			}
			options[i++] = needs_freeing[j++];
		}
		if (GTK_TOGGLE_BUTTON(toggles[SNDFORMAT])->active) {
			const gchar *temp = translate_sound_combo(SNDFORMAT);
			if (temp == NULL) {
				goto fail;
			}
			needs_freeing[j] = g_strconcat("-F", temp, NULL);
			if (needs_freeing[j] == NULL) {
				alloc_error = TRUE;
				goto fail;
			}
			options[i++] = needs_freeing[j++];
		}
		if (GTK_TOGGLE_BUTTON(toggles[SNDDELAY])->active) {
			needs_freeing[j] = g_strconcat("-D",
				gtk_entry_get_text(GTK_ENTRY(widgets[SNDDELAY])),
				NULL);
			if (needs_freeing[j] == NULL) {
				alloc_error = TRUE;
				goto fail;
			}
			options[i++] = needs_freeing[j++];
		}
		if (GTK_TOGGLE_BUTTON(toggles[SNDRATE])->active) {
			needs_freeing[j] = g_strconcat("-R",
				gtk_entry_get_text(GTK_ENTRY(GTK_COMBO(widgets[SNDRATE])->entry)),
				NULL);
			if (needs_freeing[j] == NULL) {
				alloc_error = TRUE;
				goto fail;
			}
			options[i++] = needs_freeing[j++];
		}
	}
	if (GTK_TOGGLE_BUTTON(toggles[MAPPER])->active) {
		needs_freeing[j] = g_strconcat("-M",
			gtk_entry_get_text(GTK_ENTRY(widgets[MAPPER])),
			NULL);
		if (needs_freeing[j] == NULL) {
			alloc_error = TRUE;
			goto fail;
		}
		options[i++] = needs_freeing[j++];
	}
	if (GTK_TOGGLE_BUTTON(toggles[GAMEGENIE])->active) {
		needs_freeing[j] = g_strconcat("-g",
			gtk_entry_get_text(GTK_ENTRY(widgets[GAMEGENIE])),
			NULL);
		if (needs_freeing[j] == NULL) {
			alloc_error = TRUE;
			goto fail;
		}
		options[i++] = needs_freeing[j++];
	}
	if (GTK_TOGGLE_BUTTON(toggles[STICKYKEYS])->active) {
		options[i++] = "-K";
	}
	if (GTK_TOGGLE_BUTTON(toggles[SWAPINPUT])->active) {
		options[i++] = "-X";
	}
	if (GTK_TOGGLE_BUTTON(toggles[JOY1])->active) {
		needs_freeing[j] = g_strconcat("-1",
			gtk_entry_get_text(GTK_ENTRY(widgets[JOY1])),
			NULL);
		if (needs_freeing[j] == NULL) {
			alloc_error = TRUE;
			goto fail;
		}
		options[i++] = needs_freeing[j++];
	}
	if (GTK_TOGGLE_BUTTON(toggles[JOY2])->active) {
		needs_freeing[j] = g_strconcat("-2",
			gtk_entry_get_text(GTK_ENTRY(widgets[JOY2])),
			NULL);
		if (needs_freeing[j] == NULL) {
			alloc_error = TRUE;
			goto fail;
		}
		options[i++] = needs_freeing[j++];
	}
	if (GTK_TOGGLE_BUTTON(toggles[IGNOREINST])->active) {
		options[i++] = "-i";
	}
	if (GTK_TOGGLE_BUTTON(toggles[DISPINROOT])->active) {
		options[i++] = "-I";
	}
	if (GTK_TOGGLE_BUTTON(toggles[STATCOLOR])->active) {
		options[i++] = "-S";
	}
	if (GTK_TOGGLE_BUTTON(toggles[GRAYSCALE])->active) {
		options[i++] = "-b";
	}
	if (GTK_TOGGLE_BUTTON(toggles[ENLARGE])->active) {
		needs_freeing[j] = g_strconcat("-E",
			gtk_entry_get_text(GTK_ENTRY(widgets[ENLARGE])),
			NULL);
		if (needs_freeing[j] == NULL) {
			alloc_error = TRUE;
			goto fail;
		}
		options[i++] = needs_freeing[j++];
	}
	if (GTK_TOGGLE_BUTTON(toggles[VERBOSE])->active) {
		options[i++] = "-v";
	}
	if (GTK_TOGGLE_BUTTON(toggles[FIXMAPPER])->active) {
		options[i++] = "-f";
	}
	if (GTK_TOGGLE_BUTTON(toggles[SHOWHEADER])->active) {
		options[i++] = "-H";
	}
	if (GTK_TOGGLE_BUTTON(toggles[DISASM])->active) {
		options[i++] = "-d";
	}
	if (GTK_TOGGLE_BUTTON(toggles[LINK])->active) {
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
			popup_info_dialog("ERROR: couldn't fork!\n");
		else
			create_wait_dialog();
	}

fail:
	cleanup(needs_freeing, j, alloc_error);
}

static void add_page(GtkWidget *book, GtkWidget *page, const gchar *title)
{
	GtkWidget *label;
	gtk_container_set_border_width(GTK_CONTAINER(page), 10);
	label = gtk_label_new(title);
	gtk_notebook_append_page (GTK_NOTEBOOK(book), page, label);
}

static gint quit_gtuxnes( GtkWidget *w, gpointer data )
{
	write_config_file();
	gtk_main_quit();
	return(FALSE);
}

int main( int argc, char *argv[] )
{
	GtkWidget *button;
	GtkWidget *notebook;
	GtkWidget *vbox;
	GtkWidget *bbox;

	gtk_init (&argc, &argv);

	main_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(main_window), PACKAGE_NAME);
	g_signal_connect(main_window, "delete_event", G_CALLBACK(quit_gtuxnes), NULL);
	gtk_container_set_border_width (GTK_CONTAINER (main_window), 10);

	vbox = gtk_vbox_new(FALSE, 5);


    /* Create the 'notebook' and add the pages to it */
	notebook = gtk_notebook_new ();
	gtk_notebook_set_tab_pos(GTK_NOTEBOOK (notebook), GTK_POS_TOP);
	gtk_box_pack_start(GTK_BOX(vbox), notebook, FALSE, FALSE, 0);

	add_page(notebook, create_general_options_page(), "General");
	add_page(notebook, create_sound_options_page(),   "Sound");
	add_page(notebook, create_video_options_page(),   "Video");
	add_page(notebook, create_input_options_page(),   "Input");
	add_page(notebook, create_debug_options_page(),   "Debug");


    /* Create the Save, Run and Quit buttons */
	bbox = gtk_hbutton_box_new();
	gtk_hbutton_box_set_spacing_default(10);
	gtk_hbutton_box_set_layout_default(GTK_BUTTONBOX_END);
/*
	button = gtk_button_new_with_label("Save Config");
	gtk_container_add(GTK_CONTAINER(bbox), button);
	g_signal_connect(button, "clicked", G_CALLBACK(write_config_file), NULL);
*/
	button = gtk_button_new_with_label("Run");
	g_signal_connect(button, "clicked", G_CALLBACK(run_tuxnes), NULL);
	gtk_container_add(GTK_CONTAINER(bbox), button);

	button = gtk_button_new_with_label("Quit");
	g_signal_connect(button, "clicked", G_CALLBACK(quit_gtuxnes), NULL);
	gtk_container_add(GTK_CONTAINER(bbox), button);

	gtk_box_pack_start(GTK_BOX(vbox), bbox, TRUE, TRUE, 0);

	gtk_container_add(GTK_CONTAINER(main_window), vbox);
	gtk_widget_show_all(main_window);

	strcpy(config_file_name, (char*) g_get_home_dir());
	strcat(config_file_name, "/.gtuxnesrc");

	read_config_file();

	gtk_main();

	return(0);
}
