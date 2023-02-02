#include "layer.h"

typedef struct mlp {
  Layer layer;
} MLP;

void MLP_init(MLP* p_self, const int layer_num, const int* fc_output_sizes);