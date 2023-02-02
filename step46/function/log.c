#include "function.h"
#include "functions.h"
#include "../variable/variable.h"
#include "log.h"
#include "../ndarray/ndarray.h"
#include "../utils/manage_memory/manage_memory.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static Ndarray* log_forward(Function* const p_self, const Ndarray* xs) {
  Ndarray* ys;
  ys = (Ndarray*)mymalloc(p_self->output_num * sizeof(Ndarray));
  ys[0] = Ndarray_map(xs[0], log);
  return ys;
}

static Variable** log_backward(Function* const p_self, Variable** gys) {
  Variable** gxs;
  gxs = (Variable**)mymalloc(p_self->input_num * sizeof(Variable*));
  gxs[0] = divi(gys[0], p_self->p_io[0][0]);
  return gxs;
}

static const FunctionMethods LOG_METHODS = {
  log_forward,
  log_backward
};

void Log_init(Log* p_self) {
  ((Function*)p_self)->p_methods = &LOG_METHODS;
  Function_init((Function*)p_self, 1, 1);
  strcpy(((Function*)p_self)->name, "Log");
}