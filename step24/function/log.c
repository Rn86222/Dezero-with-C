#include "function.h"
#include "../variable/variable.h"
#include "log.h"
#include "../ndarray/ndarray.h"
#include <math.h>
#include <stdlib.h>

static Ndarray* log_forward(Function* const p_self, const Ndarray* xs) {
  Ndarray* ys;
  ys = (Ndarray*)malloc(p_self->output_num * sizeof(Ndarray));
  ys[0] = Ndarray_map(xs[0], log);
  return ys;
}

static Ndarray* log_backward(Function* const p_self, const Ndarray* gys) {
  Ndarray* gxs;
  gxs = (Ndarray*)malloc(p_self->input_num * sizeof(Ndarray));
  gxs[0] = Ndarray_div(gys[0], *(p_self->p_io[0][0]->p_data));
  return gxs;
}

static const FunctionMethods LOG_METHODS = {
  log_forward,
  log_backward
};

void Log_init(Log* p_self) {
  ((Function*)p_self)->p_methods = &LOG_METHODS;
  Function_init((Function*)p_self, 1, 1);
}