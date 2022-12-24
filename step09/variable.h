#ifndef _VARIABLE_H_
#define _VARIABLE_H_

typedef struct function Function;

typedef struct variable {
  float data;
  float grad;
  int creator_exists;
  int grad_exists;
  Function* p_creator;
} Variable;

void Variable_init(Variable* p_self, const float data);
void Variable_set_creator(Variable* p_self, Function* func);
void Variable_backward(Variable* p_self);

#endif // _VARIABLE_H_