#include "variable.h"
#include "function.h"
#include "funcitonheap.h"
#include "constant.h"
#include "ndarray.h"
#include <stdio.h>
#include <stdlib.h>

void Variable_init(Variable* p_self, const Ndarray data) {
  p_self->p_data = (Ndarray*)malloc(sizeof(Ndarray));
  p_self->p_grad = (Ndarray*)malloc(sizeof(Ndarray));
  Ndarray_copy(p_self->p_data, data);
  Ndarray_init_as_zeros(p_self->p_grad, data.dim, data.shape);
  p_self->creator_exists = FALSE;
  p_self->grad_exists = FALSE;
  p_self->generation = 0;
}

void Variable_set_creator(Variable* p_self, Function* func) {
  p_self->p_creator = func;
  p_self->creator_exists = TRUE;
  p_self->generation = func->generation + 1;
}

void Variable_backward(Variable* p_self) {
  if (p_self->creator_exists == FALSE) {
    return;
  }
  if (p_self->grad_exists == FALSE) {
    for (int i = 0; i < p_self->p_grad->size; i++)
      p_self->p_grad->array[i] = 1.0;
    p_self->grad_exists = TRUE;
  }
  FunctionHeap fh;
  FunctionHeap_init(&fh, FUNCTION_HEAP_SIZE);
  FunctionHeap_insert(&fh, *(p_self->p_creator));
  Function f;
  Function** seen_fs;
  seen_fs = (Function**)malloc(FUNCTION_HEAP_SIZE * sizeof(Function*));
  seen_fs[0] = p_self->p_creator;
  int cnt = 1;
  while (fh.last != -1) {
    f = FunctionHeap_deletemax(&fh);
    Ndarray* gys;
    gys = (Ndarray*)malloc(f.output_num * sizeof(Ndarray));
    for (int i = 0; i < f.output_num; i++) {
      Ndarray_copy(&gys[i], *(f.p_io[1][i]->p_grad));
    }
    Ndarray* gxs;
    gxs = (Ndarray*)malloc(f.input_num * sizeof(Ndarray));
    for (int i = 0; i < f.input_num; i++) {
      Ndarray_copy(&gxs[i], (f.p_methods->backward(&f, gys))[i]);
    }

    for (int i = 0; i < f.input_num; i++) {
      if (f.p_io[0][i]->grad_exists) {
        Ndarray_copy(f.p_io[0][i]->p_grad, Ndarray_add(*(f.p_io[0][i]->p_grad), gxs[i]));
      } else {
        Ndarray_copy(f.p_io[0][i]->p_grad, gxs[i]);
        f.p_io[0][i]->grad_exists = TRUE;
      }
      if (f.p_io[0][i]->creator_exists) {
        bool found = FALSE;
        for (int j = 0; j < cnt; j++) {
          if (seen_fs[j] == f.p_io[0][i]->p_creator) {
            found = TRUE;
            break;
          }
        }
        if (!found) {
          FunctionHeap_insert(&fh, *(f.p_io[0][i]->p_creator));
          seen_fs[cnt++] = f.p_io[0][i]->p_creator;
        }
      }
    }
    free(gxs);
    free(gys);
  }
  free(seen_fs);
  FunctionHeap_destroy(&fh);
}

void Variable_cleargrad(Variable* p_self) {
  Ndarray_init_as_zeros(p_self->p_grad, p_self->p_grad->dim, p_self->p_grad->shape);
  p_self->grad_exists = FALSE;
}

void Variable_destroy(Variable* p_self, const bool destroyAll) {
  Ndarray_destroy(p_self->p_data);
  Ndarray_destroy(p_self->p_grad);
  if (!destroyAll || p_self->creator_exists == FALSE)
    return;
  FunctionHeap fh;
  FunctionHeap_init(&fh, FUNCTION_HEAP_SIZE);
  FunctionHeap_insert(&fh, *(p_self->p_creator));
  Function f;
  Variable** seen_is;
  seen_is = (Variable**)malloc(FUNCTION_HEAP_SIZE * sizeof(Variable*));
  int cnt = 0;
  while (fh.last != -1) {
    f = FunctionHeap_deletemax(&fh);
    for (int i = 0; i < f.input_num; i++) {
      bool found = FALSE;
      for (int j = 0; j < cnt; j++) {
        if (seen_is[j] == f.p_io[0][i])
          found = TRUE;
      }
      if (!found) {
        seen_is[cnt++] = f.p_io[0][i];
        Ndarray_destroy(f.p_io[0][i]->p_data);
        Ndarray_destroy(f.p_io[0][i]->p_grad);
        if (f.p_io[0][i]->creator_exists)
          FunctionHeap_insert(&fh, *(f.p_io[0][i]->p_creator));
      }
    }
  }
  FunctionHeap_destroy(&fh);
  free(seen_is);
}
