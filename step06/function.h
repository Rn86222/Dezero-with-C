#include "variable.h"

#ifndef _FUNCTION_H_
#define _FUNCTION_H_

struct functionMethods;

typedef struct function {
  const struct functionmethods *p_methods;
  Variable input;
} Function;

typedef struct functionmethods {
  float (*forward)(Function* const, const float);
  float (*backward)(Function* const, const float);
} FunctionMethods;

Variable Function_call(Function* p_self, const Variable input);
float Function_backward(Function* p_self, const float y);

#endif // _FUNCTION_H_