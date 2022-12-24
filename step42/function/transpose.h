#include "function.h"

#ifndef _TRANSPOSE_H_
#define _TRANSPOSE_H_

typedef struct transpose {
  Function function;
  int dim;
  int* axes;
} Transpose;

void Transpose_init(Transpose* p_self, const int dim, const int* axes);

#endif // _TRANSPOSE_H_