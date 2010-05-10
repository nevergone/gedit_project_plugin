#include "project-plugin.h"


static void ProjectOpen (BonoboUIComponent *uic, gpointer user_data, const gchar* verbname)  {
  GtkWidget * window = NULL;
  GtkWidget * dialog = NULL;
  GtkFileFilter * filter = NULL;
  int dialog_result;
  gchar * filename = NULL;
  GList * projectlist_copy;

  /* elkeszitjuk a dialogusablakot, es hozzaadjuk a szukseges filtereket */
  window = GTK_WINDOW (gedit_get_active_window ());
  dialog = gtk_file_chooser_dialog_new ("Project megnyitasa", GTK_WINDOW (window),
                                        GTK_FILE_CHOOSER_ACTION_OPEN,
										GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
										GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
										NULL);
  filter = gtk_file_filter_new();
  gtk_file_filter_set_name (filter, "gedit project file (*.gedit-prj)");
  gtk_file_filter_add_pattern (filter, "*.gedit-prj");
  gtk_file_chooser_add_filter (GTK_FILE_CHOOSER (dialog), filter);
  filter = gtk_file_filter_new();
  gtk_file_filter_set_name (filter, "All Files");
  gtk_file_filter_add_pattern (filter, "*");
  gtk_file_chooser_add_filter (GTK_FILE_CHOOSER (dialog), filter);
  dialog_result = gtk_dialog_run (GTK_DIALOG(dialog));
  switch (dialog_result)  {
    case GTK_RESPONSE_ACCEPT:
	case GTK_RESPONSE_OK:
	     filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dialog));
    default:
		 gtk_widget_destroy (dialog);
  }
  /* megvan a project-allomany, kezdodik a feldolgozas */
  projectfileparser (filename, window);
  projectlist_copy = projectlist;
  while (projectlist_copy)  {
	g_print ("***%s***\n", ((ProjectDocument*)projectlist_copy->data)->filename);
	gedit_file_new ();
	((ProjectDocument*)projectlist_copy->data)->document =  gedit_get_active_document ();
	g_return_if_fail (((ProjectDocument*)projectlist_copy->data)->document != NULL);
	gedit_document_load (((ProjectDocument*)projectlist_copy->data)->document, ((ProjectDocument*)projectlist_copy->data)->filename, NULL);
    projectlist_copy = g_list_next (projectlist_copy);
  }
  /* eltaroljuk a project informacioit */
  project_data = g_new (ProjectData, 1);
  project_data -> project_filename = g_memdup (filename, LINE_PUFFER_SIZE);
  g_free (filename);
}


static void ProjectSave (BonoboUIComponent *uic, gpointer user_data, const gchar* verbname)  {
  FILE * projectfile = NULL;
  gchar * linepuffer = NULL;
  GList * projectlist_copy = NULL;

  if (!(projectfile = fopen (project_data->project_filename, "w+")))  return;
  linepuffer = g_malloc0 (LINE_PUFFER_SIZE);
  fprintf (projectfile, "%s\n\n", PROJECT_IDENTIFY);
  projectlist_copy = projectlist;
  while (projectlist_copy)  {
    fprintf (projectfile, "%s\n", ((ProjectDocument*)projectlist_copy->data)->filename);
    projectlist_copy = g_list_next (projectlist_copy);
  }
  fclose (projectfile);
  fflush (projectfile);
  g_free (linepuffer);
}


static void ProjectClose (BonoboUIComponent *uic, gpointer user_data, const gchar* verbname)  {
  GeditMDIChild * geditmdichild;
  GList * projectlist_copy;

  projectlist_copy = projectlist; 
  while (projectlist_copy)  {
    geditmdichild = gedit_mdi_child_get_from_document (((ProjectDocument*)projectlist_copy->data)->document);
    bonobo_mdi_remove_child (&(BonoboMDI)editor_window->mdi, &(BonoboMDIChild)geditmdichild->child, FALSE);
    projectlist_copy = g_list_next (projectlist_copy);
  }
  projectlist_init ();
  menuupdate (uic);
}


static void ProjectFileSave (BonoboUIComponent *uic, gpointer user_data, const gchar* verbname)  {
  GList * projectlist_copy;
  GError * error = NULL;
  
  projectlist_copy = projectlist;
  while (projectlist_copy)  {
    gedit_document_save (((ProjectDocument*)projectlist_copy->data)->document, &error);
	if (error != NULL)  {
	  g_print ("error: %s\n", error->message);
	  g_clear_error (&error);
	}
    projectlist_copy = g_list_next (projectlist_copy);
  }
}


static void ProjectRevert (BonoboUIComponent *uic, gpointer user_data, const gchar* verbname)  {
  GList * projectlist_copy;
  
  projectlist_copy = projectlist;
  while (projectlist_copy)  {
    gedit_document_revert (((ProjectDocument*)projectlist_copy->data)->document);
    projectlist_copy = g_list_next (projectlist_copy);
  }
}


static void ProjectSettings (BonoboUIComponent *uic, gpointer user_data, const gchar* verbname)  {
  settingswindow ();
}


static void ProjectInfo (BonoboUIComponent *uic, gpointer user_data, const gchar* verbname)  {
  GtkWidget * window = NULL;
  GtkWidget * infowindow = NULL;
  GtkWidget * window_vbox = NULL;
  GtkWidget * info_label = NULL;
  GList * projectlist_copy;
  gchar * linepuffer = NULL;

  window = GTK_WINDOW (gedit_get_active_window ());
  infowindow = gtk_dialog_new_with_buttons (INFOWINDOW_TITLE, GTK_WINDOW(window), GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                            GTK_STOCK_OK, GTK_RESPONSE_OK, NULL);
  gtk_window_set_resizable (GTK_WINDOW(infowindow), FALSE);
  window_vbox = gtk_vbox_new (TRUE, 2);
  gtk_container_set_border_width (GTK_CONTAINER (window_vbox), 5);
  gtk_container_add (GTK_CONTAINER (GTK_DIALOG(infowindow)->vbox), window_vbox);  
  linepuffer = g_malloc0 (LINE_PUFFER_SIZE);
  g_sprintf (linepuffer, "%s %u", INFOWINDOW_ITEMNUMBER, g_list_length (projectlist));
  info_label = gtk_label_new (linepuffer);
  gtk_box_pack_start (GTK_BOX(window_vbox), info_label, TRUE, TRUE, 0);
  projectlist_copy = projectlist;
  while (projectlist_copy)  {
    info_label = gtk_label_new (((ProjectDocument*)projectlist_copy->data)->filename);
    gtk_box_pack_start (GTK_BOX(window_vbox), info_label, TRUE, TRUE, 0);
    projectlist_copy = g_list_next (projectlist_copy);
  }
  gtk_widget_show_all (infowindow);
  gtk_dialog_run (GTK_DIALOG(infowindow));
  gtk_widget_destroy (infowindow);
  g_free (linepuffer);
}


static void projectfileparser (const gchar * projectfilename,  GtkWidget * app_window)  {
  FILE * projectfile = NULL;
  GtkWidget * messagedialog = NULL;
  gchar * linepuffer = NULL;
  ProjectDocument * projectdocument = NULL;

  if (!(projectfile = fopen (projectfilename, "r+")))  return;
  linepuffer = g_malloc0 (LINE_PUFFER_SIZE);
  fgets (linepuffer, LINE_PUFFER_SIZE-1, projectfile);
  g_strstrip (linepuffer);
  if (g_ascii_strcasecmp (linepuffer, PROJECT_IDENTIFY))  {
    messagedialog = gtk_message_dialog_new (GTK_WINDOW(app_window), GTK_DIALOG_MODAL,
	                                        GTK_MESSAGE_ERROR, GTK_BUTTONS_OK,
											"hibas projectallomany");
	gtk_dialog_run (GTK_DIALOG(messagedialog));
	gtk_widget_destroy (messagedialog);
  }
  /* kiolvassuk a projectben szereplo allomanyneveket, felfuzzuk oket listara */
  while (!feof(projectfile))  {
    fgets (linepuffer, LINE_PUFFER_SIZE-1, projectfile);
	if (!feof(projectfile))  {
      g_strstrip (linepuffer);
      if (g_ascii_strcasecmp (linepuffer, ""))  {
	    projectdocument = g_new (ProjectDocument, 1);
		projectdocument->filename = g_strdup (linepuffer);
		projectdocument->document = NULL;
	    projectlist = g_list_append (projectlist, projectdocument);
	  }
    }
  }
  fclose (projectfile);
  g_free (linepuffer);
}


static void menuupdate (BonoboUIComponent *uic)  {
  /* ha nincs megnyitva project, letiltjuk a megfelelo menuelemeket, es forditva */
  if ((projectlist != NULL) && (gedit_mdi_get_state (editor_window) == GEDIT_STATE_NORMAL))  {
    gedit_menus_set_verb_sensitive (uic, "/commands/" PROJECT_OPEN_NAME, FALSE);
    gedit_menus_set_verb_sensitive (uic, "/commands/" PROJECT_SAVE_NAME, TRUE);
    gedit_menus_set_verb_sensitive (uic, "/commands/" PROJECT_CLOSE_NAME, TRUE);
    gedit_menus_set_verb_sensitive (uic, "/commands/" PROJECT_FILESAVE_NAME, TRUE);
    gedit_menus_set_verb_sensitive (uic, "/commands/" PROJECT_REVERT_NAME, TRUE);
    gedit_menus_set_verb_sensitive (uic, "/commands/" PROJECT_SETTINGS_NAME, TRUE);
    gedit_menus_set_verb_sensitive (uic, "/commands/" PROJECT_INFO_NAME, TRUE);
  }
  else  {
    gedit_menus_set_verb_sensitive (uic, "/commands/" PROJECT_OPEN_NAME, TRUE);
    gedit_menus_set_verb_sensitive (uic, "/commands/" PROJECT_SAVE_NAME, FALSE);
    gedit_menus_set_verb_sensitive (uic, "/commands/" PROJECT_CLOSE_NAME, FALSE);
    gedit_menus_set_verb_sensitive (uic, "/commands/" PROJECT_FILESAVE_NAME, FALSE);
    gedit_menus_set_verb_sensitive (uic, "/commands/" PROJECT_REVERT_NAME, FALSE);
    gedit_menus_set_verb_sensitive (uic, "/commands/" PROJECT_SETTINGS_NAME, FALSE);
    gedit_menus_set_verb_sensitive (uic, "/commands/" PROJECT_INFO_NAME, FALSE);

  }
}


static void projectlist_init ()  {
  GList * projectlist_copy;

  if (projectlist != NULL)  {
    projectlist_copy = projectlist;
    while (projectlist_copy)  {
      if ((((ProjectDocument*)projectlist_copy->data)->filename) != NULL)  g_free (((ProjectDocument*)projectlist_copy->data)->filename);
      if ((projectlist_copy->data) != NULL)  g_free (projectlist_copy->data);
      projectlist_copy = g_list_next (projectlist_copy);
    }
    g_list_free (projectlist);
    projectlist = NULL;
	g_free (project_data->project_filename);
	g_free (project_data);
  }
}


static void settingswindow ()  {
  g_print ("settings-file\n");
}


G_MODULE_EXPORT GeditPluginState init (GeditPlugin *plugin)  {
  gedit_debug (DEBUG_PLUGINS, "");
  plugin->private_data = NULL;
  editor_window = gedit_get_mdi ();
  return PLUGIN_OK;
}


G_MODULE_EXPORT GeditPluginState activate (GeditPlugin *plugin)  {
  GList * top_windows;

  gedit_debug (DEBUG_PLUGINS, "");
  
  /************************/
  GtkWidget * foablak = NULL;
  GtkWidget * teszt = NULL;
  
  foablak = gedit_get_active_window ();
//  teszt = gnome_app_get_dock_item_by_name (foablak, "Toolbar");
  g_print ("%s\n", gtk_window_get_title (GTK_WINDOW(foablak)));  
  
  /************************/
  
  top_windows = gedit_get_top_windows ();
  g_return_val_if_fail (top_windows != NULL, PLUGIN_ERROR);
  while (top_windows)  {
    /* menubejegyzesek hozzaadasa */
    gedit_menus_add_submenu (BONOBO_WINDOW (top_windows->data),
	                         PROJECT_MENU_PATH, PROJECT_MENU_NAME, PROJECT_MENU_LABEL);
    gedit_menus_add_menu_item (BONOBO_WINDOW (top_windows->data),
                               PROJECT_OPEN_PATH, PROJECT_OPEN_NAME,
                               PROJECT_OPEN_LABEL, PROJECT_OPEN_TIP, NULL,
                               ProjectOpen);
    gedit_menus_add_menu_item (BONOBO_WINDOW (top_windows->data),
                               PROJECT_SAVE_PATH, PROJECT_SAVE_NAME,
                               PROJECT_SAVE_LABEL, PROJECT_SAVE_TIP, NULL,
                               ProjectSave);
    gedit_menus_add_menu_item (BONOBO_WINDOW (top_windows->data),
                               PROJECT_CLOSE_PATH, PROJECT_CLOSE_NAME,
                               PROJECT_CLOSE_LABEL, PROJECT_CLOSE_TIP, NULL,
                               ProjectClose);
    gedit_menus_add_menu_item (BONOBO_WINDOW (top_windows->data),
                               PROJECT_FILESAVE_PATH, PROJECT_FILESAVE_NAME,
                               PROJECT_FILESAVE_LABEL, PROJECT_FILESAVE_TIP, NULL,
                               ProjectFileSave);
    gedit_menus_add_menu_item (BONOBO_WINDOW (top_windows->data),
                               PROJECT_REVERT_PATH, PROJECT_REVERT_NAME,
                               PROJECT_REVERT_LABEL, PROJECT_REVERT_TIP, NULL,
                               ProjectRevert);
    gedit_menus_add_menu_item (BONOBO_WINDOW (top_windows->data),
                               PROJECT_SETTINGS_PATH, PROJECT_SETTINGS_NAME,
                               PROJECT_SETTINGS_LABEL, PROJECT_SETTINGS_TIP, NULL,
                               ProjectSettings);
    gedit_menus_add_menu_item (BONOBO_WINDOW (top_windows->data),
                               PROJECT_INFO_PATH, PROJECT_INFO_NAME,
                               PROJECT_INFO_LABEL, PROJECT_INFO_TIP, NULL,
                               ProjectInfo);

    plugin -> update_ui (plugin, BONOBO_WINDOW (top_windows->data));
    top_windows = g_list_next (top_windows);	  
  }
  return PLUGIN_OK;
}


G_MODULE_EXPORT GeditPluginState update_ui (GeditPlugin *plugin, BonoboWindow *window)  {
  BonoboUIComponent *uic;

  gedit_debug (DEBUG_PLUGINS, "");
  g_return_val_if_fail (window != NULL, PLUGIN_ERROR);
  uic = gedit_get_ui_component_from_window (window);
  menuupdate (uic);
  return PLUGIN_OK;
}


G_MODULE_EXPORT GeditPluginState deactivate (GeditPlugin *plugin)  {
  gedit_menus_remove_submenu_all (PROJECT_MENU_PATH, PROJECT_MENU_NAME);
  return PLUGIN_OK;
}


G_MODULE_EXPORT GeditPluginState destroy (GeditPlugin *plugin)  {
  projectlist_init ();
  return PLUGIN_OK;  
}
