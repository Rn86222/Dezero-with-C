#include <stdio.h>
#include "variable.h"

int main() {
  Variable x;
  Variable_init(&x, 1.0);
  printf("%.2f\n", x.data);
  return 0;
}