#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "square.h"
#include "variable.h"
#include "function.h"
#include "add.h"
#include "mul.h"
#include "neg.h"
#include "ndarray.h"

int main() {
  Variable x;
  Ndarray x_data;
  int x_data_shape[1] = {2};
  Ndarray_init(&x_data, 1, x_data_shape);
  for (int i = 0; i < 2; i++) {
    x_data.array[i] = 0.25*i+1.0;
  }

  Variable a;
  Ndarray a_data;
  int a_data_shape[1] = {2};
  Ndarray_init(&a_data, 1, a_data_shape);
  for (int i = 0; i < 2; i++) {
    a_data.array[i] = 2.0;
  }

  Variable b;
  Ndarray b_data;
  int b_data_shape[1] = {2};
  Ndarray_init(&b_data, 1, b_data_shape);
  for (int i = 0; i < 2; i++) {
    b_data.array[i] = 3.0;
  }

  Variable_init(&x, x_data, "x");
  Variable_init(&a, a_data, "a");
  Variable_init(&b, b_data, "b");

  Neg neg;
  Neg_init(&neg);
  Mul mul;
  Mul_init(&mul);
  Add add;
  Add_init(&add);

  Variable** g;
  g = (Variable**)malloc(mul.function.output_num * sizeof(Variable*));
  g = Function_call((Function*)&neg, "g", &x);

  Variable** h;
  h = (Variable**)malloc(mul.function.output_num * sizeof(Variable*));
  h = Function_call((Function*)&mul, "h", &a, g[0]);

  Variable** y;
  y = (Variable**)malloc(add.function.output_num * sizeof(Variable*));
  y = Function_call((Function*)&add, "y", h[0], &b);

  Variable_backward(y[0], FALSE);

  Ndarray_print(x.p_grad);
  Ndarray_print(a.p_grad);
  Ndarray_print(b.p_grad);

  Variable_print(&x);
  Variable_print(h[0]);
  Variable_print(y[0]);

  Function_destroy((Function*)&add);
  Function_destroy((Function*)&mul);

  return 0;
}