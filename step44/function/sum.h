#include "function.h"

#ifndef _SUM_H_
#define _SUM_H_

typedef struct sum {
	Function function;
	int axis;
	bool keepdims;
} Sum;

void Sum_init(Sum* p_self, const int axis, const bool keepdims);

#endif // _SUM_H_