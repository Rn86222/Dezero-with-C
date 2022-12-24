#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <math.h>
#include "constant.h"
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

Ndarray Ndarray_sub(const Ndarray a, const Ndarray b) {
  Ndarray c;
  assert(a.dim == b.dim && a.size == b.size);
  for (int i = 0; i < a.dim; i++)
    assert(a.shape[i] == b.shape[i]);

  Ndarray_init(&c, a.dim, a.shape);
  for (int i = 0; i < c.size; i++)
    c.array[i] = a.array[i] - b.array[i];
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

Ndarray Ndarray_div(const Ndarray a, const Ndarray b) {
  Ndarray c;
  assert(a.dim == b.dim && a.size == b.size);
  for (int i = 0; i < a.dim; i++)
    assert(a.shape[i] == b.shape[i]);

  Ndarray_init(&c, a.dim, a.shape);
  for (int i = 0; i < c.size; i++) {
    assert(b.array[i] != 0);
    c.array[i] = a.array[i] / b.array[i];
  }
  return c;
}

Ndarray Ndarray_pow(const Ndarray a, const Ndarray b) {
  Ndarray c;
  assert(a.dim == b.dim && a.size == b.size);
  for (int i = 0; i < a.dim; i++)
    assert(a.shape[i] == b.shape[i]);

  Ndarray_init(&c, a.dim, a.shape);
  for (int i = 0; i < c.size; i++) {
    assert(a.array[i] >= 0);
    assert(a.array[i] != 0 || b.array[i] > 0);
    c.array[i] = pow(a.array[i], b.array[i]);
  }
  return c;
}

Ndarray Ndarray_constant_add(const Ndarray a, float c) {
  Ndarray b;
  Ndarray_init(&b, a.dim, a.shape);
  for (int i = 0; i < b.size; i++)
    b.array[i] = a.array[i] + c;
  return b;
}

Ndarray Ndarray_constant_mul(const Ndarray a, float c) {
  Ndarray b;
  Ndarray_init(&b, a.dim, a.shape);
  for (int i = 0; i < b.size; i++)
    b.array[i] = c * a.array[i];
  return b;
}

Ndarray Ndarray_neg(const Ndarray a) {
  Ndarray b;
  Ndarray_init(&b, a.dim, a.shape);
  for (int i = 0; i < b.size; i++)
    b.array[i] = -a.array[i];
  return b;
}

Ndarray Ndarray_map(const Ndarray a, double (*func)(double)) {
  Ndarray b;
  Ndarray_init(&b, a.dim, a.shape);
  for (int i = 0; i < b.size; i++)
    b.array[i] = func(a.array[i]);
  return b; 
}

static void ndarray_print(float* array, const int dim, const int size, const int* shape, const bool isFinal) {
  assert(dim >= 1);
  if (dim == 1) {
    printf("[");
    for (int i = 0; i < shape[0] - 1; i++) {
      printf("%.2f, ", array[i]);
    }
    printf("%.2f]", array[shape[0] - 1]);
    if (isFinal == FALSE) {
      printf(",\n");
    }
    return;
  }
  int down_dim = dim - 1;
  int down_size = size / shape[0];
  int* down_shape;
  float* down_array;
  down_shape = (int*)malloc(down_dim * sizeof(int));
  down_array = (float*)malloc(down_size * sizeof(float));
  for (int i = 0; i < dim - 1; i++) {
    down_shape[i] = shape[i+1];
  }
  printf("[");
  for (int i = 0; i < shape[0] - 1; i++) {
    for (int j = 0; j < down_size; j++) {
      down_array[j] = array[j + i*down_size];
    }
    ndarray_print(down_array, down_dim, down_size, down_shape, FALSE);
  }
  for (int j = 0; j < down_size; j++) {
    down_array[j] = array[j + (shape[0]-1)*down_size];
  }
  ndarray_print(down_array, down_dim, down_size, down_shape, TRUE);
  printf("]");
  if (isFinal == FALSE) {
    printf(",\n");
  }
}

void Ndarray_print(const Ndarray* p_self) {
  ndarray_print(p_self->array, p_self->dim, p_self->size, p_self->shape, TRUE);
  putchar('\n');
}