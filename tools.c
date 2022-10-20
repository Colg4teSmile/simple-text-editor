#include "gap_buffer.h"

#include <stdio.h>

extern gap_buffer_t* gap_buf_ptr;

void print_stats(void  /* TODO: gap_buffer_t* gap_buf_ptr */)
{
	printf("***** STATS *****\n");
	printf("Message:\n");
	printf("%s", gap_buf_ptr->left);
	//printf("%s\n", gap_buf_ptr->right + gap_buf_ptr->right_index);
	printf("Left index: %d\n", gap_buf_ptr->left_index);
	printf("Length of left message: %d\n", gap_buf_ptr->left_index);
	printf("Right Index: %d\n", gap_buf_ptr->right_index);
	printf("Length of right message: %d\n", (gap_buf_ptr->length >> 1) - gap_buf_ptr->right_index - 1);
	printf("Total length of buffer: %d\n", gap_buf_ptr->length);
	printf("Total length of the message: %d\n", gap_buf_ptr->left_index + (gap_buf_ptr->length >> 1) - gap_buf_ptr->right_index - 1);
	printf("*****************\n\n");
}

// dumps the contend of a buffer of given length
void dump(char buf[], int length)
{
	for(int i = 0; i < length; i++)
	{
		printf("%02x ",buf[i]);
		if(i + 1 % 8 == 0)
		{
			printf("\n");
		}
	}
	printf("\n");
}



// TODO
char* get_text(gap_buffer_t* gap_buf_ptr)
{
	//char* buf_tmp = (char*)malloc(gap_buf_ptr->length)
	return NULL;
}