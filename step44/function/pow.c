#include "function.h"
#include "functions.h"
#include "../variable/variable.h"
#include "pow.h"
#include "../ndarray/ndarray.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static Ndarray* pow_forward(Function* const p_self, const Ndarray* xs) {
  Ndarray* ys;
  ys = (Ndarray*)malloc(p_self->output_num * sizeof(Ndarray));
  ys[0] = Ndarray_pow(xs[0], xs[1]);
  return ys;
}

static Variable** pow_backward(Function* const p_self, Variable** gys) {
  Variable** gxs;
  gxs = (Variable**)malloc(p_self->input_num * sizeof(Variable*));
  gxs[0] = mul(gys[0], mul(p_self->p_io[0][1], powe(p_self->p_io[0][0], subRC(p_self->p_io[0][1], 1.0))));
  gxs[1] = mul(gys[0], mul(p_self->p_io[1][0], ln(p_self->p_io[0][0])));
  if (p_self->p_io[0][0]->p_data->size < p_self->p_io[0][1]->p_data->size) {
    gxs[0] = sum_to(gxs[0], p_self->p_io[0][0]->p_data->dim, p_self->p_io[0][0]->p_data->shape);
  } else if (p_self->p_io[0][0]->p_data->size > p_self->p_io[0][1]->p_data->size) {
    gxs[1] = sum_to(gxs[1], p_self->p_io[0][1]->p_data->dim, p_self->p_io[0][1]->p_data->shape);
  }
  return gxs;
}

static const FunctionMethods POW_METHODS = {
  pow_forward,
  pow_backward
};

void Pow_init(Pow* p_self) {
  ((Function*)p_self)->p_methods = &POW_METHODS;
  Function_init((Function*)p_self, 2, 1);
  strcpy(((Function*)p_self)->name, "Pow");
}