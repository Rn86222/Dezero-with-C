#include "ndarray.h"

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
} Function;

typedef struct functionmethods {
  Ndarray* (*forward)(Function* const, const Ndarray*);
  Ndarray* (*backward)(Function* const, const Ndarray*);
} FunctionMethods;

void Function_init(Function* p_self, const int input_num, const int output_num);
Variable** Function_call(Function* p_self, ...);
Ndarray* Function_backward(Function* p_self, const Ndarray* ys);
void Function_destroy(Function* p_self);

#endif // _FUNCTION_H_