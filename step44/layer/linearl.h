#include "layer.h"

#ifndef _LINEARL_H_
#define _LINEARL_H_

typedef struct linearl {
  Layer layer;
  int in_size;
  int out_size;
  Variable* W;
  Variable* b;
} LinearL;

void LinearL_init(LinearL* p_self, int out_size);

#endif // _LINEARL_H_