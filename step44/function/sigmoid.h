#include "function.h"

#ifndef _SIGMOID_H_
#define _SIGMOID_H_

typedef struct sigmoid {
	Function function;
} Sigmoid;

void Sigmoid_init(Sigmoid* p_self);

#endif // _SIGMOID_H_