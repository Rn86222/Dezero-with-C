#include "function.h"

#ifndef _MSE_H_
#define _MSE_H_

typedef struct mse {
	Function function;
} MSE;

void MSE_init(MSE* p_self);

#endif // _MSE_H_