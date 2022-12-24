#include "function.h"
#include "../variable/variable.h"
#include "div.h"
#include "../ndarray/ndarray.h"
#include <stdlib.h>

static Ndarray* div_forward(Function* const p_self, const Ndarray* xs) {
  Ndarray* ys;
  ys = (Ndarray*)malloc(p_self->output_num * sizeof(Ndarray));
  ys[0] = Ndarray_div(xs[0], xs[1]);
  return ys;
}

static Ndarray* div_backward(Function* const p_self, const Ndarray* gys) {
  Ndarray* gxs;
  gxs = (Ndarray*)malloc(p_self->input_num * sizeof(Ndarray));
  gxs[0] = Ndarray_div(gys[0], *(p_self->p_io[0][1]->p_data));
  gxs[1] = Ndarray_mul(gys[0], Ndarray_neg(Ndarray_div(*(p_self->p_io[0][0]->p_data), Ndarray_square(*(p_self->p_io[0][1]->p_data)))));
  return gxs;
}

static const FunctionMethods DIV_METHODS = {
  div_forward,
  div_backward
};

void Div_init(Div* p_self) {
  ((Function*)p_self)->p_methods = &DIV_METHODS;
  Function_init((Function*)p_self, 2, 1);
}