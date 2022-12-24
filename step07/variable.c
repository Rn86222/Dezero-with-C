#include "variable.h"
#include "function.h"
#include <stdio.h>

void Variable_init(Variable* p_self, const float data) {
  p_self->data = data;
  p_self->grad = 0.0;
  p_self->creator_exists = 0;
}

void Variable_set_creator(Variable* p_self, Function* func) {
  p_self->p_creator = func;
  p_self->creator_exists = 1;
}

void Variable_backward(Variable* p_self) {
  if (p_self->creator_exists) {
    Function* f = p_self->p_creator;
    Variable* x = p_self->p_creator->p_io[0];
    x->grad = f->p_methods->backward(f, p_self->grad);
    Variable_backward(x);
  }
}