#include "square.h"
#include "function.h"
#include "variable.h"
#include <stdlib.h>
#include <math.h>

static float square_forward(Function* const p_self, const float x) {
  return pow(x, 2);
}

static float square_backward(Function* const p_self, const float gy) {
  float gx = 2 * p_self->p_io[0]->data * gy;
  return gx;
}

static const FunctionMethods SQUARE_METHODS = {
  square_forward,
  square_backward
};

void Square_init(Square* p_self) {
  ((Function*)p_self)->p_methods = &SQUARE_METHODS;
  ((Function*)p_self)->p_io = (Variable**)malloc(2 * sizeof(Variable*));
  ((Function*)p_self)->p_io[0] = (Variable*)malloc(sizeof(Variable));
  ((Function*)p_self)->p_io[1] = (Variable*)malloc(sizeof(Variable));
}
