#include "function.h"
#include "variable.h"
#include "neg.h"
#include "ndarray.h"
#include <stdlib.h>

static Ndarray* neg_forward(Function* const p_self, const Ndarray* xs) {
  Ndarray* ys;
  ys = (Ndarray*)malloc(p_self->output_num * sizeof(Ndarray));
  Ndarray_copy(&ys[0], Ndarray_neg(xs[0]));
  return ys;
}

static Ndarray* neg_backward(Function* const p_self, const Ndarray* gys) {
  Ndarray* gxs;
  gxs = (Ndarray*)malloc(p_self->input_num * sizeof(Ndarray));
  Ndarray_copy(&gxs[0], Ndarray_neg(gys[0]));
  return gxs;
}

static const FunctionMethods NEG_METHODS = {
  neg_forward,
  neg_backward
};

void Neg_init(Neg* p_self) {
  ((Function*)p_self)->p_methods = &NEG_METHODS;
  Function_init((Function*)p_self, 1, 1);
}