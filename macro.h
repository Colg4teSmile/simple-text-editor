#ifndef _MACRO_MV_H_
#define _MACRO_MV_H_

#define QUADRUPLE(x) (x << 2)
#define DOUBLE(x) (x << 1)
#define HALF(x) (x >> 1)
#define QUARTER(x) (x >> 2)

#define INCREMENT_CURSOR() cursor_pos++
#define DECREMENT_CURSOR() cursor_pos--
#define GET_CURSOR() cursor_pos
#define SET_CURSOR(x) cursor_pos = x

#endif