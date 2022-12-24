#include "square.h"
#include "function.h"
#include "variable.h"
#include <math.h>
#include <assert.h>
#include <stdlib.h>

static float* square_forward(Function* const p_self, const float* xs) {
  float* ys;
  ys = (float*)malloc(sizeof(float));
  ys[0] = pow(xs[0], 2);
  return ys;
}

static float* square_backward(Function* const p_self, const float* gys) {
  float* gxs;
  gxs = (float*)malloc(sizeof(float));
  gxs[0] = 2 * p_self->p_io[0][0]->data * gys[0];
  return gxs;
}

static const FunctionMethods SQUARE_METHODS = {
  square_forward,
  square_backward
};

void Square_init(Square* p_self) {
  ((Function*)p_self)->p_methods = &SQUARE_METHODS;
  Function_init((Function*)p_self, 1, 1);
}
