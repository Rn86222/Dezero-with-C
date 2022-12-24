#include "exp.h"
#include "function.h"
#include "variable.h"
#include "ndarray.h"
#include <math.h>
#include <assert.h>
#include <stdlib.h>

static Ndarray* exp_forward(Function* const p_self, const Ndarray* xs) {
  Ndarray* ys;
  ys = (Ndarray*)malloc(p_self->output_num * sizeof(Ndarray));
  Ndarray_copy(&ys[0], Ndarray_map(xs[0], exp));
  return ys;
}

static Ndarray* exp_backward(Function* const p_self, const Ndarray* gys) {
  Ndarray* gxs;
  gxs = (Ndarray*)malloc(p_self->input_num * sizeof(Ndarray));
  Ndarray_copy(&gxs[0], Ndarray_mul(Ndarray_map(*(p_self->p_io[0][0]->p_data), exp), gys[0]));
  return gxs;
}

static const FunctionMethods EXP_METHODS = {
  exp_forward,
  exp_backward
};

void Exp_init(Exp* p_self) {
  ((Function*)p_self)->p_methods = &EXP_METHODS;
  Function_init((Function*)p_self, 1, 1);
}