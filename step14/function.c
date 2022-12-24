#include "function.h"
#include "variable.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <stdarg.h>

void Function_init(Function* p_self, const int input_num, const int output_num) {
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

Variable** Function_call(Function* p_self, ...) {
  va_list va_ptr;
  va_start(va_ptr, p_self);
  float* xs;
  xs = (float*)malloc(p_self->input_num * sizeof(float));
  for (int i = 0; i < p_self->input_num; i++) {
    p_self->p_io[0][i] = va_arg(va_ptr, Variable*);
    xs[i] = p_self->p_io[0][i]->data;
  }
  va_end(va_ptr);

  float* ys;
  ys = (float*)malloc(p_self->output_num * sizeof(float));
  ys = p_self->p_methods->forward(p_self, xs);
  for (int i = 0; i < p_self->output_num; i++) {
    Variable_init(p_self->p_io[1][i], ys[i]);
    Variable_set_creator(p_self->p_io[1][i], p_self);
  }
  free(ys);
  return p_self->p_io[1];
}

float* Function_backward(Function* p_self, const float* ys) {
  float* dy;
  dy = (float*)malloc(p_self->output_num * sizeof(float));
  dy = p_self->p_methods->backward(p_self, ys);
  return dy;
}

void Function_destroy(Function* p_self) {
  for (int i = 0; i < p_self->input_num; i++) {
    assert(p_self->p_io[0][i] != NULL);
    free(p_self->p_io[0][i]);
  }
  for (int i = 0; i < p_self->output_num; i++) {
    assert(p_self->p_io[1][i] != NULL);
    free(p_self->p_io[1][i]);
  }
  assert(p_self->p_io[0] != NULL && p_self->p_io[1] != NULL && p_self->p_io != NULL);
  free(p_self->p_io[0]);
  free(p_self->p_io[1]);
  free(p_self->p_io);
}