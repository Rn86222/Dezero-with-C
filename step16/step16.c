#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "square.h"
#include "variable.h"
#include "function.h"
#include "add.h"
#include "ndarray.h"

Variable** add(Variable* x, Variable *y){
  Add* ad;
  ad = (Add*)malloc(sizeof(Add));
  Add_init(ad);
  return Function_call((Function*)ad, x, y);
}

Variable** square(Variable* x){
  Square* sq;
  sq = (Square*)malloc(sizeof(Square));
  Square_init(sq);
  return Function_call((Function*)sq, x);
}

int main() {
  Variable x;
  Ndarray x_data;
  int x_data_shape[1] = {3};
  Ndarray_init(&x_data, 1, x_data_shape);
  x_data.array[0] = 2.0;
  x_data.array[1] = 3.0;
  x_data.array[2] = 4.0;
  Variable_init(&x, x_data);

  Variable** a;
  a = (Variable**)malloc(sizeof(Variable*));
  a = square(&x);

  Variable** y;
  y = (Variable**)malloc(sizeof(Variable*));
  y = add(square(a[0])[0], square(a[0])[0]);

  Variable_backward(y[0]);

  printf("y.data[0] %.2f\n", y[0]->p_data->array[0]);
  printf("x.grad[0] %.2f\n", x.p_grad->array[0]);
  printf("y.data[1] %.2f\n", y[0]->p_data->array[1]);
  printf("x.grad[1] %.2f\n", x.p_grad->array[1]);
  printf("y.data[2] %.2f\n", y[0]->p_data->array[2]);
  printf("x.grad[2] %.2f\n", x.p_grad->array[2]);

  Variable_destroy(y[0], TRUE);

  return 0;
}