#include "function.h"
#include "functions.h"
#include "../variable/variable.h"
#include "neg.h"
#include "../ndarray/ndarray.h"
#include "../utils/manage_memory/manage_memory.h"
#include <stdlib.h>
#include <string.h>

static Ndarray* neg_forward(Function* const p_self, const Ndarray* xs) {
  Ndarray* ys;
  ys = (Ndarray*)mymalloc(p_self->output_num * sizeof(Ndarray));
  Ndarray_copy(&ys[0], Ndarray_neg(xs[0]));
  return ys;
}

static Variable** neg_backward(Function* const p_self, Variable** gys) {
  Variable** gxs;
  gxs = (Variable**)mymalloc(p_self->input_num * sizeof(Variable*));
  gxs[0] = neg(gys[0]);
  return gxs;
}

static const FunctionMethods NEG_METHODS = {
  neg_forward,
  neg_backward
};

void Neg_init(Neg* p_self) {
  ((Function*)p_self)->p_methods = &NEG_METHODS;
  Function_init((Function*)p_self, 1, 1);
  strcpy(((Function*)p_self)->name, "Neg");
}