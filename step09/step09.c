#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "variable.h"
#include "square.h"
#include "function.h"
#include "exp.h"

Variable* square(Variable* x){
  Square* sq;
  sq = (Square*)malloc(sizeof(Square));
  Square_init(sq);
  return Function_call((Function*)sq, x);
}

Variable* expo(Variable* x){
  Exp* ex;
  ex = (Exp*)malloc(sizeof(Exp));
  Exp_init(ex);
  return Function_call((Function*)ex, x);
}

int main() {
  Variable x;
  Variable_init(&x, 0.5);

  Variable* y = square(expo(square(&x)));

  Variable_backward(y);

  printf("%.10f\n", x.grad);

  return 0;
}