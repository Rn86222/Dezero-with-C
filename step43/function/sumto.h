#include "function.h"

#ifndef _SUMTO_H_
#define _SUMTO_H_

typedef struct sumto {
	Function function;
	int dim;
	int* shape;
} SumTo;

void SumTo_init(SumTo* p_self, const int dim, const int* shape);

#endif // _SUMTO_H_