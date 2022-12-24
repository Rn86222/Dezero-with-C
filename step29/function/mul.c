#include "function.h"
#include "../variable/variable.h"
#include "mul.h"
#include "../ndarray/ndarray.h"
#include <stdlib.h>
#include <string.h>

static Ndarray* mul_forward(Function* const p_self, const Ndarray* xs) {
  Ndarray* ys;
  ys = (Ndarray*)malloc(p_self->output_num * sizeof(Ndarray));
  Ndarray_copy(&ys[0], Ndarray_mul(xs[0], xs[1]));
  return ys;
}

static Ndarray* mul_backward(Function* const p_self, const Ndarray* gys) {
  Ndarray* gxs;
  gxs = (Ndarray*)malloc(p_self->input_num * sizeof(Ndarray));
  Ndarray_copy(&gxs[0], Ndarray_mul(*(p_self->p_io[0][1]->p_data), gys[0]));
  Ndarray_copy(&gxs[1], Ndarray_mul(*(p_self->p_io[0][0]->p_data), gys[0]));
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