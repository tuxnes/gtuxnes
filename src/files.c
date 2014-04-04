/*    
 * Copyright (C) 2000-2001  Scott Weber  <scott@scottweber.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.  Please see the file COPYING for the
 * full text of the License.
 *
 * $Id: files.c,v 1.2 2001/03/05 23:26:49 sdweber Exp $
*/

#include "gtuxnes.h"

void end_dlg(GtkWidget *w, gpointer dlg)
	{
	gtk_widget_destroy(GTK_WIDGET( dlg ));
	}

GtkWidget *create_file_selection_dlg( gchar *title )
	{
	GtkWidget *temp;
	gchar *dirname;

	temp = gtk_file_selection_new(title);

	gtk_signal_connect( GTK_OBJECT(temp), "destroy",
				GTK_SIGNAL_FUNC(end_dlg), (gpointer) temp );
	gtk_signal_connect( GTK_OBJECT (GTK_FILE_SELECTION (temp)->cancel_button), "clicked",
				GTK_SIGNAL_FUNC(end_dlg), (gpointer) temp ); 
	
	/* TODO: connect help button? */

	return temp;
	}

void create_file_selection_with_ok_handler( gchar *title, 
				GtkSignalFunc ok_handler,  int entry)
	{
	GtkWidget *file_dlg;
	
	file_dlg = create_file_selection_dlg(title);
	gtk_file_selection_set_filename(GTK_FILE_SELECTION(file_dlg),
					gtk_entry_get_text(GTK_ENTRY(widgets[entry])) );
	gtk_signal_connect( GTK_OBJECT(GTK_FILE_SELECTION(file_dlg)->ok_button), "clicked",
				ok_handler, (gpointer) file_dlg );
	gtk_widget_show(file_dlg);
	}
