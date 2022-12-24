#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "square.h"
#include "variable.h"
#include "function.h"
#include "add.h"
#include "ndarray.h"

int main() {
  Variable x;
  Ndarray x_data;
  int x_data_shape[3] = {3, 4, 2};
  Ndarray_init(&x_data, 3, x_data_shape);
  for (int i = 0; i < 3*4*2; i++) {
    x_data.array[i] = 0.25*i;
  }

  Variable_init(&x, x_data, "x");
  Square A;
  Square_init(&A);
  Square B;
  Square_init(&B);
  Square C;
  Square_init(&C);
  Add D;
  Add_init(&D);

  Variable** a;
  a = (Variable**)malloc(A.function.output_num * sizeof(Variable*));
  a = Function_call((Function*)&A, "a", &x);

  Variable** b;
  b = (Variable**)malloc(B.function.output_num * sizeof(Variable*));
  b = Function_call((Function*)&B, "b", a[0]);
  
  Variable** c;
  c = (Variable**)malloc(C.function.output_num * sizeof(Variable*));
  c = Function_call((Function*)&C, "c", a[0]);

  Variable** y;
  y = (Variable**)malloc(D.function.output_num * sizeof(Variable*));
  y = Function_call((Function*)&D, "y", b[0], c[0]);

  Variable_backward(y[0], FALSE);

  Variable_print(&x);
  Variable_print(a[0]);
  Variable_print(b[0]);
  Variable_print(c[0]);
  Variable_print(y[0]);

  Function_destroy((Function*)&A);
  Function_destroy((Function*)&B);
  Function_destroy((Function*)&C);
  Function_destroy((Function*)&D);

  return 0;
}