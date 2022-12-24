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
  Variable x;
  Ndarray x_data;
  Ndarray_init_shape(&x_data, 3, 4, 3, 2);
  for (int i = 0; i < 24; i++) {
    x_data.array[i] = (float)i + 1;
  }
  Variable_init(&x, x_data, "x");
  Variable_print(&x);

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
  putchar('\n');
  Variable* z = sum(&x, 1, FALSE);
  Variable_print(z);
  putchar('\n');
  Variable* w = sum(z, 0, FALSE);
  Variable_print(w);
  putchar('\n');
  Variable* v = sum(w, 0, TRUE);
  Variable_print(v);

  // Ndarray w;
  // int shape[1] = {12};
  // w = Ndarray_reshape(z, 1, shape);
  // Ndarray_print(&w);
  // w = Ndarray_sum(w, 0, FALSE);
  // Ndarray_print(&w);
  return 0;
}