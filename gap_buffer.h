#ifndef _GAP_BUFFER_MV_H_
#define _GAP_BUFFER_MV_H_

#define MIN_SIZE_GAP_BUFFER 32
#define MIN_SIZE_GAP_BUFFER_HALF 16 // MIN_SIZE_GAP_BUFFER / 2

typedef struct gap_buffer {
	// unsigned int ID;
	char* left;
	char* right;
	unsigned int left_index;
	unsigned int right_index;
	unsigned int length;
	unsigned int cursor_pos;
} gap_buffer_t;

// TODO: all the functions should take a pointer to a gap buffer as a parameter
// TODO: init function should return a pointer to a gap buffer structure
void init_gap_buffer(void);
void free_gap_buffer(void);
void reset_gap_buffer(void);
//void insert(char ch);
void resize(void);
void insert_char(char ch);
void insert_string(const char* ch);  //TODO
// void set_cursor_at(gap_buffer_t* ptr, unsigned int index);
const char* get_left_message(void);
const char* get_right_message(void);
void update_gap_buffer(gap_buffer_t* ptr);

void delete_char(void);
void delete_range(unsigned int from, unsigned int to);  //TODO

void print_stats(gap_buffer_t* ptr);
void dump(char buf[], int length);
void dump_gap_buffer(gap_buffer_t* ptr);

#endif