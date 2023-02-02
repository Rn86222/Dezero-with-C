#include "transpose.h"
#include "function.h"
#include "functions.h"
#include "../variable/variable.h"
#include "../ndarray/ndarray.h"
#include "../utils/manage_memory/manage_memory.h"
#include <math.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static Ndarray* transpose_forward(Function* const p_self, const Ndarray* xs) {
  Ndarray* ys;
  ys = (Ndarray*)mymalloc(p_self->output_num * sizeof(Ndarray));
  ys[0] = Ndarray_transpose(xs[0], ((Transpose*)p_self)->axes);
  return ys;
}

static Variable** transpose_backward(Function* const p_self, Variable** gys) {
  Variable** gxs;
  gxs = (Variable**)mymalloc(p_self->input_num * sizeof(Variable*));
  int dim = p_self->p_io[0][0]->p_data->dim;
  int* reversed_axes;
  reversed_axes = (int*)malloc(dim * sizeof(int));
  for (int i = 0; i < dim; i++) {
    for (int j = 0; j < dim; j++) {
      if (i == ((Transpose*)p_self)->axes[j]) {
        reversed_axes[i] = j;
        break;
      }
    }
  }
  gxs[0] = transpose(gys[0], dim, reversed_axes);
  free(reversed_axes);
  return gxs;
}

static const FunctionMethods TRANSPOSE_METHODS = {
  transpose_forward,
  transpose_backward
};

void Transpose_init(Transpose* p_self, const int dim, const int* axes) {
  ((Function*)p_self)->p_methods = &TRANSPOSE_METHODS;
  Function_init((Function*)p_self, 1, 1);
  strcpy(((Function*)p_self)->name, "Transpose");
  p_self->dim = dim;
  p_self->axes = (int*)mymalloc(dim * sizeof(int));
  for (int i = 0; i < dim; i++)
    p_self->axes[i] = axes[i];
}