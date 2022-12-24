#include "constant.h"
#include "ndarray.h"

#ifndef _VARIABLE_H_
#define _VARIABLE_H_

typedef struct function Function;

typedef struct variable {
  Ndarray* p_data;
  Ndarray* p_grad;
  int num;
  bool creator_exists;
  bool grad_exists;
  int generation;
  Function* p_creator;
} Variable;

void Variable_init(Variable* p_self, const Ndarray data);
void Variable_set_creator(Variable* p_self, Function* func);
void Variable_backward(Variable* p_self);
void Variable_cleargrad(Variable* p_self);
void Variable_destroy(Variable* p_self, const bool destroyAll);

#endif // _VARIABLE_H_