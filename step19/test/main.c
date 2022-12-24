#include <stdio.h>
#include <stdlib.h>

int main() {
  int* a;
  int* b;
  printf("*a %d a %p *b %d b %p\n",*a, a, *b, b);
  a = (int*)malloc(sizeof(int));
  *a = 1;
  b = (int*)malloc(sizeof(int));
  *b = 2;
  printf("*a %d a %p *b %d b %p\n",*a, a, *b, b);
  free(a);
  printf("*a %d a %p *b %d b %p\n",*a, a, *b, b);
  free(b);
  printf("*a %d a %p *b %d b %p\n",*a, a, *b, b);
  return 0;
}