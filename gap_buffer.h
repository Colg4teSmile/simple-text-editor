#ifndef _GAP_BUFFER_MV_
#define _GAP_BUFFER_MV_

#define MIN_SIZE_GAP_BUFFER 256
#define MIN_SIZE_GAP_BUFFER_HALF 128

// structure not needed, because used one time, but still nice to have
typedef struct gap_buffer {
	char* left;
	char* right;
	unsigned int left_index;
	unsigned int right_index;
	unsigned int length;
} gap_buffer_t;


void init_gap_buffer(void);
void free_gap_buffer(void);
void insert(char ch);
void resize(void);
void insert(char ch);

void print_stats(void /*gap_buffer_t* gap_buf_ptr*/);

#endif