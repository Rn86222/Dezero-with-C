#include "variable.h"

#ifndef _FUNCTION_H_
#define _FUNCTION_H_

struct functionMethods;

typedef struct function {
  const struct functionmethods *p_methods;
} Function;

typedef struct functionmethods {
  float (*forward)(Function* const, const float);
} FunctionMethods;

Variable Function_call(Function* p_self, const Variable input);

#endif // _FUNCTION_H_