#include "sigmoid.h"
#include "function.h"
#include "functions.h"
#include "../variable/variable.h"
#include "../ndarray/ndarray.h"
#include "../utils/manage_memory/manage_memory.h"
#include <math.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

static Ndarray* sigmoid_forward(Function* const p_self, const Ndarray* xs) {
	Ndarray* ys;
	ys = (Ndarray*)mymalloc(p_self->output_num * sizeof(Ndarray));
	ys[0] = Ndarray_constant_add(Ndarray_constant_mul(Ndarray_map(Ndarray_constant_mul(xs[0], 0.5), tanh), 0.5), 0.5);
	// Ndarray_print(&ys[0]);
	return ys;
}

static Variable** sigmoid_backward(Function* const p_self, Variable** gys) {
	Variable** gxs;
	gxs = (Variable**)mymalloc(p_self->input_num * sizeof(Variable*));
	gxs[0] = mul(gys[0], mul(p_self->p_io[1][0], subLC(1, p_self->p_io[1][0])));
	return gxs;
}

static const FunctionMethods SIGMOID_METHODS = {
	sigmoid_forward,
	sigmoid_backward
};

void Sigmoid_init(Sigmoid* p_self) {
	((Function*)p_self)->p_methods = &SIGMOID_METHODS;
	Function_init((Function*)p_self, 1, 1);
	strcpy(((Function*)p_self)->name, "Sigmoid");
}
