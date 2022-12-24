#include "function.h"

#ifndef _LINEAR_H_
#define _LINEAR_H_

typedef struct linear {
	Function function;
} Linear;

void Linear_init(Linear* p_self);

#endif // _LINEAR_H_