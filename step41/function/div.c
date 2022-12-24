#include "function.h"
#include "functions.h"
#include "../variable/variable.h"
#include "div.h"
#include "../ndarray/ndarray.h"
#include <stdlib.h>
#include <string.h>

static Ndarray* div_forward(Function* const p_self, const Ndarray* xs) {
  Ndarray* ys;
  ys = (Ndarray*)malloc(p_self->output_num * sizeof(Ndarray));
  ys[0] = Ndarray_div(xs[0], xs[1]);
  return ys;
}

static Variable** div_backward(Function* const p_self, Variable** gys) {
  Variable** gxs;
  gxs = (Variable**)malloc(p_self->input_num * sizeof(Variable*));
  gxs[0] = divi(gys[0], p_self->p_io[0][1]);
  gxs[1] = mul(gys[0], neg(divi(p_self->p_io[1][0], p_self->p_io[0][1])));
  if (p_self->p_io[0][0]->p_data->size < p_self->p_io[0][1]->p_data->size) {
    gxs[0] = sum_to(gxs[0], p_self->p_io[0][0]->p_data->dim, p_self->p_io[0][0]->p_data->shape);
  } else if (p_self->p_io[0][0]->p_data->size > p_self->p_io[0][1]->p_data->size) {
    gxs[1] = sum_to(gxs[1], p_self->p_io[0][1]->p_data->dim, p_self->p_io[0][1]->p_data->shape);
  }
  return gxs;
}

static const FunctionMethods DIV_METHODS = {
  div_forward,
  div_backward
};

void Div_init(Div* p_self) {
  ((Function*)p_self)->p_methods = &DIV_METHODS;
  Function_init((Function*)p_self, 2, 1);
  strcpy(((Function*)p_self)->name, "Div");
}