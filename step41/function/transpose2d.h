#include "function.h"

#ifndef _TRANSPOSE2D_H_
#define _TRANSPOSE2D_H_

typedef struct transpose2d {
  Function function;
} Transpose2d;

void Transpose2d_init(Transpose2d* p_self);

#endif // _TRANSPOSE2D_H_