#include "linear.h"
#include "function.h"
#include "functions.h"
#include "../variable/variable.h"
#include "../ndarray/ndarray.h"
#include <math.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

static Ndarray* linear_forward(Function* const p_self, const Ndarray* xs) {
	Ndarray* ys;
	ys = (Ndarray*)malloc(p_self->output_num * sizeof(Ndarray));
	ys[0] = Ndarray_add(Ndarray_dot(xs[0], xs[1]), xs[2]);
	return ys;
}

static Variable** linear_backward(Function* const p_self, Variable** gys) {
	Variable** gxs;
	gxs = (Variable**)malloc(p_self->input_num * sizeof(Variable*));
	gxs[0] = matmul(gys[0], transpose2d(p_self->p_io[0][1]));
	gxs[1] = matmul(transpose2d(p_self->p_io[0][0]), gys[0]);
	gxs[2] = sum_to(gys[0], p_self->p_io[0][2]->p_data->dim, p_self->p_io[0][2]->p_data->shape);
	return gxs;
}

static const FunctionMethods LINEAR_METHODS = {
	linear_forward,
	linear_backward
};

void Linear_init(Linear* p_self) {
	((Function*)p_self)->p_methods = &LINEAR_METHODS;
	Function_init((Function*)p_self, 3, 1);
	strcpy(((Function*)p_self)->name, "Linear");
}
