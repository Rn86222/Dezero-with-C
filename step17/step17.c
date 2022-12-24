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
  int x_data_shape[1] = {3};
  Ndarray_init(&x_data, 1, x_data_shape);
  x_data.array[0] = 2.0;
  x_data.array[1] = 3.0;
  x_data.array[2] = 4.0;
  Variable_init(&x, x_data);
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
  a = Function_call((Function*)&A, &x);

  Variable** b;
  b = (Variable**)malloc(B.function.output_num * sizeof(Variable*));
  b = Function_call((Function*)&B, a[0]);
  
  Variable** c;
  c = (Variable**)malloc(C.function.output_num * sizeof(Variable*));
  c = Function_call((Function*)&C, a[0]);

  Variable** y;
  y = (Variable**)malloc(D.function.output_num * sizeof(Variable*));
  y = Function_call((Function*)&D, b[0], c[0]);

  Variable_backward(y[0]);

  printf("y.data %.2f\n", y[0]->p_data->array[0]);
  printf("x.grad %.2f\n", x.p_grad->array[0]);
  printf("y.data %.2f\n", y[0]->p_data->array[1]);
  printf("x.grad %.2f\n", x.p_grad->array[1]);
  printf("y.data %.2f\n", y[0]->p_data->array[2]);
  printf("x.grad %.2f\n", x.p_grad->array[2]);

  Function_destroy((Function*)&A);
  Function_destroy((Function*)&B);
  Function_destroy((Function*)&C);
  Function_destroy((Function*)&D);

  return 0;
}