#include "function.h"
#include "functions.h"
#include "../variable/variable.h"
#include "cos.h"
#include "../ndarray/ndarray.h"
#include "../utils/manage_memory/manage_memory.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

static Ndarray* cos_forward(Function* const p_self, const Ndarray* xs) {
  Ndarray* ys;
  ys = (Ndarray*)mymalloc(p_self->output_num * sizeof(Ndarray));
  ys[0] = Ndarray_map(xs[0], cos);
  return ys;
}

static Variable** cos_backward(Function* const p_self, Variable** gys) {
  Variable** gxs;
  gxs = (Variable**)mymalloc(p_self->input_num * sizeof(Variable*));
  gxs[0] = mul(gys[0], neg(sine(p_self->p_io[0][0])));
  return gxs;
}

static const FunctionMethods COS_METHODS = {
  cos_forward,
  cos_backward
};

void Cos_init(Cos* p_self) {
  ((Function*)p_self)->p_methods = &COS_METHODS;
  Function_init((Function*)p_self, 1, 1);
  strcpy(((Function*)p_self)->name, "Cos");
}