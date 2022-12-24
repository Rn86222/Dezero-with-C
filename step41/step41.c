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
#include "function/reshape.h"

int main() {
  // Ndarray a, b, c;
  // int shape[1] = {3};
  // Ndarray_init(&a, 1, shape);
  // for (int i = 0; i < 3; i++)
  //   a.array[i] = (float)i + 1;
  // Ndarray_init(&b, 1, shape);
  // for (int i = 0; i < 3; i++)
  //   b.array[i] = (float)i + 4;
  // c = Ndarray_dot(a, b);
  // Ndarray_print(&c);

  // Ndarray a, b, c;
  // int shape1[2] = {2, 3};
  // int shape2[2] = {3, 4};
  // Ndarray_init(&a, 2, shape1);
  // for (int i = 0; i < 6; i++)
  //   a.array[i] = (float)i + 1;
  // Ndarray_init(&b, 2, shape2);
  // for (int i = 0; i < 12; i++)
  //   b.array[i] = (float)i + 4;
  // c = Ndarray_dot(a, b);
  // Ndarray_print(&c);

  Variable x;
  Ndarray x_data;
  Ndarray_init_shape(&x_data, 2, 2, 3);
  for (int i = 0; i < 6; i++)
    x_data.array[i] = (float)i + 1;
  Variable_init(&x, x_data, "x");

  Variable W;
  Ndarray W_data;
  Ndarray_init_shape(&W_data, 2, 3, 4);
  for (int i = 0; i < 12; i++)
    W_data.array[i] = (float)i + 1;
  Variable_init(&W, W_data, "W");

  Variable_print(&x);
  Variable_print(&W);

  Variable* y = matmulN("y", &x, &W);
  Variable_print(y);
  Variable_backward(y, FALSE);
  Variable_print(x.p_grad);
  Variable_print(W.p_grad);


  return 0;
}