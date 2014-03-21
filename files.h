/*    
 * Copyright (C) 2000-2001  Scott Weber  <scott@scottweber.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.  Please see the file COPYING for the
 * full text of the License.
 *
 * $Id: files.h,v 1.2 2001/03/05 23:26:49 sdweber Exp $
*/

void end_dlg(GtkWidget *w, gpointer dlg);

GtkWidget *create_file_selection_dlg( gchar *title );

void create_file_selection_with_ok_handler( gchar *title, 
						GtkSignalFunc ok_handler,
						int entry );
