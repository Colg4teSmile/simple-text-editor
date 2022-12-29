#include <stdio.h>
#include <gtk/gtk.h>

#include "macro.h"
#include "gap_buffer.h"
#include "gui.h"

gap_buffer_t* gap_buf_ptr;

int main(int argc, char* argv[])
{
	gap_buf_ptr = (gap_buffer_t*)malloc(sizeof(gap_buffer_t));
	init_gap_buffer(gap_buf_ptr);

	gtk_init(&argc, &argv);
    text_editor_gui_main();
    gtk_main();

	return 0;
}