#include "exp.h"
#include "function.h"
#include <math.h>

static float exp_forward(Function* const p_self, const float x) {
  return exp(x);
}

static const FunctionMethods EXP_METHODS = {
  exp_forward
};

void Exp_init(Exp* p_self) {
  ((Function*)p_self)->p_methods = &EXP_METHODS;
}