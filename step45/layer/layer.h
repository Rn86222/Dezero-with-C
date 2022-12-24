#include "../variable/variable.h"

#ifndef _LAYER_H_
#define _LAYER_H_

typedef struct layer Layer;

typedef struct layer {
  const struct layermethods *p_methods;
  Variable ***p_io;
  int param_num;
  int max_param_num;
  int input_num;
  int output_num;
  Variable** p_params;
  int layer_num;
  int max_layer_num;
  Layer** p_layers;
} Layer;

typedef struct layermethods {
  Variable** (*forward)(Layer* const, Variable**);
} LayerMethods;

void Layer_init(Layer* p_self, const int input_num, const int output_num, const int max_param_num, const int max_layer_num);
Variable** Layer_call(Layer* p_self, ...);
void Layer_cleargrads(Layer* p_self);
void Layer_add_layer(Layer* p_self, Layer* layer);
void Layer_update_params(Layer* p_self, const float lr);

#endif // _LAYER_H_