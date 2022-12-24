#include <stdio.h>
#include <stdlib.h>

typedef struct a {
  int *c;
  int *d;
  int b;
} A;

void A_init(A* p_self, int b) {
  p_self = (A*)malloc(sizeof(A));
  p_self->b = b;
}

int main() {
  A a;
  printf("%d\n", a.b);
  A_init(&a, 3);
  printf("%d\n", a.b);
  return 0;
}