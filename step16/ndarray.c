#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "ndarray.h"

void Ndarray_init(Ndarray* p_self, const int dim, const int* shape) {
  p_self->shape = (int*)malloc(dim * sizeof(int));
  assert(dim != 0);
  p_self->dim = dim;
  p_self->size = 1;
  for (int i = 0; i < dim; i++) {
    assert(shape[i] != 0);
    p_self->shape[i] = shape[i];
    p_self->size *= shape[i];
  }
  p_self->array = (float*)malloc(p_self->size * sizeof(float));
}

void Ndarray_init_as_zeros(Ndarray* p_self, const int dim, const int* shape) {
  p_self->shape = (int*)malloc(dim * sizeof(int));
  assert(dim != 0);
  p_self->dim = dim;
  p_self->size = 1;
  for (int i = 0; i < dim; i++) {
    assert(shape[i] != 0);
    p_self->shape[i] = shape[i];
    p_self->size *= shape[i];
  }
  p_self->array = (float*)malloc(p_self->size * sizeof(float));
  for (int i = 0; i < p_self->size; i++) {
    p_self->array[i] = 0.0;
  }
}

void Ndarray_copy(Ndarray* p_self, const Ndarray original) {
  Ndarray_init(p_self, original.dim, original.shape);
  for (int i = 0; i < p_self->size; i++)
    p_self->array[i] = original.array[i];
}

Ndarray Ndarray_add(const Ndarray a, const Ndarray b) {
  Ndarray c;
  assert(a.dim == b.dim && a.size == b.size);
  for (int i = 0; i < a.dim; i++)
    assert(a.shape[i] == b.shape[i]);

  Ndarray_init(&c, a.dim, a.shape);
  for (int i = 0; i < c.size; i++)
    c.array[i] = a.array[i] + b.array[i];
  return c;
} 

Ndarray Ndarray_mul(const Ndarray a, const Ndarray b) {
  Ndarray c;
  assert(a.dim == b.dim && a.size == b.size);
  for (int i = 0; i < a.dim; i++)
    assert(a.shape[i] == b.shape[i]);

  Ndarray_init(&c, a.dim, a.shape);
  for (int i = 0; i < c.size; i++)
    c.array[i] = a.array[i] * b.array[i];
  return c;
}

Ndarray Ndarray_constant_mul(const Ndarray a, float c) {
  Ndarray b;
  Ndarray_init(&b, a.dim, a.shape);
  for (int i = 0; i < b.size; i++)
    b.array[i] = c * a.array[i];
  return b;
}

Ndarray Ndarray_map(const Ndarray a, double (*func)(double)) {
  Ndarray b;
  Ndarray_init(&b, a.dim, a.shape);
  for (int i = 0; i < b.size; i++)
    b.array[i] = func(a.array[i]);
  return b; 
}

void Ndarray_destroy(Ndarray* p_self) {
  free(p_self->array);
  free(p_self->shape);
  p_self->size = 0;
  p_self->dim = 0;
  free(p_self);
}
