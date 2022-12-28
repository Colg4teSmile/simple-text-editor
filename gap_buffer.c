#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "gap_buffer.h"
#include "macro.h"

static gap_buffer_t gap_buf;
gap_buffer_t* gap_buf_ptr = &gap_buf;

void init_gap_buffer(void)
{
	gap_buf.left = (char*) calloc(MIN_SIZE_GAP_BUFFER_HALF, sizeof(char));
	gap_buf.left_index = 0;

	gap_buf.right = (char*) calloc(MIN_SIZE_GAP_BUFFER_HALF, sizeof(char));
	gap_buf.right_index = MIN_SIZE_GAP_BUFFER_HALF - 1;

	gap_buf.length = MIN_SIZE_GAP_BUFFER;

	gap_buf.cursor_pos = 0;
}

void free_gap_buffer(void)
{
	free(gap_buf.left);
	gap_buf.left = NULL;

	free(gap_buf.right);
	gap_buf.right = NULL;
}

void reset_gap_buffer(void)
{
	free_gap_buffer();
	gap_buf.left_index = 0;
	gap_buf.right_index = 0;
	gap_buf.length = 0;
}

// double the size if too small, half it if too big
void resize(void)
{
	// compute length of text written in buffer
	unsigned int length_tmp = LEFT_LENGTH(gap_buf_ptr) + RIGHT_LENGTH(gap_buf_ptr);
	if(DOUBLE(length_tmp) >= gap_buf.length)
	{
		//double the size of the buffer and copy the data
		char* buf_left_tmp = (char*)calloc(gap_buf.length, sizeof(char));
		memcpy(buf_left_tmp, gap_buf.left, gap_buf.left_index);

		char* buf_right_tmp = (char*)calloc(gap_buf.length, sizeof(char));

		// copy a string only if there is something in the buffer
		if (HALF(gap_buf.length) > gap_buf.right_index + 1)
		{
			memcpy(buf_right_tmp + HALF(gap_buf.length) + gap_buf.right_index + 1, 
				   gap_buf.right + gap_buf.right_index + 1, 
				   RIGHT_LENGTH(gap_buf_ptr));
		}

		free_gap_buffer();
		gap_buf.left = buf_left_tmp;
		gap_buf.right = buf_right_tmp;
		gap_buf.right_index = gap_buf.right_index + HALF(gap_buf.length);
		gap_buf.length = DOUBLE(gap_buf.length);
	}
	else if(QUADRUPLE(length_tmp) < gap_buf.length && gap_buf.length > MIN_SIZE_GAP_BUFFER)
	{
		unsigned int new_half_buf_length = QUARTER(gap_buf.length);

		char* buf_left_tmp = (char*)calloc(new_half_buf_length,sizeof(char));
		memcpy(buf_left_tmp, gap_buf.left, gap_buf.left_index);

		char* buf_right_tmp = (char*)calloc(new_half_buf_length,sizeof(char));
		// copy a string only if there is something in the buffer
		if(HALF(gap_buf.length) > gap_buf.right_index + 1)
		{
			memcpy(buf_right_tmp + gap_buf.right_index - new_half_buf_length, 
				   gap_buf.right + gap_buf.right_index, 
				   RIGHT_LENGTH(gap_buf_ptr));
		}

		free_gap_buffer();
		gap_buf.left = buf_left_tmp;
		gap_buf.right = buf_right_tmp;
		gap_buf.right_index = gap_buf.right_index - new_half_buf_length;	
		gap_buf.length = HALF(gap_buf.length);
	}
}

void insert_char(char ch)
{
	*(gap_buf.left + gap_buf.left_index++) = ch;
	resize();
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

void save_file(const char* filename)
{
	FILE* file = fopen(filename,"w");
	if(file == NULL)
	{
		printf("Error opening %s!\\n",filename);
	}
	scanf("%s",gap_buf.left);
	scanf("%s",gap_buf.right + gap_buf.right_index + 1);
	fclose(file);
}

const char* get_left_message(void)
{
	return gap_buf.left;
}

const char* get_right_message(void)
{
	return gap_buf.right + gap_buf.right_index + 1;
}

void delete_char(void)
{
	if (gap_buf.left_index > 0)
	{
		*(gap_buf.left + gap_buf.left_index--) = '\0';
		// DECREMENT_CURSOR();
	}
}

// TODO
void delete_range(unsigned int from, unsigned int to)
{

}