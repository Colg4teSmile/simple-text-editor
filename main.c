#include <stdio.h>
#include <gtk/gtk.h>

#include "gap_buffer.h"
#include "gui.h"

extern gap_buffer_t* gap_buf_ptr;

int main(int argc, char* argv[])
{
	init_gap_buffer();

	gtk_init(&argc, &argv);
    text_editor_gui_main();
    gtk_main();

	return 0;
}