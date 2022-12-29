#include <stdio.h>

#include "macro.h"
#include "gap_buffer.h"

extern gap_buffer_t* gap_buf_ptr;

void print_stats(gap_buffer_t* ptr)
{
	printf("***** STATS *****\n");
	// printf("Message:\n");
	printf("left message: %s\n", ptr->left);
	printf("right message: %s\n", ptr->right + ptr->right_index);
	printf("left index: %d\n", ptr->left_index);
	printf("length of left message: %d\n", LEFT_LENGTH(ptr));
	printf("right Index: %d\n", ptr->right_index);
	printf("length of right message: %d\n", RIGHT_LENGTH(ptr));
	printf("total length of buffer: %d\n", ptr->length);
	printf("total length of the message: %d\n", LEFT_LENGTH(ptr) + RIGHT_LENGTH(ptr));
	printf("position of cursor: %u\n", ptr->cursor_pos);
	printf("*****************\n\n");
}

// dumps the contend of a buffer of given length
void dump(char buf[], int length)
{
	for(int i = 0; i < length; i++)
	{
		printf("%02x ",buf[i]);
		if((i + 1) % 8 == 0)
		{
			printf("\n");
		}
	}
	printf("\n");
}

void dump_gap_buffer(gap_buffer_t* ptr)
{
	print_stats(ptr);
    dump(ptr->left, ptr->length >> 1);
    dump(ptr->right, ptr->length >> 1);
}
