#include "functionstack.h"
#include "function.h"
#include <stdio.h>
#include <stdlib.h>

void FunctionStack_init(FunctionStack* p_self, const int size) {
  p_self->last = -1;
  p_self->size = size;
  p_self->stack = (Function* )malloc(size * sizeof(Function));
}

void FunctionStack_push(FunctionStack* p_self, Function func) {
  if (p_self->last >= p_self->size - 1) {
    printf("FunctionStack_push error: stack overflow.\n");
    return;
  }
  p_self->stack[++p_self->last] = func;
}

Function FunctionStack_pop(FunctionStack* p_self) {
  if (p_self->last == -1) {
    printf("FunctionStack_pop error: no function in stack.\n");
    Function tmp;
    return tmp;
  }
  return p_self->stack[p_self->last--];
}