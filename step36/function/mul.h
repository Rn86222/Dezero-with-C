#include "function.h"

#ifndef _MUL_H_
#define _MUL_H_

typedef struct mul {
  Function function;
} Mul;

void Mul_init(Mul* p_self);

#endif // _MUL_H_