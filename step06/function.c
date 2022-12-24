#include "function.h"
#include "variable.h"

Variable Function_call(Function* p_self, const Variable input) {
  p_self->input = input;
  float y = p_self->p_methods->forward(p_self, input.data);
  Variable output;
  Variable_init(&output, y);
  return output;
}

float Function_backward(Function* p_self, const float y) {
  float dy = p_self->p_methods->backward(p_self, y);
  return dy;
}