#include <stdio.h>
#include "variable.h"
#include "square.h"
#include "function.h"

int main() {
  Variable x;
  Variable_init(&x, 10);
  Square f;
  Square_init(&f);
  Variable y = Function_call((Function*)&f, x);
  printf("%.2f\n", y.data);
  return 0;
}