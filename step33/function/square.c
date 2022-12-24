#include "square.h"
#include "function.h"
#include "functions.h"
#include "../variable/variable.h"
#include "../ndarray/ndarray.h"
#include <math.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

static Ndarray* square_forward(Function* const p_self, const Ndarray* xs) {
  Ndarray* ys;
  ys = (Ndarray*)malloc(p_self->output_num * sizeof(Ndarray));
  ys[0] = Ndarray_square(xs[0]);
  return ys;
}

static Variable** square_backward(Function* const p_self, Variable** gys) {
  Variable** gxs;
  gxs = (Variable**)malloc(p_self->input_num * sizeof(Variable*));
  gxs[0] = mul(gys[0], mulLC(2.0, p_self->p_io[0][0]));
  return gxs;
}

static const FunctionMethods SQUARE_METHODS = {
  square_forward,
  square_backward
};

void Square_init(Square* p_self) {
  ((Function*)p_self)->p_methods = &SQUARE_METHODS;
  Function_init((Function*)p_self, 1, 1);
  strcpy(((Function*)p_self)->name, "Square");
}
