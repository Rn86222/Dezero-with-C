#include "function.h"
#include "../variable/variable.h"
#include "../ndarray/ndarray.h"
#include <stdlib.h>
#include <string.h>
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

Variable** Function_call(Function* p_self, const char* name, ...) {
  va_list va_ptr;
  va_start(va_ptr, name);
  Ndarray* xs;
  xs = (Ndarray*)malloc(p_self->input_num * sizeof(Ndarray));
  int max_gen = 0;
  for (int i = 0; i < p_self->input_num; i++) {
    p_self->p_io[0][i] = va_arg(va_ptr, Variable*);
    xs[i] = *(p_self->p_io[0][i]->p_data);
    if (max_gen < p_self->p_io[0][i]->generation) {
      max_gen = p_self->p_io[0][i]->generation;
    }
  }
  p_self->generation = max_gen;
  va_end(va_ptr);
  int name_len = strlen(name);
  char y_name[100];
  bool noname = (name_len == 0);
  if (!noname) {
    strcpy(y_name, name);
    y_name[name_len] = '_';
  } else {
    y_name[0] = '\0';
  }
  Ndarray* ys;
  ys = (Ndarray*)malloc(p_self->output_num * sizeof(Ndarray));
  for (int i = 0; i < p_self->output_num; i++) {
    if (!noname)
      sprintf(y_name+name_len+1, "%d", i);
    ys[i] = (p_self->p_methods->forward(p_self, xs))[i];
    Variable_init(p_self->p_io[1][i], ys[i], y_name);
    Variable_set_creator(p_self->p_io[1][i], p_self);
  }
  free(xs);
  free(ys);
  return p_self->p_io[1];
}

Variable** Function_call_with_Lconstant(Function* p_self, const char* name, const float constant, Variable* p_input) {
  assert(p_self->input_num == 2);
  Ndarray* xs;
  xs = (Ndarray*)malloc(2 * sizeof(Ndarray));
  p_self->p_io[0][1] = p_input;
  xs[1] = *(p_input->p_data);
  p_self->generation = p_input->generation;

  Variable* const_v;
  const_v = (Variable*)malloc(sizeof(Variable));
  Variable_init_as_one_constant(const_v, constant);
  p_self->p_io[0][0] = const_v;
  xs[0] = *(const_v->p_data);

  int name_len = strlen(name);
  char y_name[100];
  bool noname = (name_len == 0);
  if (!noname) {
    strcpy(y_name, name);
    y_name[name_len] = '_';
  } else {
    y_name[0] = '\0';
  }
  Ndarray* ys;
  ys = (Ndarray*)malloc(p_self->output_num * sizeof(Ndarray));
  for (int i = 0; i < p_self->output_num; i++) {
    if (!noname)
      sprintf(y_name+name_len+1, "%d", i);
    ys[i] = (p_self->p_methods->forward(p_self, xs))[i];
    Variable_init(p_self->p_io[1][i], ys[i], y_name);
    Variable_set_creator(p_self->p_io[1][i], p_self);
  }
  free(xs);
  free(ys);
  return p_self->p_io[1];
}

Variable** Function_call_with_Rconstant(Function* p_self, const char* name, Variable* p_input, const float constant) {
  assert(p_self->input_num == 2);
  Ndarray* xs;
  xs = (Ndarray*)malloc(2 * sizeof(Ndarray));
  p_self->p_io[0][0] = p_input;
  xs[0] = *(p_input->p_data);
  p_self->generation = p_input->generation;

  Variable* const_v;
  const_v = (Variable*)malloc(sizeof(Variable));
  Variable_init_as_one_constant(const_v, constant);
  p_self->p_io[0][1] = const_v;
  xs[1] = *(const_v->p_data);

  int name_len = strlen(name);
  char y_name[100];
  bool noname = (name_len == 0);
  if (!noname) {
    strcpy(y_name, name);
    y_name[name_len] = '_';
  }  else {
    y_name[0] = '\0';
  }
  Ndarray* ys;
  ys = (Ndarray*)malloc(p_self->output_num * sizeof(Ndarray));
  for (int i = 0; i < p_self->output_num; i++) {
    if (!noname)
      sprintf(y_name+name_len+1, "%d", i);
    ys[i] = (p_self->p_methods->forward(p_self, xs))[i];
    Variable_init(p_self->p_io[1][i], ys[i], y_name);
    Variable_set_creator(p_self->p_io[1][i], p_self);
  }
  free(xs);
  free(ys);
  return p_self->p_io[1];
}

// Ndarray* Function_backward(Function* p_self, const Ndarray* ys) {
//   Ndarray* dys;
//   dys = (Ndarray*)malloc(p_self->input_num * sizeof(Ndarray));
//   for (int i = 0; i < p_self->input_num; i++) {
//     Ndarray_copy(&dys[i], (p_self->p_methods->backward(p_self, ys))[i]);
//   }
//   return dys;
// }

void Function_destroy(Function* p_self) {
  for (int i = 0; i < p_self->input_num; i++) {
    if (p_self->p_io[0][i] != NULL); {
      free(p_self->p_io[0][i]);
      p_self->p_io[0][i] = NULL;
    }
  }
  for (int i = 0; i < p_self->output_num; i++) {
    if (p_self->p_io[1][i] != NULL) {
      free(p_self->p_io[1][i]);
      p_self->p_io[1][i] = NULL;
    }
  }
  if (p_self->p_io[0] != NULL) {
    free(p_self->p_io[0]);
    p_self->p_io[0] = NULL;
  }
  if (p_self->p_io[1] != NULL) {
    free(p_self->p_io[1]);
    p_self->p_io[1] = NULL;
  }
  if (p_self->p_io != NULL) {
    free(p_self->p_io);
    p_self->p_io = NULL;
  }
}