#include "function.h"

#ifndef _SQUARE_H_
#define _SQAURE_H_

typedef struct square {
  Function function;
} Square;

void Square_init(Square* p_self);

#endif // _SQAURE_H_