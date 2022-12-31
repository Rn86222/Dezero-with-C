#include "tanh.h"
#include "function.h"
#include "functions.h"
#include "../variable/variable.h"
#include "../ndarray/ndarray.h"
#include "../utils/manage_memory/manage_memory.h"
#include <math.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

static Ndarray* tanh_forward(Function* const p_self, const Ndarray* xs) {
  Ndarray* ys;
  ys = (Ndarray*)mymalloc(p_self->output_num * sizeof(Ndarray));
  ys[0] = Ndarray_map(xs[0], tanh);
  return ys;
}

static Variable** tanh_backward(Function* const p_self, Variable** gys) {
  Variable** gxs;
  gxs = (Variable**)mymalloc(p_self->input_num * sizeof(Variable*));
  gxs[0] = mul(subLC(1.0, square(p_self->p_io[1][0])), gys[0]);
  return gxs;
}

static const FunctionMethods TANH_METHODS = {
  tanh_forward,
  tanh_backward
};

void Tanh_init(Tanh* p_self) {
  ((Function*)p_self)->p_methods = &TANH_METHODS;
  Function_init((Function*)p_self, 1, 1);
  strcpy(((Function*)p_self)->name, "Tanh");
}