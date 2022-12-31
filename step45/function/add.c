#include "function.h"
#include "functions.h"
#include "../variable/variable.h"
#include "add.h"
#include "../ndarray/ndarray.h"
#include "../utils/manage_memory/manage_memory.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static Ndarray* add_forward(Function* const p_self, const Ndarray* xs) {
  Ndarray* ys;
  ys = (Ndarray*)mymalloc(p_self->output_num * sizeof(Ndarray));
  ys[0] = Ndarray_add(xs[0], xs[1]);
  return ys;
}

static Variable** add_backward(Function* const p_self, Variable** gys) {
  Variable** gxs;
  gxs = (Variable**)mymalloc(p_self->input_num * sizeof(Variable*));
  gxs[0] = gys[0];
  gxs[1] = gys[0];
  if (p_self->p_io[0][0]->p_data->size < p_self->p_io[0][1]->p_data->size) {
    gxs[0] = sum_to(gxs[0], p_self->p_io[0][0]->p_data->dim, p_self->p_io[0][0]->p_data->shape);
  } else if (p_self->p_io[0][0]->p_data->size > p_self->p_io[0][1]->p_data->size) {
    gxs[1] = sum_to(gxs[1], p_self->p_io[0][1]->p_data->dim, p_self->p_io[0][1]->p_data->shape);
  }
  return gxs;
}

static const FunctionMethods ADD_METHODS = {
  add_forward,
  add_backward
};

void Add_init(Add* p_self) {
  ((Function*)p_self)->p_methods = &ADD_METHODS;
  Function_init((Function*)p_self, 2, 1);
  strcpy(((Function*)p_self)->name, "Add");
}
