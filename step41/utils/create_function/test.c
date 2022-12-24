#include <test.h>
#include "function.h"
#include "functions.h"
#include "../variable/variable.h"
#include "../ndarray/ndarray.h"
#include <math.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

static Ndarray* test_forward(Function* const p_self, const Ndarray* xs) {
	Ndarray* ys;
	ys = (Ndarray*)malloc(p_self->output_num * sizeof(Ndarray));
	ys[0] = xs[0];
	return ys;
}

static Variable** test_backward(Function* const p_self, Variable** gys) {
	Variable** gxs;
	gxs = (Variable**)malloc(p_self->input_num * sizeof(Variable*));
	gxs[0] = gys[0];
	return gxs;
}

static const FunctionMethods TEST_METHODS = {
	test_forward,
	test_backward
};

void Test_init(Test* p_self) {
	((Function*)p_self)->p_methods = &TEST_METHODS;
	Function_init((Function*)p_self, 1, 1);
	strcpy(((Function*)p_self)->name, "Test");
}
