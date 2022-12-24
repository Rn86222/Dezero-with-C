#include "function.h"
#include "funcitonheap.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

static void FunctionHeap_swap(FunctionHeap *p_self, int a, int b) {
  Function tmp = p_self->heap[a];
  p_self->heap[a] = p_self->heap[b];
  p_self->heap[b] = tmp;
}

void FunctionHeap_init(FunctionHeap *p_self, const int size) {
  p_self->size = size;
  p_self->last = -1;
  p_self->heap = (Function*)malloc(size * sizeof(Function));
}

void FunctionHeap_insert(FunctionHeap *p_self, Function func) {
  assert(p_self->last < p_self->size - 1);
  p_self->heap[++p_self->last] = func;

  int i = p_self->last;
  while (i > 0) {
    if (p_self->heap[(i - 1) / 2].generation < p_self->heap[i].generation) {
      FunctionHeap_swap(p_self, (i - 1) / 2, i);
      i = (i - 1) / 2;
    } else {
      break;
    }
  }
}

Function FunctionHeap_deletemax(FunctionHeap *p_self) {
  Function func = p_self->heap[0];
  p_self->heap[0] = p_self->heap[p_self->last--];
  int i = 0;
  while (2 * i + 1 <= p_self->last) {
    if (p_self->heap[i].generation < p_self->heap[i * 2 + 1].generation) {
      if (i * 2 + 2 <= p_self->last && p_self->heap[i * 2 + 2].generation < p_self->heap[i * 2 + 1].generation) {
        FunctionHeap_swap(p_self, i, i * 2 + 2);
        i = i * 2 + 2;
      } else {
        FunctionHeap_swap(p_self, i, i * 2 + 1);
        i = i * 2 + 1;
      }
    } else if (p_self->heap[i].generation < p_self->heap[i * 2 + 2].generation){
      FunctionHeap_swap(p_self, i, i * 2 + 2);
      i = i * 2 + 2;
    } else {
      return func;
    }
  }
  return func;
}

void FunctionHeap_destroy(FunctionHeap* p_self) {
  p_self->size = 0;
  p_self->last = -1;
  free(p_self->heap);
}