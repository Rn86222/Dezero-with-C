#include "matmul.h"
#include "function.h"
#include "functions.h"
#include "../variable/variable.h"
#include "../ndarray/ndarray.h"
#include "../utils/manage_memory/manage_memory.h"
#include <math.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

static Ndarray* matmul_forward(Function* const p_self, const Ndarray* xs) {
	Ndarray* ys;
	ys = (Ndarray*)mymalloc(p_self->output_num * sizeof(Ndarray));
	ys[0] = Ndarray_dot(xs[0], xs[1]);
	return ys;
}

static Variable** matmul_backward(Function* const p_self, Variable** gys) {
	Variable** gxs;
	gxs = (Variable**)mymalloc(p_self->input_num * sizeof(Variable*));
	gxs[0] = matmul(gys[0], transpose2d(p_self->p_io[0][1]));
	gxs[1] = matmul(transpose2d(p_self->p_io[0][0]), gys[0]);
	return gxs;
}

static const FunctionMethods MATMUL_METHODS = {
	matmul_forward,
	matmul_backward
};

void MatMul_init(MatMul* p_self) {
	((Function*)p_self)->p_methods = &MATMUL_METHODS;
	Function_init((Function*)p_self, 2, 1);
	strcpy(((Function*)p_self)->name, "MatMul");
}
