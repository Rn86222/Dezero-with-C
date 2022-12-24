#include "function.h"
#include "../variable/variable.h"
#include "sin.h"
#include "../ndarray/ndarray.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

static Ndarray* sin_forward(Function* const p_self, const Ndarray* xs) {
  Ndarray* ys;
  ys = (Ndarray*)malloc(p_self->output_num * sizeof(Ndarray));
  ys[0] = Ndarray_map(xs[0], sin);
  return ys;
}

static Ndarray* sin_backward(Function* const p_self, const Ndarray* gys) {
  Ndarray* gxs;
  gxs = (Ndarray*)malloc(p_self->input_num * sizeof(Ndarray));
  gxs[0] = Ndarray_mul(gys[0], Ndarray_map(*(p_self->p_io[0][0]->p_data), cos));
  return gxs;
}

static const FunctionMethods SIN_METHODS = {
  sin_forward,
  sin_backward
};

void Sin_init(Sin* p_self) {
  ((Function*)p_self)->p_methods = &SIN_METHODS;
  Function_init((Function*)p_self, 1, 1);
  strcpy(((Function*)p_self)->name, "Sin");
}