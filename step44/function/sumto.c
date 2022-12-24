#include "sumto.h"
#include "function.h"
#include "functions.h"
#include "../variable/variable.h"
#include "../ndarray/ndarray.h"
#include <math.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

static Ndarray* sumto_forward(Function* const p_self, const Ndarray* xs) {
	Ndarray* ys;
	ys = (Ndarray*)malloc(p_self->output_num * sizeof(Ndarray));
	ys[0] = Ndarray_sum_to(xs[0], ((SumTo*)p_self)->dim, ((SumTo*)p_self)->shape);
	return ys;
}

static Variable** sumto_backward(Function* const p_self, Variable** gys) {
	Variable** gxs;
	gxs = (Variable**)malloc(p_self->input_num * sizeof(Variable*));
	gxs[0] = broadcast_to(gys[0], p_self->p_io[0][0]->p_data->dim, p_self->p_io[0][0]->p_data->shape);
	return gxs;
}

static const FunctionMethods SUMTO_METHODS = {
	sumto_forward,
	sumto_backward
};

void SumTo_init(SumTo* p_self, const int dim, const int* shape) {
	((Function*)p_self)->p_methods = &SUMTO_METHODS;
	Function_init((Function*)p_self, 1, 1);
	strcpy(((Function*)p_self)->name, "SumTo");
	p_self->dim = dim;
	p_self->shape = (int*)malloc(dim * sizeof(int));
	for (int i = 0; i < dim; i++)
		p_self->shape[i] = shape[i];
}
