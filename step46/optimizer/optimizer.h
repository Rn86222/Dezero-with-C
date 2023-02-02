#include "../layer/layers.h"

#ifndef _OPTIMIZER_H_
#define _OPTIMIZER_H_

typedef struct optimizer {
  Layer* target;
} Optimizer;

void Optimizer_init(Optimizer* p_self);
Optimizer* Optimizer_setup(Optimizer* p_self, Layer* target);
void Optimizer_update(Optimizer* p_self);


#endif // _OPTIMIZER_H_