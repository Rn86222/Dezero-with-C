#ifndef _FUNCTION_H_
#define _FUNCTION_H_

typedef struct variable Variable;

struct functionMethods;

typedef struct function {
  const struct functionmethods *p_methods;
  Variable **p_io;
} Function;

typedef struct functionmethods {
  float (*forward)(Function* const, const float);
  float (*backward)(Function* const, const float);
} FunctionMethods;

Variable* Function_call(Function* p_self, Variable* p_input);
float Function_backward(Function* p_self, const float y);
void Function_destroy(Function* p_self);

#endif // _FUNCTION_H_