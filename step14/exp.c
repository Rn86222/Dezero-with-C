#include "exp.h"
#include "function.h"
#include "variable.h"
#include <math.h>
#include <assert.h>
#include <stdlib.h>

static float* exp_forward(Function* const p_self, const float* xs) {
  float* ys;
  ys = (float*)malloc(sizeof(float));
  ys[0] = exp(xs[0]);
  return ys;
}

static float* exp_backward(Function* const p_self, const float* gys) {
  float* gxs;
  gxs = (float*)malloc(sizeof(float));
  gxs[0] = exp(p_self->p_io[0][0]->data) * gys[0];
  return gxs;
}

static const FunctionMethods EXP_METHODS = {
  exp_forward,
  exp_backward
};

void Exp_init(Exp* p_self) {
  ((Function*)p_self)->p_methods = &EXP_METHODS;
  Function_init((Function*)p_self, 1, 1);
}