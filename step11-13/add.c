#include "function.h"
#include "variable.h"
#include "add.h"
#include <stdlib.h>

static float* add_forward(Function* const p_self, const float* xs) {
  float* ys;
  ys = (float*)malloc(sizeof(float));
  ys[0] = xs[0] + xs[1];
  return ys;
}

static float* add_backward(Function* const p_self, const float* gy) {
  float* gys;
  gys = (float*)malloc(2 * sizeof(float));
  gys[0] = gy[0];  gys[1] = gy[0];
  return gys;
}

static const FunctionMethods ADD_METHODS = {
  add_forward,
  add_backward
};

void Add_init(Add* p_self) {
  ((Function*)p_self)->p_methods = &ADD_METHODS;
  Function_init((Function*)p_self, 2, 1);
}