#include "linearl.h"
#include "../variable/variable.h"
#include "../ndarray/ndarray.h"
#include "../function/functions.h"
#include "../utils/manage_memory/manage_memory.h"
#include <assert.h>
#include <stdlib.h>
#include <math.h>

static Variable** linearl_forward(Layer* const p_self, Variable** xs) {
  if (p_self->param_num < p_self->max_param_num) {
    ((LinearL*)p_self)->in_size = xs[0]->p_data->shape[1];
    Ndarray W_data;
    Ndarray_init_shape_randn_as_static(&W_data, 2, ((LinearL*)p_self)->in_size, ((LinearL*)p_self)->out_size);
    W_data = Ndarray_constant_mul_as_static(W_data, sqrt((float)1.0 / ((LinearL*)p_self)->in_size));
    Variable_init_as_param(((LinearL*)p_self)->W, W_data, "W");
    p_self->p_params[(p_self->param_num)++] = ((LinearL*)p_self)->W;
  }

  Variable** ys;
  ys = (Variable**)mymalloc(p_self->output_num * sizeof(Variable*));
  ys[0] = linear(xs[0], ((LinearL*)p_self)->W, ((LinearL*)p_self)->b);
  return ys;
}

static const LayerMethods LINEARL_METHODS = {
  linearl_forward
};

void LinearL_init(LinearL* p_self, const int out_size, const int max_layer_num) {
  Layer_init((Layer*)p_self, 1, 1, 2, max_layer_num);
  p_self->out_size = out_size;
  ((Layer*)p_self)->p_methods = &LINEARL_METHODS;
  p_self->W = (Variable*)malloc(sizeof(Variable));
  p_self->b = (Variable*)malloc(sizeof(Variable));
  Ndarray b_data;
  Ndarray_init_shape_zero_as_static(&b_data, 1, out_size);
  Variable_init_as_param(p_self->b, b_data, "b");
  ((Layer*)p_self)->p_params[(((Layer*)p_self)->param_num)++] = p_self->b;
}