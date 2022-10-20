#include <gtk/gtk.h>

#include "gap_buffer.h"
#include "gui.h"

static GtkTextBuffer* buffer_text_area;
static GtkTextIter iter;
static GtkWidget* window; 
static GtkWidget* view;
static GtkTextBuffer *buffer;
static GtkWidget* menubar;
static GtkWidget* box;
static GtkTextMark* mark;

static gint position;

static void quit(GtkWidget *window, gpointer data)
{ 
	gtk_main_quit(); 
}

static void update(void)
{
    gtk_text_buffer_set_text(GTK_TEXT_BUFFER(buffer_text_area),get_left_message(),get_left_size());
    gtk_text_buffer_get_iter_at_offset(buffer_text_area, &iter, 0);
    gtk_text_buffer_insert(buffer_text_area, &iter, get_right_message(), get_right_size());
}

static gboolean press_key (GtkWidget *widget, GdkEventKey *event, gpointer data)
{
    mark = gtk_text_buffer_get_insert(buffer_text_area);
    gtk_text_buffer_get_iter_at_mark(buffer_text_area, &iter, mark);
    position = gtk_text_iter_get_offset(&iter);

    set_cursor_at(position);

    switch (event->keyval)
    {
        case GDK_KEY_a:
        case GDK_KEY_b:
        case GDK_KEY_c:
        case GDK_KEY_d:
        case GDK_KEY_e:
        case GDK_KEY_f:
        case GDK_KEY_g:
        case GDK_KEY_h:
        case GDK_KEY_i:
        case GDK_KEY_j:
        case GDK_KEY_k:
        case GDK_KEY_l:
        case GDK_KEY_m:
        case GDK_KEY_n:
        case GDK_KEY_o:
        case GDK_KEY_p:
        case GDK_KEY_q:
        case GDK_KEY_r:
        case GDK_KEY_s:
        case GDK_KEY_t:
        case GDK_KEY_u:
        case GDK_KEY_v:
        case GDK_KEY_w:
        case GDK_KEY_x:
        case GDK_KEY_y:
        case GDK_KEY_z:
        case GDK_KEY_A:
        case GDK_KEY_B:
        case GDK_KEY_C:
        case GDK_KEY_D:
        case GDK_KEY_E:
        case GDK_KEY_F:
        case GDK_KEY_G:
        case GDK_KEY_H:
        case GDK_KEY_I:
        case GDK_KEY_J:
        case GDK_KEY_K:
        case GDK_KEY_L:
        case GDK_KEY_M:
        case GDK_KEY_N:
        case GDK_KEY_O:
        case GDK_KEY_P:
        case GDK_KEY_Q:
        case GDK_KEY_R:
        case GDK_KEY_S:
        case GDK_KEY_T:
        case GDK_KEY_U:
        case GDK_KEY_V:
        case GDK_KEY_W:
        case GDK_KEY_X:
        case GDK_KEY_Y:
        case GDK_KEY_Z:
        case GDK_KEY_0:
        case GDK_KEY_1:
        case GDK_KEY_2:
        case GDK_KEY_3:
        case GDK_KEY_4:
        case GDK_KEY_5:
        case GDK_KEY_6:
        case GDK_KEY_7:
        case GDK_KEY_8:
        case GDK_KEY_9:
        case GDK_KEY_space:
            insert_char(event->keyval);
            break;
        case GDK_KEY_BackSpace:
            delete_char();
            break;
        default:
            return FALSE;
    }
    update();
    return TRUE;
}

void text_editor_gui_main(void)
{
    // main window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "simple text editor");
    gtk_window_set_default_size(GTK_WINDOW(window), 1000, 600);
 	g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(quit), NULL);

    // main box
    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5); // non so cosa vogliano dire questi parametri

    // menubar with buttons
    menubar = gtk_menu_bar_new();
    gtk_box_pack_start(GTK_BOX(box), menubar, FALSE, FALSE, 0);

    // the actual interface of the editor
    view = gtk_text_view_new();
    gtk_box_pack_end(GTK_BOX(box), view, TRUE, TRUE, 0);
    gtk_text_view_set_editable(GTK_TEXT_VIEW(view), FALSE);
    gtk_widget_add_events(view, GDK_KEY_PRESS_MASK);
    g_signal_connect (G_OBJECT (view), "key_press_event", G_CALLBACK (press_key), NULL);
    buffer_text_area = gtk_text_view_get_buffer(GTK_TEXT_VIEW(view));

    gtk_container_add(GTK_CONTAINER(window), box);
    gtk_widget_show_all(window);
}