#include "layer.h"
#include <stdarg.h>
#include <assert.h>
#include <stdlib.h>

void Layer_init(Layer* p_self, const int input_num, const int output_num, const int max_param_num) {
  p_self->max_param_num = max_param_num;
  p_self->param_num = 0;
  p_self->params = (Variable**)malloc(max_param_num * sizeof(Variable*));
  p_self->p_io = (Variable***)malloc(2 * sizeof(Variable**));
  p_self->p_io[0] = (Variable**)malloc(input_num * sizeof(Variable*));
  p_self->p_io[1] = (Variable**)malloc(output_num * sizeof(Variable*));
  p_self->input_num = input_num;
  p_self->output_num = output_num;
  assert(p_self->p_io[0] != NULL && p_self->p_io[1] != NULL && p_self->p_io != NULL);
  
  for (int i = 0; i < input_num; i++) {
    p_self->p_io[0][i] = (Variable*)malloc(sizeof(Variable));
    assert(p_self->p_io[0][i] != NULL);
  }
  for (int i = 0; i < output_num; i++) {
    p_self->p_io[1][i] = (Variable*)malloc(sizeof(Variable));
    assert(p_self->p_io[1][i] != NULL);
  }
}

Variable** Layer_call(Layer* p_self, ...) {
  va_list va_ptr;
  va_start(va_ptr, p_self);
  for (int i = 0; i < p_self->input_num; i++)
    p_self->p_io[0][i] = va_arg(va_ptr, Variable*);
  va_end(va_ptr);
  Variable** ys;
  ys = p_self->p_methods->forward(p_self, p_self->p_io[0]);
  for (int i = 0; i < p_self->output_num; i++)
    p_self->p_io[1][i] = ys[i];
  
  return p_self->p_io[1];
}

void Layer_cleargrads(Layer* p_self) {
  for (int i = 0; i < p_self->param_num; i++)
    Variable_cleargrad(p_self->params[i]);
}