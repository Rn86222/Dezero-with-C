#include "function.h"

#ifndef _ADD_H_
#define _ADD_H_

typedef struct add {
  Function function;
} Add;

void Add_init(Add* p_self);

#endif // _ADD_H_