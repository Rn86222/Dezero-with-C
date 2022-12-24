#include "constant.h"
#include "ndarray.h"

#ifndef _VARIABLE_H_
#define _VARIABLE_H_

typedef struct function Function;

typedef struct variable {
  Ndarray* p_data;
  Ndarray* p_grad;
  bool creator_exists;
  bool grad_exists;
  int generation;
  Function* p_creator;
  char name[100];
} Variable;

void Variable_init(Variable* p_self, const Ndarray data, const char* name);
void Variable_set_creator(Variable* p_self, Function* func);
void Variable_backward(Variable* p_self, const bool retain_grad);
void Variable_cleargrad(Variable* p_self);
void Variable_print(Variable* p_self);

#endif // _VARIABLE_H_