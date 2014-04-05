/*    
 * Copyright (C) 2000-2001  Scott Weber  <scott@scottweber.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.  Please see the file COPYING for the
 * full text of the License.
*/

#include "gtuxnes.h"

int num_opts = 0;
char config_file_name[513];
GtkWidget *main_window;
GtkWidget *wait_dlg;

static void popup_info_dialog(char *msg)
	{
	GtkWidget *dlg;
	GtkWidget *lbl;
	GtkWidget *button;

	dlg = gtk_dialog_new();
	lbl = gtk_label_new(msg);
	gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dlg)->vbox), lbl, TRUE, TRUE, 0);
	button = gtk_button_new_with_label("Okay");
	gtk_signal_connect(GTK_OBJECT(button), "clicked",
				GTK_SIGNAL_FUNC(end_dlg), dlg);
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

	if (curr_val == 100)
		{
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

static char *allocate_and_copy(char *cmdln_switch, GtkEntry *entry)
	{
	char *temp;

	temp = (char *) g_strconcat(cmdln_switch,
					gtk_entry_get_text(entry), NULL);
	return temp;
	}

static void cleanup(char *free_me[], int index[], int size, gboolean was_error)
	{
	int j;
	if (was_error)
		popup_info_dialog("ERROR: couldn't allocate space for string\n");
	for (j = 0; j < size; j++)
		g_free(free_me[index[j]]);
	}

static void run_tuxnes( GtkWidget *w, gpointer data )
	{
	int i = 1;
	int j = 0;
	int needs_freeing[NUM_OF_ENTRIES-1];
	char *options[num_opts+3];
	pid_t tuxnes_pid;

	options[0] = "tuxnes";
	options[num_opts+1] = gtk_entry_get_text(GTK_ENTRY(widgets[ROMNAME]));
	options[num_opts+2] = NULL;

	g_print("calling: tuxnes ");
	if (GTK_TOGGLE_BUTTON(toggles[JOYREMAP])->active)
		{
		g_print("-J%s ",
			gtk_entry_get_text(GTK_ENTRY(widgets[JOYREMAP])));
		options[i] = allocate_and_copy("-J", GTK_ENTRY(widgets[JOYREMAP]));
		if (options[i] == NULL)
			{
			cleanup(options, needs_freeing, j, TRUE);
			return;
			}
		needs_freeing[j] = i;
		j++;
		i++;
		}
	if (GTK_TOGGLE_BUTTON(toggles[DISPLAY])->active)
		{
		g_print("--display=%s ",
			gtk_entry_get_text(GTK_ENTRY(widgets[DISPLAY])));
		options[i] = allocate_and_copy("--display=",
					GTK_ENTRY(widgets[DISPLAY]));
		if (options[i] == NULL)
			{
			cleanup(options, needs_freeing, j, TRUE);
			return;
			}
		needs_freeing[j] = i;
		j++;
		i++;
		}		
	if (GTK_TOGGLE_BUTTON(toggles[NTSC])->active)
		{
		char *temp, *temp2;

		correct_ntsc_value(widgets[NTSCHUE], (gpointer) NTSCHUE);
		correct_ntsc_value(widgets[NTSCTINT], (gpointer) NTSCTINT);

		g_print("-N%s,%s ",
			gtk_entry_get_text(GTK_ENTRY(widgets[NTSCHUE])),
			gtk_entry_get_text(GTK_ENTRY(widgets[NTSCTINT])));
		temp = allocate_and_copy("-N",
				GTK_ENTRY(widgets[NTSCHUE]));
		if (temp == NULL)
			{
			cleanup(options, needs_freeing, j, TRUE);
			return;
			}
			
		temp2 = (char*) g_malloc(sizeof(char) * (strlen(temp)+2));
		if (temp2 == NULL)
			{
			cleanup(options, needs_freeing, j, TRUE);
			g_free(temp);
			return;
			}
		strcpy(temp2, temp);
		strcat(temp2, ",");
		g_free(temp);
		options[i] = allocate_and_copy(temp2,
				GTK_ENTRY(widgets[NTSCTINT]));
		if (options[i] == NULL)
			{
			cleanup(options, needs_freeing, j, TRUE);
			g_free(temp2);
			return;
			}
		g_free(temp2);
		needs_freeing[j] = i;
		j++;
		i++;
		}		
	if (GTK_TOGGLE_BUTTON(toggles[GEOMETRY])->active)
		{
		g_print("-G%s ",
			gtk_entry_get_text(GTK_ENTRY(widgets[GEOMETRY])));
		options[i] = allocate_and_copy("-G",
				GTK_ENTRY(widgets[GEOMETRY]));
		if (options[i] == NULL)
			{
			cleanup(options, needs_freeing, j, TRUE);
			return;
			}
		needs_freeing[j] = i;
		j++;
		i++;
		}
	if (GTK_TOGGLE_BUTTON(toggles[SCANLINES])->active)
		{
		g_print("-L%s ",
			gtk_entry_get_text(GTK_ENTRY(widgets[SCANLINES])));
		options[i] = allocate_and_copy("-L",
				GTK_ENTRY(widgets[SCANLINES]));
		if (options[i] == NULL)
			{
			cleanup(options, needs_freeing, j, TRUE);
			return;
			}
		needs_freeing[j] = i;
		j++;
		i++;
		}
	if (GTK_TOGGLE_BUTTON(toggles[PALFILE])->active)
		{
		g_print("-p%s ",
			gtk_entry_get_text(GTK_ENTRY(widgets[PALFILE])));
		options[i] = allocate_and_copy("-p",
				GTK_ENTRY(widgets[PALFILE]));
		if (options[i] == NULL)
			{
			cleanup(options, needs_freeing, j, TRUE);
			return;
			}
		needs_freeing[j] = i;
		j++;
		i++;
		}
	if (GTK_TOGGLE_BUTTON(toggles[BLTINPAL])->active)
		{
		g_print("-P%s ",
			gtk_entry_get_text(GTK_ENTRY(GTK_COMBO(widgets[BLTINPAL])->entry)));
		options[i] = allocate_and_copy("-P",
					GTK_ENTRY(GTK_COMBO(widgets[BLTINPAL])->entry));
		if (options[i] == NULL)
			{
			cleanup(options, needs_freeing, j, TRUE);
			return;
			}
		needs_freeing[j] = i;
		j++;
		i++;
		}
	if (GTK_TOGGLE_BUTTON(toggles[MIRROR])->active)
		{
		char *temp = translate_video_combo(MIRROR);
		if (temp == NULL)
			{
			cleanup(options, needs_freeing, j, TRUE);
			return;
			}
		options[i] = g_strconcat("-m", temp, NULL);
		if (options[i] == NULL)
			{
			cleanup(options, needs_freeing, j, TRUE);
			return;
			}
		g_print("-m%s ", temp);
		needs_freeing[j] = i;
		j++;
		i++;
		}
	if (GTK_TOGGLE_BUTTON(toggles[RENDERER])->active)
		{
		char *temp = translate_video_combo(RENDERER);
		if (temp == NULL)
			{
			cleanup(options, needs_freeing, j, TRUE);
			return;
			}
		options[i] = g_strconcat("-r", temp, NULL);
		if (options[i] == NULL)
			{
			cleanup(options, needs_freeing, j, TRUE);
			return;
			}
		g_print("-r%s ", temp);
		needs_freeing[j] = i;
		j++;
		i++;
		}
	if (GTK_TOGGLE_BUTTON(toggles[MUTESOUND])->active)
		{
		g_print("-smute ");
		options[i] = "-smute";
		i++;
		}
	else
		{
		if (GTK_TOGGLE_BUTTON(toggles[SNDDEV])->active)
			{
			g_print("-s%s ",
				gtk_entry_get_text(GTK_ENTRY(GTK_COMBO(widgets[SNDDEV])->entry)));
			options[i] = allocate_and_copy("-s",
						GTK_ENTRY(GTK_COMBO(widgets[SNDDEV])->entry));
			if (options[i] == NULL)
				{
				cleanup(options, needs_freeing, j, TRUE);
				return;
				}
			needs_freeing[j] = i;
			j++;
			i++;
			}
		if (GTK_TOGGLE_BUTTON(toggles[SNDFORMAT])->active)
			{
			gchar *temp = translate_sound_combo(SNDFORMAT);
			if (temp == NULL)
				{
				cleanup(options, needs_freeing, j, TRUE);
				return;
				}
			options[i] = g_strconcat("-F", temp, NULL);
			if (options[i] == NULL)
				{
				cleanup(options, needs_freeing, j, TRUE);
				return;
				}
			g_print("-F%s ", temp);
			needs_freeing[j] = i;
			j++;
			i++;
			}
		if (GTK_TOGGLE_BUTTON(toggles[SNDDELAY])->active)
			{
			g_print("-D%s ",
				gtk_entry_get_text(GTK_ENTRY(widgets[SNDDELAY])));
			options[i] = allocate_and_copy("-D", 
							GTK_ENTRY(widgets[SNDDELAY]));
			if (options[i] == NULL)
				{
				cleanup(options, needs_freeing, j, TRUE);
				return;
				}
			needs_freeing[j] = i;
			j++;
			i++;
			}
		if (GTK_TOGGLE_BUTTON(toggles[SNDRATE])->active)
			{
			g_print("-R%s ",
				gtk_entry_get_text(GTK_ENTRY(GTK_COMBO(widgets[SNDRATE])->entry)));
			options[i] = allocate_and_copy("-R",
					GTK_ENTRY(GTK_COMBO(widgets[SNDRATE])->entry));
			if (options[i] == NULL)
				{
				cleanup(options, needs_freeing, j, TRUE);
				return;
				}
			needs_freeing[j] = i;
			j++;
			i++;
			}
		}
	if (GTK_TOGGLE_BUTTON(toggles[MAPPER])->active)
		{
		g_print("-M%s ",gtk_entry_get_text(GTK_ENTRY(widgets[MAPPER])));
		options[i] = allocate_and_copy("-M",
					GTK_ENTRY(widgets[MAPPER]));
		if (options[i] == NULL)
			{
			cleanup(options, needs_freeing, j, TRUE);
			return;
			}
		needs_freeing[j] = i;
		j++;
		i++;
		}	
	if (GTK_TOGGLE_BUTTON(toggles[GAMEGENIE])->active)
		{
		g_print("-g%s ",gtk_entry_get_text(GTK_ENTRY(widgets[GAMEGENIE])));
		options[i] = allocate_and_copy("-g", 
					GTK_ENTRY(widgets[GAMEGENIE]));
		if (options[i] == NULL)
			{
			cleanup(options, needs_freeing, j, TRUE);
			return;
			}
		needs_freeing[j] = i;
		j++;
		i++;
		}	
	if (GTK_TOGGLE_BUTTON(toggles[STICKYKEYS])->active)
		{
		g_print("-K ");
		options[i] = "-K";
		i++;
		}
	if (GTK_TOGGLE_BUTTON(toggles[SWAPINPUT])->active)
		{
		g_print("-X ");
		options[i] = "-X";
		i++;
		}
	if (GTK_TOGGLE_BUTTON(toggles[JOY1])->active)
		{
		g_print("-1%s ",
			gtk_entry_get_text(GTK_ENTRY(widgets[JOY1])));
		options[i] = allocate_and_copy("-1",
				GTK_ENTRY(widgets[JOY1]));
		if (options[i] == NULL)
			{
			cleanup(options, needs_freeing, j, TRUE);
			return;
			}
		needs_freeing[j] = i;
		j++;
		i++;
		}
	if (GTK_TOGGLE_BUTTON(toggles[JOY2])->active)
		{
		g_print("-2%s ",
			gtk_entry_get_text(GTK_ENTRY(widgets[JOY2])));
		options[i] = allocate_and_copy("-2",
				GTK_ENTRY(widgets[JOY2]));
		if (options[i] == NULL)
			{
			cleanup(options, needs_freeing, j, TRUE);
			return;
			}
		needs_freeing[j] = i;
		j++;
		i++;
		}
	if (GTK_TOGGLE_BUTTON(toggles[IGNOREINST])->active)
		{
		g_print("-i ");
		options[i] = "-i";
		i++;
		}
	if (GTK_TOGGLE_BUTTON(toggles[DISPINROOT])->active)
		{
		g_print("-I ");
		options[i] = "-I";
		i++;
		}
	if (GTK_TOGGLE_BUTTON(toggles[STATCOLOR])->active)
		{
		g_print("-S ");
		options[i] = "-S";
		i++;
		}
	if (GTK_TOGGLE_BUTTON(toggles[GRAYSCALE])->active)
		{
		g_print("-b ");
		options[i] = "-b";
		i++;
		}
	if (GTK_TOGGLE_BUTTON(toggles[ENLARGE])->active)
		{
		g_print("-E%s ",
			gtk_entry_get_text(GTK_ENTRY(widgets[ENLARGE])));
		options[i] = allocate_and_copy("-E",
				GTK_ENTRY(widgets[ENLARGE]));
		if (options[i] == NULL)
			{
			cleanup(options, needs_freeing, j, TRUE);
			return;
			}
		needs_freeing[j] = i;
		j++;
		i++;
		}
	if (GTK_TOGGLE_BUTTON(toggles[VERBOSE])->active)
		{
		g_print("-v ");
		options[i] = "-v";
		i++;
		}
	if (GTK_TOGGLE_BUTTON(toggles[FIXMAPPER])->active)
		{
		g_print("-f ");
		options[i] = "-f";
		i++;
		}
	if (GTK_TOGGLE_BUTTON(toggles[SHOWHEADER])->active)
		{
		g_print("-H ");
		options[i] = "-H";
		i++;
		}
	if (GTK_TOGGLE_BUTTON(toggles[DISASM])->active)
		{
		g_print("-d ");
		options[i] = "-d";
		i++;
		}
	if (GTK_TOGGLE_BUTTON(toggles[LINK])->active)
		{
		g_print("-l ");
		options[i] = "-l";
		i++;
		}
	g_print("%s\n", gtk_entry_get_text(GTK_ENTRY(widgets[ROMNAME])));

	
	if ((tuxnes_pid = fork()) == 0)
		{
		/* TuxNES child */
		execvp("tuxnes", options); 
		exit(1);
		}
	else
		{
		/* GTuxNES Parent */
		if (tuxnes_pid < 0)
			popup_info_dialog("ERROR: coudln't fork!\n");
		else
			create_wait_dialog();

		cleanup(options, needs_freeing, j, FALSE);
		}
	}

static void add_page(GtkWidget *book, GtkWidget *page, gchar *title)
	{
	GtkWidget *label;
	gtk_container_set_border_width(GTK_CONTAINER(page), 10);
	gtk_widget_show(page);
	label = gtk_label_new(title);
	gtk_widget_show(label);
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
	gtk_window_set_title(GTK_WINDOW(main_window), "GTuxNES");
	gtk_signal_connect (GTK_OBJECT (main_window), "delete_event",
				GTK_SIGNAL_FUNC (quit_gtuxnes), NULL);
	gtk_container_set_border_width (GTK_CONTAINER (main_window), 10);
	
	vbox = gtk_vbox_new(FALSE, 5);


    /* Create the 'notebook' and add the pages to it */
	notebook = gtk_notebook_new ();
	gtk_notebook_set_tab_pos(GTK_NOTEBOOK (notebook), GTK_POS_TOP);
	gtk_box_pack_start(GTK_BOX(vbox), notebook, FALSE, FALSE, 0);
	gtk_widget_show(notebook);
    
	add_page(notebook, create_general_options_page(), "General");
	add_page(notebook, create_sound_options_page(),   "Sound");
	add_page(notebook, create_video_options_page(),   "Video");
	add_page(notebook, create_input_options_page(),   "Input");
	add_page(notebook, create_debug_options_page(),   "Debug");
      

    /* Create the Save, Run and Quit buttons */
	bbox = gtk_hbutton_box_new();
	gtk_hbutton_box_set_spacing_default(10);
	gtk_hbutton_box_set_layout_default(GTK_BUTTONBOX_END);

/* 	button = gtk_button_new_with_label("Save Config");
	gtk_container_add(GTK_CONTAINER(bbox), button);
	gtk_signal_connect(GTK_OBJECT(button), "clicked",
				GTK_SIGNAL_FUNC(write_config_file), NULL);
	gtk_widget_show(button);
*/
	button = gtk_button_new_with_label("Run");
	gtk_signal_connect(GTK_OBJECT(button), "clicked",
			       GTK_SIGNAL_FUNC(run_tuxnes), NULL);
	gtk_container_add(GTK_CONTAINER(bbox), button);
	gtk_widget_show(button);
    
	button = gtk_button_new_with_label("Quit");
	gtk_signal_connect(GTK_OBJECT(button), "clicked",
			       GTK_SIGNAL_FUNC(quit_gtuxnes), NULL);
	gtk_container_add(GTK_CONTAINER(bbox), button);
	gtk_widget_show(button);

	gtk_box_pack_start(GTK_BOX(vbox), bbox, TRUE, TRUE, 0);
	gtk_widget_show(bbox);

	gtk_container_add(GTK_CONTAINER(main_window), vbox);
	gtk_widget_show(vbox);
	gtk_widget_show(main_window);

	strcpy(config_file_name, (char*) g_get_home_dir());
	strcat(config_file_name, "/.gtuxnesrc");

	read_config_file();

	gtk_main();

	return(0);
}
