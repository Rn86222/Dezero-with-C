#include "function.h"

#ifndef _NEG_H_
#define _NEG_H_

typedef struct neg {
  Function function;
} Neg;

void Neg_init(Neg* p_self);

#endif // _NEG_H_