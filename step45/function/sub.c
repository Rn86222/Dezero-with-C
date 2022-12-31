#include "function.h"
#include "functions.h"
#include "../variable/variable.h"
#include "sub.h"
#include "../ndarray/ndarray.h"
#include "../utils/manage_memory/manage_memory.h"
#include <stdlib.h>
#include <string.h>

static Ndarray* sub_forward(Function* const p_self, const Ndarray* xs) {
  Ndarray* ys;
  ys = (Ndarray*)mymalloc(p_self->output_num * sizeof(Ndarray));
  ys[0] = Ndarray_sub(xs[0], xs[1]);
  return ys;
}

static Variable** sub_backward(Function* const p_self, Variable** gys) {
  Variable** gxs;
  gxs = (Variable**)mymalloc(p_self->input_num * sizeof(Variable*));
  gxs[0] = gys[0];
  gxs[1] = neg(gys[0]);
  if (p_self->p_io[0][0]->p_data->size < p_self->p_io[0][1]->p_data->size) {
    gxs[0] = sum_to(gxs[0], p_self->p_io[0][0]->p_data->dim, p_self->p_io[0][0]->p_data->shape);
  } else if (p_self->p_io[0][0]->p_data->size > p_self->p_io[0][1]->p_data->size) {
    gxs[1] = sum_to(gxs[1], p_self->p_io[0][1]->p_data->dim, p_self->p_io[0][1]->p_data->shape);
  }
  return gxs;
}

static const FunctionMethods SUB_METHODS = {
  sub_forward,
  sub_backward
};

void Sub_init(Sub* p_self) {
  ((Function*)p_self)->p_methods = &SUB_METHODS;
  Function_init((Function*)p_self, 2, 1);
  strcpy(((Function*)p_self)->name, "Sub");
}