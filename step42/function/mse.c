#include "mse.h"
#include "function.h"
#include "functions.h"
#include "../variable/variable.h"
#include "../ndarray/ndarray.h"
#include <math.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

static Ndarray* mse_forward(Function* const p_self, const Ndarray* xs) {
	Ndarray* ys;
	ys = (Ndarray*)malloc(p_self->output_num * sizeof(Ndarray));
	int shape[1] = {1};
	ys[0] = Ndarray_constant_mul(Ndarray_sum_to(Ndarray_square(Ndarray_sub(xs[0], xs[1])), 0, shape), (float)1.0 / Ndarray_sub(xs[0], xs[1]).shape[0]);
	return ys;
}

static Variable** mse_backward(Function* const p_self, Variable** gys) {
	Variable** gxs;
	gxs = (Variable**)malloc(p_self->input_num * sizeof(Variable*));
	Variable* diff = sub(p_self->p_io[0][0], p_self->p_io[0][1]);
	gxs[0] = mulRC(mul(gys[0], diff), (float)2.0 / diff->p_data->shape[0]);
	gxs[1] = neg(gxs[0]);
	return gxs;
}

static const FunctionMethods MSE_METHODS = {
	mse_forward,
	mse_backward
};

void MSE_init(MSE* p_self) {
	((Function*)p_self)->p_methods = &MSE_METHODS;
	Function_init((Function*)p_self, 2, 1);
	strcpy(((Function*)p_self)->name, "MSE");
}
