#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "square.h"
#include "variable.h"
#include "function.h"
#include "add.h"

Variable** add(Variable* x, Variable *y){
  Add* ad;
  ad = (Add*)malloc(sizeof(Add));
  Add_init(ad);
  return Function_call((Function*)ad, x, y);
}

int main() {
  Variable x;
  Variable_init(&x, 3.0);

  Variable** y;
  y = (Variable**)malloc(sizeof(Variable*));
  y = add(&x, &x);

  Variable_backward(y[0]);

  printf("x.grad %.2f\n", x.grad);

  Variable_cleargrad(&x);

  Variable** z;
  z = (Variable**)malloc(sizeof(Variable*));
  z = add(&x, add(&x, &x)[0]);

  Variable_backward(z[0]);

  printf("x.grad %.2f\n", x.grad);

  return 0;
}