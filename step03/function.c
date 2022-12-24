#include "function.h"
#include "variable.h"

Variable Function_call(Function* p_self, const Variable input) {
  float y = p_self->p_methods->forward(p_self, input.data);
  Variable output;
  Variable_init(&output, y);
  return output;
}
