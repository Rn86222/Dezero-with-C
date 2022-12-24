#include "twolayernet.h"
#include "linearl.h"
#include "../function/functions.h"
#include <stdlib.h>

static Variable** twolayernet_forward(Layer* const p_self, Variable** xs) {
  Variable** ys;
  ys = (Variable**)malloc(p_self->output_num * sizeof(Variable*));
  ys[0] = Layer_call(p_self->p_layers[0], xs[0])[0];
  ys[0] = sigmoid(ys[0]);
  ys[0] = Layer_call(p_self->p_layers[1], ys[0])[0];
  return ys;
}

static const LayerMethods TWOLAYERNET_METHODS = {
  twolayernet_forward
};

void TwoLayerNet_init(TwoLayerNet* p_self, const int hidden_size, const int out_size) {
  Layer_init((Layer*)p_self, 1, 1, 2, 2);
  ((Layer*)p_self)->p_methods = &TWOLAYERNET_METHODS;
  LinearL* l1 = (LinearL*)malloc(sizeof(LinearL));
  LinearL* l2 = (LinearL*)malloc(sizeof(LinearL));;
  LinearL_init(l1, hidden_size, 0);
  LinearL_init(l2, out_size, 0);
  ((Layer*)p_self)->p_layers[0] = (Layer*)l1;
  ((Layer*)p_self)->p_layers[1] = (Layer*)l2;
   ((Layer*)p_self)->layer_num = 2;
}