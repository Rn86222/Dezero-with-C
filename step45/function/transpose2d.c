#include "transpose2d.h"
#include "function.h"
#include "functions.h"
#include "../variable/variable.h"
#include "../ndarray/ndarray.h"
#include "../utils/manage_memory/manage_memory.h"
#include <math.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

static Ndarray* transpose2d_forward(Function* const p_self, const Ndarray* xs) {
  Ndarray* ys;
  ys = (Ndarray*)mymalloc(p_self->output_num * sizeof(Ndarray));
  ys[0] = Ndarray_transpose2d(xs[0]);
  return ys;
}

static Variable** transpose2d_backward(Function* const p_self, Variable** gys) {
  Variable** gxs;
  gxs = (Variable**)mymalloc(p_self->input_num * sizeof(Variable*));
  gxs[0] = transpose2d(gys[0]);
  return gxs;
}

static const FunctionMethods TRANSPOSE2D_METHODS = {
  transpose2d_forward,
  transpose2d_backward
};

void Transpose2d_init(Transpose2d* p_self) {
  ((Function*)p_self)->p_methods = &TRANSPOSE2D_METHODS;
  Function_init((Function*)p_self, 1, 1);
  strcpy(((Function*)p_self)->name, "Transpose2d");
}