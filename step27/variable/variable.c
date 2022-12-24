#include "variable.h"
#include "../function/function.h"
#include "../function/functionheap.h"
#include "../macro/constant.h"
#include "../ndarray/ndarray.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

void Variable_init(Variable* p_self, const Ndarray data, const char* name) {
  p_self->p_data = (Ndarray*)malloc(sizeof(Ndarray));
  p_self->p_grad = (Ndarray*)malloc(sizeof(Ndarray));
  Ndarray_copy(p_self->p_data, data);
  Ndarray_init_as_zeros(p_self->p_grad, data.dim, data.shape);
  strcpy(p_self->name, name);
  p_self->creator_exists = FALSE;
  p_self->grad_exists = FALSE;
  p_self->generation = 0;
}

void Variable_init_as_one_constant(Variable* p_self, const float value) {
  int shape[1] = {1};
  p_self->p_data = (Ndarray*)malloc(sizeof(Ndarray));
  p_self->p_grad = (Ndarray*)malloc(sizeof(Ndarray));
  p_self->p_data->array = (float*)malloc(sizeof(float));
  p_self->p_data->shape = (int*)malloc(sizeof(int));
  p_self->p_data->array[0] = value;
  p_self->p_data->dim = 1;
  p_self->p_data->shape[0] = 1;
  p_self->p_data->size = 1;
  Ndarray_init_as_zeros(p_self->p_grad, 1, shape);
  strcpy(p_self->name, "");
  p_self->creator_exists = FALSE;
  p_self->grad_exists = FALSE;
  p_self->generation = 0;
}

void Variable_set_creator(Variable* p_self, Function* func) {
  p_self->p_creator = func;
  p_self->creator_exists = TRUE;
  p_self->generation = func->generation + 1;
}

void Variable_backward(Variable* p_self, const bool retain_grad) {
  if (p_self->creator_exists == FALSE) {
    return;
  }
  if (p_self->grad_exists == FALSE) {
    p_self->p_grad = (Ndarray*)malloc(sizeof(Ndarray));
    Ndarray_init(p_self->p_grad, p_self->p_data->dim, p_self->p_data->shape);
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
        if (found == FALSE) {
          FunctionHeap_insert(&fh, *(f.p_io[0][i]->p_creator));
          seen_fs[cnt++] = f.p_io[0][i]->p_creator;
        }
      }
    }
    if (retain_grad == FALSE) {
      for (int i = 0; i < f.output_num; i++) {
        if (f.p_io[1][i]->p_grad != NULL)
          free(f.p_io[1][i]->p_grad);
        f.p_io[1][i]->grad_exists = FALSE;
      }
    }
    free(gys);
    free(gxs);
  }
  free(seen_fs);
}

void Variable_cleargrad(Variable* p_self) {
  if (p_self->grad_exists) {
    Ndarray_init_as_zeros(p_self->p_grad, p_self->p_grad->dim, p_self->p_grad->shape);
    p_self->grad_exists = FALSE;
  }
}

void Variable_print(Variable* p_self) {
  printf("name: %s\n", p_self->name);
  printf("generation: %d\n", p_self->generation);
  printf("shape: [");
  for (int i = 0; i < p_self->p_data->dim - 1; i++) {
    printf("%d, ", p_self->p_data->shape[i]);
  }
  printf("%d]\n", p_self->p_data->shape[p_self->p_data->dim-1]);
  printf("data:\n");
  Ndarray_print(p_self->p_data);
}