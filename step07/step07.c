#include <stdio.h>
#include <math.h>
#include "variable.h"
#include "square.h"
#include "function.h"
#include "exp.h"

int main() {
  Variable x;
  Variable_init(&x, 0.5);

  Square A;
  Square_init(&A);
  Exp B;
  Exp_init(&B);
  Square C;
  Square_init(&C);

  Variable a = Function_call((Function*)&A, &x);
  Variable b = Function_call((Function*)&B, &a);
  Variable y = Function_call((Function*)&C, &b);

  y.grad = 1.0;

  Variable_backward(&y);

  printf("%.10f\n", x.grad);

  Function_destroy((Function*)&A);
  Function_destroy((Function*)&B);
  Function_destroy((Function*)&C);

  return 0;
}