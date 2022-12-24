#include "function.h"

#ifndef _FUNCTIONHEAP_H_
#define _FUNCTIONHEAP_H_

typedef struct functionheap {
  Function* heap;
  int last;
  int size;
} FunctionHeap;

void FunctionHeap_init(FunctionHeap *p_self, const int size);
void FunctionHeap_insert(FunctionHeap *p_self, Function func);
Function FunctionHeap_deletemax(FunctionHeap *p_self);

#endif // _FUNCTIONHAP_H_