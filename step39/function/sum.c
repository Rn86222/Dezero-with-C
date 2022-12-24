#include "sum.h"
#include "function.h"
#include "functions.h"
#include "../variable/variable.h"
#include "../ndarray/ndarray.h"
#include <math.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

static Ndarray* sum_forward(Function* const p_self, const Ndarray* xs) {
	Ndarray* ys;
	ys = (Ndarray*)malloc(p_self->output_num * sizeof(Ndarray));
	ys[0] = Ndarray_sum(xs[0], ((Sum*)p_self)->axis, ((Sum*)p_self)->keepdims);
	return ys;
}

static Variable* reshape_sum_backward(Variable* gy, const int* shape, const int axis, const bool keepdims) {
	if (keepdims)
		return gy;
	int* new_shape;
	int new_dim = gy->p_data->dim + 1;
	new_shape = (int*)malloc(new_dim * sizeof(int));
	int cnt = 0;
	for (int i = 0; i < new_dim; i++) {
		if (i == axis) {
			new_shape[i] = 1;
		} else {
			new_shape[i] = shape[cnt++];
		}
	}
	return reshape(gy, new_dim, new_shape);
}

static Variable** sum_backward(Function* const p_self, Variable** gys) {
	Variable** gxs;
	gxs = (Variable**)malloc(p_self->input_num * sizeof(Variable*));
	gxs[0] = reshape_sum_backward(gys[0], p_self->p_io[0][0]->p_data->shape, ((Sum*)p_self)->axis, ((Sum*)p_self)->keepdims);
	return gxs;
}

static const FunctionMethods SUM_METHODS = {
	sum_forward,
	sum_backward
};

void Sum_init(Sum* p_self, const int axis, const bool keepdims) {
	((Function*)p_self)->p_methods = &SUM_METHODS;
	Function_init((Function*)p_self, 1, 1);
	strcpy(((Function*)p_self)->name, "Sum");
	p_self->axis = axis;
	p_self->keepdims = keepdims;
}
