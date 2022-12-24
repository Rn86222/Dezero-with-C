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

  Variable a = Function_call((Function*)&A, x);
  Variable b = Function_call((Function*)&B, a);
  Variable y = Function_call((Function*)&C, b);

  y.grad = 1.0;
  b.grad = Function_backward((Function*)&C, y.grad);
  a.grad = Function_backward((Function*)&B, b.grad);
  x.grad = Function_backward((Function*)&A, a.grad);

  printf("%.10f\n", x.grad);
  return 0;
}