#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "variable/variable.h"
#include "function/function.h"
#include "function/functions.h"
#include "ndarray/ndarray.h"
#include "macro/constant.h"
#include "dot/dot.h"

#define MAX_LOOP 10

int main() {
  Variable x;
  Ndarray x_data;
  int x_data_shape[1] = {1};
  Ndarray_init(&x_data, 1, x_data_shape);
  x_data.array[0] = 1.0;
  Variable_init(&x, x_data, "x");

  Variable y;
  Ndarray y_data;
  int y_data_shape[1] = {1};
  Ndarray_init(&y_data, 1, y_data_shape);
  y_data.array[0] = 1.0;
  Variable_init(&y, y_data, "y");

  Variable** z;
  z = (Variable**)malloc(1 * sizeof(Variable*));
  z[0] = mulN("z", addLC(1.0, mul(square(add(addLC(1.0, &x), &y)), add(add(subLC(19.0, mulLC(14.0, &x)), sub(mulLC(3.0, square(&x)), mulLC(14.0, &y))), add(mulLC(6.0, mul(&x, &y)), mulLC(3.0, square(&y)))))),
                   addLC(30.0, mul(square(sub(mulLC(2.0, &x), mulLC(3.0, &y))), add(add(subLC(18.0, mulLC(32.0, &x)), add(mulLC(12.0, square(&x)), mulLC(48.0, &y))), sub(mulLC(27.0, square(&y)), mulLC(36.0, mul(&x, &y)))))));

  // for (int i = 0; i < MAX_LOOP; i++) {
  //   Ndarray_print(x.p_data);
  //   // Ndarray_print(y.p_data);
  //   z[0] = subN("z", poweRC(&x, 4), mulLC(2, square(&x)));
  //   Variable_cleargrad(&x);
  //   Variable_backward(z[0], FALSE);
  //   *(x.p_data) = Ndarray_sub(*(x.p_data), Ndarray_div(*(x.p_grad), Ndarray_constant_add(Ndarray_constant_mul(Ndarray_square(*(x.p_data)), 12.0), -4.0)));
  // }

  Variable_backward(z[0], FALSE);
  
  plot_dot_graph(z[0], FALSE, FALSE, "graph.png");

  Ndarray_print(x.p_grad);
  Ndarray_print(y.p_grad);

  Variable_print(&x);
  // Variable_print(&y);
  Variable_print(z[0]);

  // printf("\nmain end\n");
  return 0;
}