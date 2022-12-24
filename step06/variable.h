#ifndef _VARIABLE_H_
#define _VARIABLE_H_

typedef struct variable {
  float data;
  float grad;
} Variable;

void Variable_init(Variable* p_self, const float data);

#endif // _VARIABLE_H_