#include <stdio.h>

#include <gtk/gtk.h>

#include "gap_buffer.h"

GtkTextBuffer * buffer_text_area;
GtkTextIter* iter;

extern gap_buffer_t* gap_buf_ptr;

static void quit(GtkWidget *window, gpointer data){ gtk_main_quit(); }

static void update(void)
{
    gtk_text_buffer_set_text(GTK_TEXT_BUFFER(buffer_text_area),get_left_message(),get_left_size());
    gtk_text_buffer_get_iter_at_offset(buffer_text_area, iter, 0);
    gtk_text_buffer_insert(buffer_text_area, iter, get_right_message(), get_right_size());
    //gtk_label_set_label ( GTK_LABEL ( widget ), "ciaoooooo\n" );
    //insert_char('a');
    //gtk_text_buffer_set_text(GTK_TEXT_BUFFER(buffer_text_area),get_left_message(),get_left_size());
    //printf("ciao\n");
    //gtk_text_view_set_buffer(GTK_TEXT_VIEW(widget), get_left_message());
    //gtk_text_buffer_get_iter_at_offset(buffer_text_area, &iter, 0);
    //gtk_text_buffer_insert(buffer_text_area, &iter, "Plain text\n", -1);

    //gtk_text_view_set_buffer(GTK_TEXT_VIEW(widget), get_left_message() );
}

gboolean press_key (GtkWidget *widget, GdkEventKey *event, gpointer data);

static void text_editor_gui_main ()
{
    //text_buffer =  gtk_text_buffer_new(NULL);

    // Qui viene instanziata la finestra principale
    GtkWidget* window; 
    GtkWidget* view;
    GtkTextBuffer *buffer;
    GtkWidget* menubar;
    GtkWidget* box;

    // main window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "simple text editor");
    gtk_window_set_default_size(GTK_WINDOW(window), 1000, 600);
 	g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(quit), NULL);

    // Qui viene creato un box che contiente i vari widget della finestra, infatti la finestra
    // può contenere al massimo un widget
    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5); // non so cosa vogliano dire questi parametri

    // Qui viene creato il menubar
    menubar = gtk_menu_bar_new();
    gtk_box_pack_start(GTK_BOX(box), menubar, FALSE, FALSE, 0); // menu bar added to box


    // qui viene creato l'editor che è semplicemente un widget posto all'interno di un box
    //view = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    
    view = gtk_text_view_new();
    gtk_box_pack_end(GTK_BOX(box), view, TRUE, TRUE, 0);
    gtk_text_view_set_editable(GTK_TEXT_VIEW(view), FALSE);
    gtk_widget_add_events(view, GDK_KEY_PRESS_MASK);
    g_signal_connect (G_OBJECT (view), "key_press_event", G_CALLBACK (press_key), NULL);
    buffer_text_area = gtk_text_view_get_buffer(GTK_TEXT_VIEW(view));

    // box viene aggiunto a window
    gtk_container_add(GTK_CONTAINER(window), box);
  

  //  GtkWidget *label;

//label
//label = gtk_label_new("This is my label");

//gtk_label_set_text(GTK_LABEL (label), "I cannot use this func");

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
	init_gap_buffer();

	gtk_init(&argc, &argv);

	//GtkApplication* app = gtk_application_new (NULL, G_APPLICATION_FLAGS_NONE);

 	// main app
    text_editor_gui_main();

    gtk_main();

	return 0;
}

gboolean press_key (GtkWidget *widget, GdkEventKey *event, gpointer data) {
    insert_char('a');
    update();


    return TRUE;

    char ch;
    switch (event->keyval)
    {
        case GDK_KEY_t:
            insert_char('t');
            gtk_label_set_label ( GTK_LABEL ( widget ), get_left_message() );
            gtk_main_iteration();
            return TRUE;
            
        default:
            return TRUE;
    }


    return TRUE;
}
