#include "function.h"

#ifndef _COS_H_
#define _COS_H_

typedef struct cos {
  Function function;
} Cos;

void Cos_init(Cos* p_self);

#endif // _COS_H_