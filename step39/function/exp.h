#include "function.h"

#ifndef _EXP_H_
#define _EXP_H_

typedef struct exp {
  Function function;
} Exp;

void Exp_init(Exp* p_self);

#endif // _EXP_H_