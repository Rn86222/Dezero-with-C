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
  // Variable x;
  // Ndarray x_data;
  // Ndarray_init_shape(&x_data, 2, 2, 3);
  // for (int i = 0; i < 6; i++) {
  //   x_data.array[i] = (float)i + 1;
  // }
  // Variable_init(&x, x_data, "x");
  // Variable_print(&x);

  // Variable* y = sum(&x, 0, FALSE);
  // Variable_print(y);
  // Variable_backward(y, FALSE);
  // Variable_print(x.p_grad);

  Variable x;
  Ndarray x_data;
  Ndarray_init_shape(&x_data, 4, 2, 3, 4, 5);
  for (int i = 0; i < 120; i++) {
    x_data.array[i] = (float)i + 1;
  }
  Variable_init(&x, x_data, "x");
  Variable_print(&x);

  int shape[4] = {1,1,1,1};

  Variable* y = sum_to(&x, 4, shape);
  Variable_print(y);

  // Variable** y;
  // y = (Variable**)malloc(1 * sizeof(Variable*));
  // y[0] = Variable_reshape(&x, 2, 6, 4);
  // Variable_print(y[0]);
  
  // Variable_backward(y[0], FALSE);

  // Variable_print(x.p_grad);

  // Variable** z;
  // z = (Variable**)malloc(1 * sizeof(Variable*));
  // z[0] = transpose2d(y[0]);
  // Variable_print(z[0]);


  // Variable** y;
  // y = (Variable**)malloc(1 * sizeof(Variable*));
  // y[0] = Variable_transpose(&x, 2, 1, 0);
  // Variable_print(y[0]);
  // Variable_backward(y[0], FALSE);
  // Variable_print(x.p_grad);
  // putchar('\n');
  // Variable* z = sum(&x, 1, FALSE);
  // Variable_print(z);
  // putchar('\n');
  // Variable* w = sum(z, 0, FALSE);
  // Variable_print(w);
  // putchar('\n');
  // Variable* v = sum(w, 0, TRUE);
  // Variable_print(v);

  // Variable x0;
  // Ndarray x0_data;
  // Ndarray_init_shape(&x0_data, 1, 3);
  // x0_data.array[0] = 1;
  // x0_data.array[1] = 2;
  // x0_data.array[2] = 3;
  // Variable_init(&x0, x0_data, "x0");

  // Variable x1;
  // Ndarray x1_data;
  // Ndarray_init_shape(&x1_data, 1, 1);
  // x1_data.array[0] = 10;
  // Variable_init(&x1, x1_data, "x1");

  // Variable_print(&x0);
  // Variable_print(&x1);

  // Variable* y = add(&x0, &x1);
  // Variable_print(y);
  // Variable_backward(y, FALSE);
  
  // Variable_print(x0.p_grad);
  // Variable_print(x1.p_grad);

  return 0;
}