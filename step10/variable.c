#include "variable.h"
#include "function.h"
#include "functionstack.h"
#include "constant.h"
#include <stdio.h>

void Variable_init(Variable* p_self, const float data) {
  p_self->data = data;
  p_self->grad = 0.0;
  p_self->creator_exists = FALSE;
  p_self->grad_exists = FALSE;
}

void Variable_set_creator(Variable* p_self, Function* func) {
  p_self->p_creator = func;
  p_self->creator_exists = TRUE;
}

void Variable_backward(Variable* p_self) {
  if (p_self->creator_exists == FALSE) {
    return;
  }
  if (p_self->grad_exists == FALSE) {
    p_self->grad = 1.0;
    p_self->grad_exists = TRUE;
  }
  FunctionStack fs;
  FunctionStack_init(&fs, FUNCTION_STACK_SIZE);
  FunctionStack_push(&fs, *(p_self->p_creator));

  Function f;
  while (fs.last != -1) {
    f = FunctionStack_pop(&fs);
    Variable* x = f.p_io[0];
    Variable* y = f.p_io[1];
    x->grad = f.p_methods->backward(&f, y->grad);
    if (x->creator_exists) {
      FunctionStack_push(&fs, *(x->p_creator));
    }
  }
}