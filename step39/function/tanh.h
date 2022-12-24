#include "function.h"

#ifndef _TANH_H_
#define _TANH_H_

typedef struct tanh {
  Function function;
} Tanh;

void Tanh_init(Tanh* p_self);

#endif // _TANH_H_