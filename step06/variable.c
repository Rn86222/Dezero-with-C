#include "variable.h"

void Variable_init(Variable* p_self, const float data) {
  p_self->data = data;
  p_self->grad = 0.0;
}