#include "reshape.h"
#include "function.h"
#include "functions.h"
#include "../variable/variable.h"
#include "../ndarray/ndarray.h"
#include "../utils/manage_memory/manage_memory.h"
#include <math.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

static Ndarray* reshape_forward(Function* const p_self, const Ndarray* xs) {
  Ndarray* ys;
  ys = (Ndarray*)mymalloc(p_self->output_num * sizeof(Ndarray));
  ys[0] = Ndarray_reshape(xs[0], ((Reshape*)p_self)->dim, ((Reshape*)p_self)->shape);
  return ys;
}

static Variable** reshape_backward(Function* const p_self, Variable** gys) {
  Variable** gxs;
  gxs = (Variable**)mymalloc(p_self->input_num * sizeof(Variable*));
  gxs[0] = reshape(gys[0], p_self->p_io[0][0]->p_data->dim, p_self->p_io[0][0]->p_data->shape);
  return gxs;
}

static const FunctionMethods RESHAPE_METHODS = {
  reshape_forward,
  reshape_backward
};

void Reshape_init(Reshape* p_self, const int dim, const int* shape) {
  ((Function*)p_self)->p_methods = &RESHAPE_METHODS;
  Function_init((Function*)p_self, 1, 1);
  strcpy(((Function*)p_self)->name, "Reshape");
  p_self->dim = dim;
  p_self->shape = (int*)mymalloc(dim * sizeof(int));
  for (int i = 0; i < dim; i++)
    p_self->shape[i] = shape[i];
}