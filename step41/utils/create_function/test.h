#include "function.h"

#ifndef _TEST_H_
#define _TEST_H_

typedef struct test {
	Function function;
} Test;

void Test_init(Test* p_self);

#endif // _TEST_H_