#include "function.h"

#ifndef _PFUNCTIONHEAP_H_
#define _PFUNCTIONHEAP_H_

typedef struct pfunctionheap {
  Function** heap;
  int last;
  int size;
} PFunctionHeap;

void PFunctionHeap_init(PFunctionHeap *p_self, const int size);
void PFunctionHeap_insert(PFunctionHeap *p_self, Function* func);
Function* PFunctionHeap_deletemax(PFunctionHeap *p_self);

#endif // _FUNCTIONHAP_H_