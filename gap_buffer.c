#include "gap_buffer.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


static gap_buffer_t gap_buf;
gap_buffer_t* gap_buf_ptr = &gap_buf;

void init_gap_buffer(void)
{
	gap_buf.left = (char*) malloc(MIN_SIZE_GAP_BUFFER_HALF);
	memset(gap_buf.left, 0, MIN_SIZE_GAP_BUFFER_HALF);
	gap_buf.left_index = 0;

	gap_buf.right = (char*) malloc(MIN_SIZE_GAP_BUFFER_HALF);
	memset(gap_buf.right, 0x65, MIN_SIZE_GAP_BUFFER_HALF);
	gap_buf.right_index = MIN_SIZE_GAP_BUFFER_HALF - 1;

	gap_buf.length = MIN_SIZE_GAP_BUFFER;
}

void free_gap_buffer(void)
{
	free(gap_buf.left);
	gap_buf.left = NULL;
	//gap_buf.left_index = 0;

	printf("coglione1\n");
	//free(gap_buf.right);
	printf("coglione2\n");
	gap_buf.right = NULL;
	//gap_buf.right_index = 0;

	//gap_buf.length = 0;
}

// double the size if too small, half it if too big
void resize(void)
{
	unsigned int length_tmp = gap_buf.left_index + (gap_buf.length >> 1) - gap_buf.right_index - 1;
	if(length_tmp >= 2 * gap_buf.length)
	{
		//double the size of the buffer and copy the data
		char* buf_left_tmp = (char*)malloc(gap_buf.length);
		memset(buf_left_tmp, 0, gap_buf.length);
		memcpy(buf_left_tmp, gap_buf.left, gap_buf.left_index);

		char* buf_right_tmp = (char*)malloc(gap_buf.length);
		memset(buf_right_tmp, 0, gap_buf.length);
		memcpy(buf_right_tmp + gap_buf.length + gap_buf.right_index, gap_buf.right + gap_buf.right_index, gap_buf.length - gap_buf.right_index - 1);

		free_gap_buffer();

		gap_buf.left = buf_left_tmp;
		gap_buf.right = buf_right_tmp;
		gap_buf.right_index += gap_buf.length;		

		gap_buf.length <<= 1;
	}
	else if(length_tmp < gap_buf.length * 2 && gap_buf.length > MIN_SIZE_GAP_BUFFER)
	{
		//TODO: half the size
		unsigned int new_half_buf_length = gap_buf.length >> 2;

		char* buf_left_tmp = (char*)malloc(new_half_buf_length);
		memset(buf_left_tmp, 0, new_half_buf_length);
		memcpy(buf_left_tmp, gap_buf.left, gap_buf.left_index);

		char* buf_right_tmp = (char*)malloc(new_half_buf_length);
		memset(buf_right_tmp, 0, new_half_buf_length);
		memcpy(buf_right_tmp + gap_buf.right_index - new_half_buf_length, gap_buf.right + gap_buf.right_index, gap_buf.length - gap_buf.right_index - 1);

		free_gap_buffer();

		gap_buf.left = buf_left_tmp;
		gap_buf.right = buf_right_tmp;
		gap_buf.right_index -= new_half_buf_length;	

		gap_buf.length >>= 1;
	}
}


void insert(char ch)
{
	*(gap_buf.left + gap_buf.left_index++) = ch;
	resize();
}


// TODO: to put in tools.c
void print_stats(void /*gap_buffer_t* gap_buf_ptr*/)
{
	printf("***** STATS *****\n");
	printf("Message:\n");
	printf("%s",gap_buf_ptr->left);
	printf("%s\n",gap_buf_ptr->right + gap_buf_ptr->right_index);
	printf("Left Index: %d\n",gap_buf_ptr->left_index);
	printf("Right Index: %d (length of right buffer: %d)\n",gap_buf_ptr->right_index, gap_buf_ptr->length >> 1 - gap_buf_ptr->right_index - 1);
	printf("Total length of buffer: %d\n",gap_buf_ptr->length);
	printf("Total length of the message: %d\n", gap_buf.left_index + (gap_buf.length >> 1) - gap_buf.right_index - 1);
	printf("*****************\n\n");
}
