#ifndef _FUNCTION_H_
#define _FUNCTION_H_

typedef struct variable Variable;

struct functionmethods;

typedef struct function {
  const struct functionmethods *p_methods;
  Variable ***p_io;
  int input_num;
  int output_num;
} Function;

typedef struct functionmethods {
  float* (*forward)(Function* const, const float*);
  float* (*backward)(Function* const, const float*);
} FunctionMethods;

void Function_init(Function* p_self, const int input_num, const int output_num);
Variable** Function_call(Function* p_self, ...);
float* Function_backward(Function* p_self, const float* y);
void Function_destroy(Function* p_self);

#endif // _FUNCTION_H_