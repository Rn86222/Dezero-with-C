#include "functionstack.h"
#include "function.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

void FunctionStack_init(FunctionStack* p_self, const int size) {
  p_self->last = -1;
  p_self->size = size;
  p_self->stack = (Function* )malloc(size * sizeof(Function));
  assert(p_self->stack != NULL);
}

void FunctionStack_push(FunctionStack* p_self, Function func) {
  assert(p_self->last < p_self->size - 1);
  p_self->stack[++p_self->last] = func;
}

Function FunctionStack_pop(FunctionStack* p_self) {
  assert(p_self->last >= 0);
  return p_self->stack[p_self->last--];
}