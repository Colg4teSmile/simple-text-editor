#include "gap_buffer.h"

#include <stdio.h>

#include <gtk/gtk.h>

static void quit(GtkWidget *window, gpointer data){ gtk_main_quit(); }

static void update(GtkWidget *window, gpointer data)
{
    
}

static void text_editor_gui_main ()
{
    //text_buffer =  gtk_text_buffer_new(NULL);

	GtkWidget* window; 
	//GtkWidget* box;
    //GtkWidget* menubar;
    GtkWidget* view;
    GtkTextBuffer *buffer;

    // main window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "simple text editor");
    gtk_window_set_default_size(GTK_WINDOW(window), 1000, 600);
 	g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(quit), NULL);

    view = gtk_text_view_new();
    gtk_container_add(GTK_CONTAINER(window), view);
    
    //gtk_window_set_child(GTK_WINDOW (window), view);

    //box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

    /*
    menubar = gtk_menu_bar_new();
    gtk_box_pack_start(GTK_BOX(box), menubar, FALSE, FALSE, 0);
    view = gtk_text_view_new();
    gtk_box_pack_start(GTK_BOX(box), view, FALSE, FALSE, 0);

    gtk_container_add(GTK_CONTAINER(window), box);

    gtk_widget_show_all(window);
    */
    /*
      GtkWidget *window;
      GtkWidget *headbar;
      GtkWidget *view;
      GtkWidget *vbox;
      //GtkWidget *button;

      // main window
      window = gtk_application_window_new (app);
      gtk_window_set_title(GTK_WINDOW (window), "simple text editor");
      gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
      gtk_window_set_default_size (GTK_WINDOW (window), 1000, 600);

      vbox = gtk_box_new(FALSE, 0);
      view = gtk_text_view_new();
      gtk_box_pack_start(GTK_BOX(vbox), view, TRUE, TRUE, 0);

      // header bar on top of the main window
      headbar = gtk_header_bar_new();
      gtk_header_bar_set_title (GTK_HEADER_BAR (headbar), "Welcome to GTK");
      gtk_header_bar_set_show_close_button (GTK_HEADER_BAR (headbar), TRUE);

      gtk_window_set_titlebar(GTK_WINDOW(window), headbar);
      //button = gtk_button_new_with_label ("Hello World");
      //g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);
      //gtk_window_set_child (GTK_WINDOW (window), button);

      gtk_window_present (GTK_WINDOW (window));
      */
    gtk_widget_show_all(window);
}


int main(int argc, char* argv[])
{
	//init_gap_buffer();

	gtk_init(&argc, &argv);

	//GtkApplication* app = gtk_application_new (NULL, G_APPLICATION_FLAGS_NONE);

 	// main app
    text_editor_gui_main();

    gtk_main();

	return 0;
}