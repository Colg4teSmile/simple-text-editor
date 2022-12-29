#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "gap_buffer.h"
#include "macro.h"

static void resize(gap_buffer_t* ptr);

void init_gap_buffer(gap_buffer_t* ptr)
{
	// ptr = (gap_buffer_t*)malloc(sizeof(gap_buffer_t));
	ptr->left = (char*) calloc(MIN_SIZE_GAP_BUFFER_HALF, sizeof(char));
	ptr->left_index = 0;

	ptr->right = (char*) calloc(MIN_SIZE_GAP_BUFFER_HALF, sizeof(char));
	ptr->right_index = MIN_SIZE_GAP_BUFFER_HALF - 1;

	ptr->length = MIN_SIZE_GAP_BUFFER;

	ptr->cursor_pos = 0;
	printf("ciao: %u\n",ptr->cursor_pos);
}

void free_gap_buffer(gap_buffer_t* ptr)
{
	free(ptr->left);
	ptr->left = NULL;

	free(ptr->right);
	ptr->right = NULL;
}

void reset_gap_buffer(gap_buffer_t* ptr)
{
	free_gap_buffer(ptr);
	ptr->left_index = 0;
	ptr->right_index = 0;
	ptr->length = 0;
}

// double the size if too small, half it if too big
static void resize(gap_buffer_t* ptr)
{
	// compute length of text written in buffer
	unsigned int length_tmp = LEFT_LENGTH(ptr) + RIGHT_LENGTH(ptr);
	if(DOUBLE(length_tmp) >= ptr->length)
	{
		//double the size of the buffer and copy the data
		char* buf_left_tmp = (char*)calloc(ptr->length, sizeof(char));
		memcpy(buf_left_tmp, ptr->left, ptr->left_index);

		char* buf_right_tmp = (char*)calloc(ptr->length, sizeof(char));

		// copy a string only if there is something in the buffer
		if (HALF(ptr->length) > ptr->right_index + 1)
		{
			memcpy(buf_right_tmp + HALF(ptr->length) + ptr->right_index + 1, 
				   ptr->right + ptr->right_index + 1, 
				   RIGHT_LENGTH(ptr));
		}

		free_gap_buffer(ptr);
		ptr->left = buf_left_tmp;
		ptr->right = buf_right_tmp;
		ptr->right_index = ptr->right_index + HALF(ptr->length);
		ptr->length = DOUBLE(ptr->length);
	}
	else if(QUADRUPLE(length_tmp) < ptr->length && ptr->length > MIN_SIZE_GAP_BUFFER)
	{
		unsigned int new_half_buf_length = QUARTER(ptr->length);

		char* buf_left_tmp = (char*)calloc(new_half_buf_length,sizeof(char));
		memcpy(buf_left_tmp, ptr->left, ptr->left_index);

		char* buf_right_tmp = (char*)calloc(new_half_buf_length,sizeof(char));
		// copy a string only if there is something in the buffer
		if(HALF(ptr->length) > ptr->right_index + 1)
		{
			memcpy(buf_right_tmp + ptr->right_index - new_half_buf_length, 
				   ptr->right + ptr->right_index, 
				   RIGHT_LENGTH(ptr));
		}

		free_gap_buffer(ptr);
		ptr->left = buf_left_tmp;
		ptr->right = buf_right_tmp;
		ptr->right_index = ptr->right_index - new_half_buf_length;	
		ptr->length = HALF(ptr->length);
	}
}

void insert_char(gap_buffer_t* ptr, char ch)
{
	*(ptr->left + ptr->left_index++) = ch;
	resize(ptr);
}

//TODO
void insert_string(const char* ch)
{

}

void update_gap_buffer(gap_buffer_t* ptr)
{
	if(ptr->cursor_pos >= ptr->length)
	{
		printf("Error: cursor_pos greater than length in gap_buffer\n");
		return;
	}
	if(ptr->cursor_pos < ptr->left_index)
	{
		(void)memcpy(ptr->right + ptr->right_index + 1 - (ptr->left_index - ptr->cursor_pos), 
					 ptr->left + ptr->cursor_pos, 
					 ptr->left_index - ptr->cursor_pos);
		(void)memset(ptr->left + ptr->cursor_pos, 0, ptr->left_index - ptr->cursor_pos);
		ptr->right_index = ptr->right_index - (ptr->left_index - ptr->cursor_pos);
		ptr->left_index = ptr->cursor_pos;
	}
	else if(ptr->cursor_pos > ptr->left_index)
	{
		(void)memcpy(ptr->left + ptr->left_index, 
					 ptr->right + ptr->right_index + 1, 
					 ptr->cursor_pos - ptr->left_index);
		(void)memset(ptr->right, 0, ptr->cursor_pos - ptr->left_index);
		ptr->right_index = ptr->right_index + (ptr->cursor_pos - ptr->left_index);
		ptr->left_index = ptr->cursor_pos;
	}
}
/*
void set_cursor_at(gap_buffer_t* ptr, unsigned int index)
{
	if(index >= ptr->length)
	{
		printf("Error: function %s tried to access out of range value\n", __func__);
		return;
	}
	if(index < ptr->left_index)
	{
		(void)memcpy(ptr->right + ptr->right_index - (ptr->left_index - index), 
					 ptr->left + index, 
					 ptr->left_index - index);
		(void)memset(ptr->left + index, 0, ptr->left_index - index);
		ptr->left_index = index;
		ptr->right_index = ptr->right_index - (ptr->left_index - index);
	}
	else if(index > ptr->left_index)
	{
		(void)memcpy(ptr->left +  ptr->left_index, 
					 ptr->right + ptr->right_index, 
					 index - ptr->left_index);
		(void)memset(ptr->right, 0, index - ptr->left_index);
		ptr->left_index = index;
		ptr->right_index = ptr->right_index + (index - ptr->left_index);
	}
}
*/

void save_file(const char* filename, gap_buffer_t* ptr)
{
	FILE* file = fopen(filename,"w");
	if(file == NULL)
	{
		printf("Error opening %s!\\n",filename);
	}
	scanf("%s",ptr->left);
	scanf("%s",ptr->right + ptr->right_index + 1);
	fclose(file);
}

const char* get_left_message(gap_buffer_t* ptr)
{
	return ptr->left;
}

const char* get_right_message(gap_buffer_t* ptr)
{
	return ptr->right + ptr->right_index + 1;
}

void delete_char(gap_buffer_t* ptr)
{
	if (ptr->left_index > 0)
	{
		*(ptr->left + ptr->left_index--) = '\0';
		resize(ptr);
	}
}

// TODO
void delete_range(unsigned int from, unsigned int to)
{

}