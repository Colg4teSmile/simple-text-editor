#ifndef _MACRO_MV_H_
#define _MACRO_MV_H_

#define QUADRUPLE(x) (x << 2)
#define DOUBLE(x) (x << 1)
#define HALF(x) (x >> 1)
#define QUARTER(x) (x >> 2)

#define LEFT_LENGTH(ptr) ptr->left_index
#define RIGHT_LENGTH(ptr) HALF(ptr->length) - (ptr->right_index + 1)

#define INCREMENT_CURSOR(ptr) if(ptr->cursor_pos < LEFT_LENGTH(ptr) + RIGHT_LENGTH(ptr)) ptr->cursor_pos++
#define DECREMENT_CURSOR(ptr) if(ptr->cursor_pos > 0) ptr->cursor_pos--
#define GET_CURSOR(ptr) ptr->cursor_pos
// #define SET_CURSOR(x) cursor_pos = x

#endif