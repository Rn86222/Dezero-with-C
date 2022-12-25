#include "variable.h"
#include "../function/functions.h"
#include "../macro/constant.h"
#include "../ndarray/ndarray.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>

void Variable_init(Variable* p_self, const Ndarray data, const char* name) {
  p_self->p_data = (Ndarray*)malloc(sizeof(Ndarray));
  p_self->p_grad = (Variable*)malloc(sizeof(Variable));
  *(p_self->p_data) = data;
  strcpy(p_self->name, name);
  p_self->creator_exists = FALSE;
  p_self->grad_exists = FALSE;
  p_self->isConst = FALSE;
  p_self->isParam = FALSE;
  p_self->generation = 0;
}

void Variable_init_as_param(Variable* p_self, const Ndarray data, const char* name) {
  p_self->p_data = (Ndarray*)malloc(sizeof(Ndarray));
  p_self->p_grad = (Variable*)malloc(sizeof(Variable));
  *(p_self->p_data) = data;
  strcpy(p_self->name, name);
  p_self->creator_exists = FALSE;
  p_self->grad_exists = FALSE;
  p_self->isConst = FALSE;
  p_self->isParam = TRUE;
  p_self->generation = 0;
}

void Variable_init_as_one_constant(Variable* p_self, const float value) {
  int shape[1] = {1};
  p_self->p_data = (Ndarray*)malloc(sizeof(Ndarray));
  p_self->p_grad = (Variable*)malloc(sizeof(Variable));
  p_self->p_data->array = (float*)malloc(sizeof(float));
  p_self->p_data->shape = (int*)malloc(sizeof(int));
  p_self->p_data->array[0] = value;
  p_self->p_data->dim = 0;
  p_self->p_data->shape[0] = 1;
  p_self->p_data->size = 1;
  char name[100];
  sprintf(name, "%.2f", value);
  strcpy(p_self->name, name);
  p_self->creator_exists = FALSE;
  p_self->grad_exists = FALSE;
  p_self->isConst = TRUE;
  p_self->isParam = FALSE;
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
    p_self->p_grad = (Variable*)malloc(sizeof(Variable));
    Ndarray data;
    Ndarray_init(&data, p_self->p_data->dim, p_self->p_data->shape);
    for (int i = 0; i < p_self->p_data->size; i++)
      data.array[i] = 1.0;
    char dout_name[20];
    dout_name[0] = 'd';
    strcpy(dout_name + 1, p_self->name);
    Variable_init(p_self->p_grad, data, dout_name);
    p_self->grad_exists = TRUE;
    p_self->p_grad->isConst = TRUE;
  }
  PFunctionHeap fh;
  PFunctionHeap_init(&fh, FUNCTION_HEAP_SIZE);
  PFunctionHeap_insert(&fh, p_self->p_creator);
  Function* f;

  Function** seen_fs;
  seen_fs = (Function**)malloc(FUNCTION_HEAP_SIZE * sizeof(Function*));
  seen_fs[0] = p_self->p_creator;
  int cnt = 1;
  
  while (fh.last != -1) {
    f = PFunctionHeap_deletemax(&fh);
    Variable** gys;
    gys = (Variable**)malloc(f->output_num * sizeof(Variable*));
    for (int i = 0; i < f->output_num; i++) {
      gys[i] = f->p_io[1][i]->p_grad;
    }
    Variable** gxs;
    gxs = f->p_methods->backward(f, gys);
    for (int i = 0; i < f->input_num; i++) {
      if (f->p_io[0][i]->grad_exists) {
        f->p_io[0][i]->p_grad = add(f->p_io[0][i]->p_grad, gxs[i]);
      } else if (!(f->p_io[0][i]->isConst)) {
        f->p_io[0][i]->p_grad = gxs[i];
        f->p_io[0][i]->grad_exists = TRUE;
      }
      if (f->p_io[0][i]->creator_exists) {
        bool found = FALSE;
        for (int j = 0; j < cnt; j++) {
          if (seen_fs[j] == f->p_io[0][i]->p_creator) {
            found = TRUE;
            break;
          }
        }
        if (!found) {
          PFunctionHeap_insert(&fh, f->p_io[0][i]->p_creator);
          seen_fs[cnt++] = f->p_io[0][i]->p_creator;
        }
      }
    }
    if (!retain_grad) {
      for (int i = 0; i < f->output_num; i++) {
        // if (f->p_io[1][i]->p_grad != NULL && !(f->p_io[1][i]->isConst)) {
        //   free(f->p_io[1][i]->p_grad);
        // }
        f->p_io[1][i]->grad_exists = FALSE;
      }
    }
  }
  free(seen_fs);
}

void Variable_cleargrad(Variable* p_self) {
  p_self->grad_exists = FALSE;
}

Variable* Variable_reshape(Variable* p_self, ...) {
  va_list va_ptr;
  int dim = p_self->p_data->dim;
  va_start(va_ptr, p_self);
  int* shape;
  int size = 1;
  shape = (int*)malloc(dim * sizeof(int));
  for (int i = 0; i < dim; i++) {
    shape[i] = va_arg(va_ptr, int);
    size *= shape[i];
  }
  assert(p_self->p_data->size == size);
  return reshape(p_self, dim, shape);
}

Variable* Variable_transpose(Variable* p_self, ...) {
  va_list va_ptr;
  int dim = p_self->p_data->dim;
  va_start(va_ptr, p_self);
  int* axes;
  int* used;
  axes = (int*)malloc(dim * sizeof(int));
  used = (int*)malloc(dim * sizeof(int));
  for (int i = 0; i < dim; i++) {
    axes[i] = va_arg(va_ptr, int);
    assert(axes[i] < dim);
    for (int j = 0; j < i; j++)
      assert(axes[i] != used[j]);
    used[i] = axes[i];
  }
  return transpose(p_self, dim, axes);
}

void Variable_print(Variable* p_self) {
  printf("name: %s\n", p_self->name);
  printf("generation: %d\n", p_self->generation);
  printf("shape: [");
  for (int i = 0; i < p_self->p_data->dim - 1; i++) {
    printf("%d, ", p_self->p_data->shape[i]);
  }
  if (p_self->p_data->dim != 0) {
    printf("%d]\n", p_self->p_data->shape[p_self->p_data->dim-1]);
  } else {
    printf("None]\n");
  }
  printf("data:\n");
  Ndarray_print(p_self->p_data);
}

void Variable_destroy(Variable* p_self, const bool upstream) {
  Ndarray_destroy(p_self->p_data);
  p_self->p_data = NULL;
  if (p_self->grad_exists) {
    Ndarray_destroy(p_self->p_grad->p_data);
    p_self->p_grad->p_data = NULL;
    p_self->grad_exists = FALSE;
  }
  if (p_self->p_grad != NULL) {
    free(p_self->p_grad);
    p_self->p_grad == NULL;
  }
  if (!upstream || p_self->creator_exists == FALSE)
    return;
  PFunctionHeap fh;
  PFunctionHeap_init(&fh, FUNCTION_HEAP_SIZE);
  PFunctionHeap_insert(&fh, p_self->p_creator);
  Function* f;
  Variable** seen_is;
  seen_is = (Variable**)malloc(FUNCTION_HEAP_SIZE * sizeof(Variable*));
  int cnt = 0;
  while (fh.last != -1) {
    f = PFunctionHeap_deletemax(&fh);
    for (int i = 0; i < f->input_num; i++) {
      bool found = FALSE;
      for (int j = 0; j < cnt; j++) {
        if (seen_is[j] == f->p_io[0][i])
          found = TRUE;
      }
      if (!found) {
        seen_is[cnt++] = f->p_io[0][i];
        if (f->p_io[0][i]->creator_exists) {
          Ndarray_destroy(f->p_io[0][i]->p_data);
          f->p_io[0][i]->p_data = NULL;
          if (f->p_io[0][i]->grad_exists) {
            Ndarray_destroy(f->p_io[0][i]->p_grad->p_data);
            f->p_io[0][i]->p_grad->p_data = NULL;
          }
          if (f->p_io[0][i]->p_grad != NULL) {
            free(f->p_io[0][i]->p_grad);
            f->p_io[0][i]->p_grad = NULL;
          }
          PFunctionHeap_insert(&fh, f->p_io[0][i]->p_creator);
          f->p_io[0][i]->creator_exists = FALSE;
        }
      }
    }
    Function_destroy(f);
  }
  PFunctionHeap_destroy(&fh);
  free(seen_is);
}
