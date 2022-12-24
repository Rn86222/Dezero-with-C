#include "function.h"

#ifndef _RESHAPE_H_
#define _RESHAPE_H_

typedef struct reshape {
  Function function;
  int dim;
  int* shape;
} Reshape;

void Reshape_init(Reshape* p_self, const int dim, const int* shape);

#endif // _RESHAPE_H_