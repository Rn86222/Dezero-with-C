#include "mlp.h"
#include "linearl.h"
#include "../function/functions.h"
#include "../utils/manage_memory/manage_memory.h"
#include <stdlib.h>
#include <stdio.h>

static Variable** mlp_forward(Layer* const p_self, Variable** xs) {
  Variable** ys;
  ys = (Variable**)mymalloc(p_self->output_num * sizeof(Variable*));
  ys[0] = Layer_call(p_self->p_layers[0], xs[0])[0];
  ys[0] = sigmoid(ys[0]);
  for (int i = 1; i < p_self->layer_num - 1; i++) {
    ys[0] = Layer_call(p_self->p_layers[i], ys[0])[0];
    ys[0] = sigmoid(ys[0]);
  }
  if (p_self->layer_num > 1)
    ys[0] = Layer_call(p_self->p_layers[p_self->layer_num - 1], ys[0])[0];
  return ys;
}

static const LayerMethods MLP_METHODS = {
  mlp_forward
};

void MLP_init(MLP* p_self, const int layer_num, const int* fc_output_sizes) {
  Layer_init((Layer*)p_self, 1, 1, 0, layer_num);
  ((Layer*)p_self)->p_methods = &MLP_METHODS;
  LinearL** layers = (LinearL**)malloc(layer_num * sizeof(LinearL*));
  for (int i = 0; i < layer_num; i++) {
    layers[i] = (LinearL*)malloc(sizeof(LinearL));
    LinearL_init(layers[i], fc_output_sizes[i], 0);
    Layer_add_layer((Layer*)p_self, (Layer*)layers[i]);
  }
}