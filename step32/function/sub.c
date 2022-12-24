#include "function.h"
#include "functions.h"
#include "../variable/variable.h"
#include "sub.h"
#include "../ndarray/ndarray.h"
#include <stdlib.h>
#include <string.h>

static Ndarray* sub_forward(Function* const p_self, const Ndarray* xs) {
  Ndarray* ys;
  ys = (Ndarray*)malloc(p_self->output_num * sizeof(Ndarray));
  ys[0] = Ndarray_sub(xs[0], xs[1]);
  return ys;
}

static Variable** sub_backward(Function* const p_self, Variable** gys) {
  Variable** gxs;
  gxs = (Variable**)malloc(p_self->input_num * sizeof(Variable*));
  gxs[0] = addRC(gys[0], 0.0);
  gxs[1] = neg(gys[0]);
  return gxs;
}

static const FunctionMethods SUB_METHODS = {
  sub_forward,
  sub_backward
};

void Sub_init(Sub* p_self) {
  ((Function*)p_self)->p_methods = &SUB_METHODS;
  Function_init((Function*)p_self, 2, 1);
  strcpy(((Function*)p_self)->name, "Sub");
}