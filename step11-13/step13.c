#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "square.h"
#include "variable.h"
#include "function.h"
#include "add.h"

Variable** square(Variable* x){
  Square* sq;
  sq = (Square*)malloc(sizeof(Square));
  Square_init(sq);
  return Function_call((Function*)sq, x);
}

Variable** add(Variable* x, Variable *y){
  Add* ad;
  ad = (Add*)malloc(sizeof(Add));
  Add_init(ad);
  return Function_call((Function*)ad, x, y);
}

int main() {
  Variable x0;
  Variable x1;
  Variable_init(&x0, 2.0);
  Variable_init(&x1, 3.0);

  Variable** y;
  y = (Variable**)malloc(sizeof(Variable*));
  y = add(square(&x0)[0], square(&x1)[0]);

  Variable_backward(y[0]);

  printf("%.2f\n", y[0]->data);
  printf("%.2f\n", x0.grad);
  printf("%.2f\n", x1.grad);

  return 0;
}