#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <glib/gutils.h>
#include <glib/gi18n.h>
#include <gedit/gedit2.h>
#include <gedit/gedit-menus.h>
#include <gedit/gedit-plugin.h>
#include <gedit/gedit-debug.h>
#include <gedit/gedit-mdi-child.h>


/* a keszitett menubejegyzesek azonositoi es adatai */

#define PROJECT_MENU_LABEL				N_("Projects")
#define PROJECT_MENU_PATH				"/menu/File/FileOps_2/"
#define PROJECT_MENU_NAME				"ProjectMenu"

#define PROJECT_OPEN_LABEL				N_("Open project")
#define PROJECT_OPEN_PATH				"/menu/File/FileOps_2/ProjectMenu/"
#define PROJECT_OPEN_NAME				"ProjectOpen"
#define PROJECT_OPEN_TIP				N_("Open project")

#define PROJECT_SAVE_LABEL				N_("Save project")
#define PROJECT_SAVE_PATH				"/menu/File/FileOps_2/ProjectMenu/"
#define PROJECT_SAVE_NAME				"ProjectSave"
#define PROJECT_SAVE_TIP				N_("Save project")

#define PROJECT_CLOSE_LABEL				N_("Close project")
#define PROJECT_CLOSE_PATH				"/menu/File/FileOps_2/ProjectMenu/"
#define PROJECT_CLOSE_NAME				"ProjectClose"
#define PROJECT_CLOSE_TIP				N_("Close project")

#define PROJECT_FILESAVE_LABEL			N_("Project file save")
#define PROJECT_FILESAVE_PATH			"/menu/File/FileOps_2/ProjectMenu/"
#define PROJECT_FILESAVE_NAME			"ProjectFileSave"
#define PROJECT_FILESAVE_TIP			N_("Project file save")

#define PROJECT_REVERT_LABEL			N_("Revert project")
#define PROJECT_REVERT_PATH				"/menu/File/FileOps_2/ProjectMenu/"
#define PROJECT_REVERT_NAME				"ProjectRevert"
#define PROJECT_REVERT_TIP				N_("Revert project")

#define PROJECT_SETTINGS_LABEL			N_("Project settings")
#define PROJECT_SETTINGS_PATH			"/menu/File/FileOps_2/ProjectMenu/"
#define PROJECT_SETTINGS_NAME			"ProjectSettings"
#define PROJECT_SETTINGS_TIP			N_("Project settings (add/remove file, etc.)")

#define PROJECT_INFO_LABEL				N_("Project information")
#define PROJECT_INFO_PATH				"/menu/File/FileOps_2/ProjectMenu/"
#define PROJECT_INFO_NAME				"ProjectInfo"
#define PROJECT_INFO_TIP				N_("Project information")

#define PROJECT_IDENTIFY				"[gedit project file]"

#define INFOWINDOW_TITLE				N_("Project Information")
#define INFOWINDOW_ITEMNUMBER			N_("Number of project files:")

#define SETTINGSWINDOW_TITLE			N_("settings")
#define SETTINGSWINDOW_READONLY			N_("Read-only project")
#define SETTINGSWINDOW_PROJECTNAME		N_("Project name:")

#define LINE_PUFFER_SIZE				5120

/* a projectben szereplo allomanyok adatainak tarolasara szolgalo struktura */
typedef struct  {
  gchar * filename;
  GeditDocument * document;
} ProjectDocument;

/* a project adatainak tarolasara szolgalo struktura */
typedef struct  {
  gchar * project_filename;
  gchar * project_name;
} ProjectData;

static GeditMDI * editor_window;
static GList * projectlist;
static ProjectData * project_data;


static void ProjectOpen (BonoboUIComponent *uic, gpointer user_data, const gchar* verbname);
static void ProjectSave (BonoboUIComponent *uic, gpointer user_data, const gchar* verbname);
static void ProjectClose (BonoboUIComponent *uic, gpointer user_data, const gchar* verbname);
static void ProjectFileSave (BonoboUIComponent *uic, gpointer user_data, const gchar* verbname);
static void ProjectRevert (BonoboUIComponent *uic, gpointer user_data, const gchar* verbname);
static void ProjectSettings (BonoboUIComponent *uic, gpointer user_data, const gchar* verbname);
static void ProjectInfo (BonoboUIComponent *uic, gpointer user_data, const gchar* verbname);

static void projectfileparser (const gchar * projectfilename, GtkWidget * app_window);
static void menuupdate (BonoboUIComponent *uic);
static void projectlist_init ();
static void settingswindow ();

G_MODULE_EXPORT GeditPluginState init (GeditPlugin *plugin);
G_MODULE_EXPORT GeditPluginState activate (GeditPlugin *plugin);
G_MODULE_EXPORT GeditPluginState update_ui (GeditPlugin *plugin, BonoboWindow *window);
G_MODULE_EXPORT GeditPluginState deactivate (GeditPlugin *plugin);
G_MODULE_EXPORT GeditPluginState destroy (GeditPlugin *plugin);
