#include "function.h"
#include "functions.h"
#include "../variable/variable.h"
#include "mul.h"
#include "../ndarray/ndarray.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static Ndarray* mul_forward(Function* const p_self, const Ndarray* xs) {
  Ndarray* ys;
  ys = (Ndarray*)malloc(p_self->output_num * sizeof(Ndarray));
  ys[0] = Ndarray_mul(xs[0], xs[1]);
  return ys;
}

static Variable** mul_backward(Function* const p_self, Variable** gys) {
  Variable** gxs;
  gxs = (Variable**)malloc(p_self->input_num * sizeof(Variable*));
  gxs[0] = mul(p_self->p_io[0][1], gys[0]);
  gxs[1] = mul(p_self->p_io[0][0], gys[0]);
  if (p_self->p_io[0][0]->p_data->size < p_self->p_io[0][1]->p_data->size) {
    gxs[0] = sum_to(gxs[0], p_self->p_io[0][0]->p_data->dim, p_self->p_io[0][0]->p_data->shape);
  } else if (p_self->p_io[0][0]->p_data->size > p_self->p_io[0][1]->p_data->size) {
    gxs[1] = sum_to(gxs[1], p_self->p_io[0][1]->p_data->dim, p_self->p_io[0][1]->p_data->shape);
  }
  return gxs;
}

static const FunctionMethods MUL_METHODS = {
  mul_forward,
  mul_backward
};

void Mul_init(Mul* p_self) {
  ((Function*)p_self)->p_methods = &MUL_METHODS;
  Function_init((Function*)p_self, 2, 1);
  strcpy(((Function*)p_self)->name, "Mul");
}