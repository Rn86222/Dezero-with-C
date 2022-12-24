#include "function.h"
#include "variable.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

void Function_init(Function* p_self) {
  p_self->p_io = (Variable**)malloc(2 * sizeof(Variable*));
  p_self->p_io[0] = (Variable*)malloc(sizeof(Variable));
  p_self->p_io[1] = (Variable*)malloc(sizeof(Variable));
  assert(p_self->p_io[0] != NULL && p_self->p_io[1] != NULL && p_self->p_io != NULL);
}

Variable* Function_call(Function* p_self, Variable* p_input) {
  p_self->p_io[0] = p_input;
  float y = p_self->p_methods->forward(p_self, p_input->data);
  Variable_init(p_self->p_io[1], y);
  Variable_set_creator(p_self->p_io[1], p_self);
  return p_self->p_io[1];
}

float Function_backward(Function* p_self, const float y) {
  float dy = p_self->p_methods->backward(p_self, y);
  return dy;
}

void Function_destroy(Function* p_self) {
  assert(p_self->p_io[0] != NULL && p_self->p_io[1] != NULL && p_self->p_io != NULL);
  free(p_self->p_io[0]);
  free(p_self->p_io[1]);
  free(p_self->p_io);
}