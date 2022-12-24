#include "function.h"
#include "variable.h"
#include "ndarray.h"
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
  Ndarray* xs;
  xs = (Ndarray*)malloc(p_self->input_num * sizeof(Ndarray));
  int max_gen = 0;

  for (int i = 0; i < p_self->input_num; i++) {
    p_self->p_io[0][i] = va_arg(va_ptr, Variable*);
    Ndarray_copy(&xs[i], *(p_self->p_io[0][i]->p_data));
    if (max_gen < p_self->p_io[0][i]->generation) {
      max_gen = p_self->p_io[0][i]->generation;
    }
  }
  p_self->generation = max_gen;
  va_end(va_ptr);

  Ndarray* ys;
  ys = (Ndarray*)malloc(p_self->output_num * sizeof(Ndarray));
  for (int i = 0; i < p_self->output_num; i++) {
    Ndarray_copy(&ys[i], (p_self->p_methods->forward(p_self, xs))[i]);
    Variable_init(p_self->p_io[1][i], ys[i]);
    Variable_set_creator(p_self->p_io[1][i], p_self);
  }
  free(xs);
  free(ys);
  return p_self->p_io[1];
}

Ndarray* Function_backward(Function* p_self, const Ndarray* ys) {
  Ndarray* dys;
  dys = (Ndarray*)malloc(p_self->input_num * sizeof(Ndarray));
  for (int i = 0; i < p_self->input_num; i++) {
    Ndarray_copy(&dys[i], (p_self->p_methods->backward(p_self, ys))[i]);
  }
  return dys;
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