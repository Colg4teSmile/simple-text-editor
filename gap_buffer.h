#ifndef _GAP_BUFFER_MV_
#define _GAP_BUFFER_MV_

#define MIN_SIZE_GAP_BUFFER 32
#define MIN_SIZE_GAP_BUFFER_HALF 16

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
void reset_gap_buffer(void);
void insert(char ch);
void resize(void);
void insert_char(char ch);
void insert_string(const char* ch);  //TODO
void cursor_at(unsigned int);
const char* get_left_message(void);
const char* get_right_message(void);
void delete_char(void);
void delete_range(unsigned int from, unsigned int to);  //TODO

void print_stats(void /*gap_buffer_t* gap_buf_ptr*/);

#endif