#include "function.h"

#ifndef _POW_H_
#define _POW_H_

typedef struct pow {
  Function function;
} Pow;

void Pow_init(Pow* p_self);

#endif // _POW_H_