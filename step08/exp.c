#include "exp.h"
#include "function.h"
#include "variable.h"
#include <math.h>
#include <stdlib.h>

static float exp_forward(Function* const p_self, const float x) {
  return exp(x);
}

static float exp_backward(Function* const p_self, const float gy) {
  float gx = exp(p_self->p_io[0]->data) * gy;
  return gx;
}

static const FunctionMethods EXP_METHODS = {
  exp_forward,
  exp_backward
};

void Exp_init(Exp* p_self) {
  ((Function*)p_self)->p_methods = &EXP_METHODS;
  ((Function*)p_self)->p_io = (Variable**)malloc(2 * sizeof(Variable*));
  ((Function*)p_self)->p_io[0] = (Variable*)malloc(sizeof(Variable));
  ((Function*)p_self)->p_io[1] = (Variable*)malloc(sizeof(Variable));
}