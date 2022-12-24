#include "function.h"

#ifndef _FUNCTIONSTACK_H_
#define _FUNCTIONSTACK_H_

typedef struct functionstack {
  Function* stack;
  int last;
  int size;
} FunctionStack;

void FunctionStack_init(FunctionStack* p_self, const int size);
void FunctionStack_push(FunctionStack* p_self, Function func);
Function FunctionStack_pop(FunctionStack* p_self);

#endif // _FUNCTIONSTACK_H_