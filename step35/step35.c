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

#define GNUPLOT "gnuplot -persist"
#define MAX_LOOP 7

int main() {
  Variable x;
  Ndarray x_data;
  int x_data_shape[1] = {1};
  Ndarray_init(&x_data, 1, x_data_shape);
  x_data.array[0] = 1.0;
  Variable_init(&x, x_data, "x");

  Variable** y;
  y = (Variable**)malloc(1 * sizeof(Variable*));
  y[0] = tanhyN("y", &x);
  Variable_print(y[0]);

  Variable_backward(y[0], FALSE);

  for (int i = 0; i < MAX_LOOP; i++) {
    Variable_cleargrad(&x);
    Variable_backward(x.p_grad, FALSE);
  }
  plot_dot_graph(x.p_grad, FALSE, TRUE, "graph8-2.png");

  // Variable_backward(z[0], FALSE);
  // z[0] = squareN("z", &x);
  // z[0] = mulN("z", addLC(1.0, mul(square(add(addLC(1.0, &x), &y)), add(add(subLC(19.0, mulLC(14.0, &x)), sub(mulLC(3.0, square(&x)), mulLC(14.0, &y))), add(mulLC(6.0, mul(&x, &y)), mulLC(3.0, square(&y)))))),
  //                  addLC(30.0, mul(square(sub(mulLC(2.0, &x), mulLC(3.0, &y))), add(add(subLC(18.0, mulLC(32.0, &x)), add(mulLC(12.0, square(&x)), mulLC(48.0, &y))), sub(mulLC(27.0, square(&y)), mulLC(36.0, mul(&x, &y)))))));


  // Variable_backward(z[0], FALSE);
  
  // plot_dot_graph(z[0], FALSE, FALSE, "graph.png");
  // Variable_print(x.p_grad);

  // Variable_cleargrad(&x);

  // plot_dot_graph(x.p_grad, FALSE, FALSE, "graph2.png");
  // Variable_backward(x.p_grad, FALSE);
  // Variable_print(x.p_grad);
  // Variable_print(z[0]);

  return 0;
}