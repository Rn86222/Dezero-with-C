#include "variable.h"
#include "function.h"
#include "functionstack.h"
#include "constant.h"
#include <stdio.h>
#include <stdlib.h>

void Variable_init(Variable* p_self, const float data) {
  p_self->data = data;
  p_self->grad = 0.0;
  p_self->creator_exists = FALSE;
  p_self->grad_exists = FALSE;
}

void Variable_set_creator(Variable* p_self, Function* func) {
  p_self->p_creator = func;
  p_self->creator_exists = TRUE;
}

void Variable_backward(Variable* p_self) {
  if (p_self->creator_exists == FALSE) {
    return;
  }
  if (p_self->grad_exists == FALSE) {
    p_self->grad = 1.0;
    p_self->grad_exists = TRUE;
  }
  FunctionStack fs;
  FunctionStack_init(&fs, FUNCTION_STACK_SIZE);
  FunctionStack_push(&fs, *(p_self->p_creator));
  Function f;
  while (fs.last != -1) {
    f = FunctionStack_pop(&fs);
    float* gys;
    gys = (float*)malloc(f.output_num * sizeof(float));
    for (int i = 0; i < f.output_num; i++) {
      gys[i] = f.p_io[1][i]->grad;
    }
    float* gxs;
    gxs = (float*)malloc(f.input_num * sizeof(float));
    gxs = f.p_methods->backward(&f, gys);

    for (int i = 0; i < f.input_num; i++) {
      if (f.p_io[0][i]->grad_exists) {
        f.p_io[0][i]->grad += gxs[i];
      } else {
        f.p_io[0][i]->grad = gxs[i];
        f.p_io[0][i]->grad_exists = TRUE;
      }
      if (f.p_io[0][i]->creator_exists) {
        FunctionStack_push(&fs, *(f.p_io[0][i]->p_creator));
      }
    }
  }
}

void Variable_cleargrad(Variable* p_self) {
  p_self->grad = 0.0;
  p_self->grad_exists = FALSE;
}