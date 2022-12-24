#include "../ndarray/ndarray.h"

#ifndef _FUNCTION_H_
#define _FUNCTION_H_

typedef struct variable Variable;

struct functionmethods;

typedef struct function {
  const struct functionmethods *p_methods;
  Variable ***p_io;
  int input_num;
  int output_num;
  int generation;
  char name[100];
} Function;

typedef struct functionmethods {
  Ndarray* (*forward)(Function* const, const Ndarray*);
  Variable** (*backward)(Function* const, Variable**);
} FunctionMethods;

void Function_init(Function* p_self, const int input_num, const int output_num);
Variable** Function_call(Function* p_self, const char* name, ...);
Variable** Function_call_with_Lconstant(Function* p_self, const char* name, const float constant, Variable* p_input);
Variable** Function_call_with_Rconstant(Function* p_self, const char* name, Variable* p_input, const float constant);
// Ndarray* Function_backward(Function* p_self, const Ndarray* ys);
void Function_destroy(Function* p_self);

#endif // _FUNCTION_H_