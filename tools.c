#include "gap_buffer.h"

#include <stdio.h>

extern gap_buffer_t* gap_buf_ptr;

void print_stats(gap_buffer_t* ptr)
{
	printf("***** STATS *****\n");
	printf("Message:\n");
	printf("left message: %s", ptr->left);
	printf("right message: %s\n", ptr->right + ptr->right_index);
	printf("Left index: %d\n", ptr->left_index);
	printf("Length of left message: %d\n", ptr->left_index);
	printf("Right Index: %d\n", ptr->right_index);
	printf("Length of right message: %d\n", (ptr->length >> 1) - ptr->right_index - 1);
	printf("Total length of buffer: %d\n", ptr->length);
	printf("Total length of the message: %d\n", ptr->left_index + (ptr->length >> 1) - ptr->right_index - 1);
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

// TODO
char* get_text(gap_buffer_t* gap_buf_ptr)
{
	//char* buf_tmp = (char*)malloc(gap_buf_ptr->length)
	return NULL;
}