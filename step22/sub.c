#include "function.h"
#include "variable.h"
#include "sub.h"
#include "ndarray.h"
#include <stdlib.h>

static Ndarray* sub_forward(Function* const p_self, const Ndarray* xs) {
  Ndarray* ys;
  ys = (Ndarray*)malloc(p_self->output_num * sizeof(Ndarray));
  Ndarray_copy(&ys[0], Ndarray_sub(xs[0], xs[1]));
  return ys;
}

static Ndarray* sub_backward(Function* const p_self, const Ndarray* gys) {
  Ndarray* gxs;
  gxs = (Ndarray*)malloc(p_self->input_num * sizeof(Ndarray));
  gxs[0] = gys[0];
  Ndarray_copy(&gxs[1], Ndarray_neg(gys[0]));
  return gxs;
}

static const FunctionMethods SUB_METHODS = {
  sub_forward,
  sub_backward
};

void Sub_init(Sub* p_self) {
  ((Function*)p_self)->p_methods = &SUB_METHODS;
  Function_init((Function*)p_self, 2, 1);
}