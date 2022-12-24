#include "function.h"
#include "../variable/variable.h"
#include "add.h"
#include "../ndarray/ndarray.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static Ndarray* add_forward(Function* const p_self, const Ndarray* xs) {
  Ndarray* ys;
  ys = (Ndarray*)malloc(p_self->output_num * sizeof(Ndarray));
  ys[0] = Ndarray_add(xs[0], xs[1]);
  return ys;
}

static Ndarray* add_backward(Function* const p_self, const Ndarray* gys) {
  Ndarray* gxs;
  gxs = (Ndarray*)malloc(p_self->input_num * sizeof(Ndarray));
  gxs[0] = gys[0];  gxs[1] = gys[0];
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
