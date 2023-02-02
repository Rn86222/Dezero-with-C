#include "layer.h"

typedef struct twolayernet {
  Layer layer;
} TwoLayerNet;

void TwoLayerNet_init(TwoLayerNet* p_self, const int hidden_size, const int out_size);