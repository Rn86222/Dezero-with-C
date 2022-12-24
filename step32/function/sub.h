#include "function.h"

#ifndef _SUB_H_
#define _SUB_H_

typedef struct sub {
  Function function;
} Sub;

void Sub_init(Sub* p_self);

#endif // _SUBH_