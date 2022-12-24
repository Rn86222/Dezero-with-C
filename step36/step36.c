#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "variable/variable.h"
#include "function/function.h"
#include "function/functions.h"
#include "ndarray/ndarray.h"
#include "macro/constant.h"
#include "dot/dot.h"


int main() {
  Variable x;
  Ndarray x_data;
  int x_data_shape[1] = {1};
  Ndarray_init(&x_data, 1, x_data_shape);
  x_data.array[0] = 2.0;
  Variable_init(&x, x_data, "x");

  Variable** y;
  y = (Variable**)malloc(1 * sizeof(Variable*));
  y[0] = squareN("y", &x);
  Variable_print(y[0]);
  y[0]->isConst = FALSE;

  Variable_backward(y[0], FALSE);
  Variable_print(x.p_grad);

  Variable** z;
  z = (Variable**)malloc(1 * sizeof(Variable*));
  z[0] = addN("z", poweRC(x.p_grad, 3.0), y[0]);
  plot_dot_graph(z[0], FALSE, FALSE, "graphz.png");
  

  Variable_cleargrad(&x);
  Variable_backward(z[0], FALSE);
  plot_dot_graph(x.p_grad, FALSE, FALSE, "graph.png");

  Variable_print(x.p_grad);

  return 0;
}