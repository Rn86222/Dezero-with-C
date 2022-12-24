#include "function.h"
#include "../variable/variable.h"
#include "pow.h"
#include "../ndarray/ndarray.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>

static Ndarray* pow_forward(Function* const p_self, const Ndarray* xs) {
  Ndarray* ys;
  ys = (Ndarray*)malloc(p_self->output_num * sizeof(Ndarray));
  ys[0] = Ndarray_pow(xs[0], xs[1]);
  return ys;
}

static Ndarray* pow_backward(Function* const p_self, const Ndarray* gys) {
  Ndarray* gxs;
  gxs = (Ndarray*)malloc(p_self->input_num * sizeof(Ndarray));
  gxs[0] = Ndarray_mul(gys[0], Ndarray_mul(*(p_self->p_io[0][1]->p_data), Ndarray_pow(*(p_self->p_io[0][0]->p_data), Ndarray_constant_add(*(p_self->p_io[0][1]->p_data), -1))));
  gxs[1] = Ndarray_mul(gys[0], Ndarray_mul(*(p_self->p_io[1][0]->p_data), Ndarray_map(*(p_self->p_io[0][0]->p_data), log)));
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