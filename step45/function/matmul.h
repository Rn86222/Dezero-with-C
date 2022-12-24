#include "function.h"

#ifndef _MATMUL_H_
#define _MATMUL_H_

typedef struct matmul {
	Function function;
} MatMul;

void MatMul_init(MatMul* p_self);

#endif // _MATMUL_H_