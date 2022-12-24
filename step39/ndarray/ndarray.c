#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <math.h>
#include <stdarg.h>
#include "../macro/constant.h"
#include "ndarray.h"

void Ndarray_init(Ndarray* p_self, const int dim, const int* shape) {
  if (dim == 0) {
    Ndarray_init_as_scalar(p_self);
    return;
  }
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

void Ndarray_init_shape(Ndarray* p_self, const int dim, ...) {
  if (dim == 0) {
    Ndarray_init_as_scalar(p_self);
    return;
  }
  p_self->shape = (int*)malloc(dim * sizeof(int));
  assert(dim != 0);
  va_list va_ptr;
  va_start(va_ptr, dim);
  p_self->dim = dim;
  p_self->size = 1;
  p_self->shape = (int*)malloc(dim * sizeof(int));
  for (int i = 0; i < dim; i++) {
    int len = va_arg(va_ptr, int);
    assert(len != 0);
    p_self->shape[i] = len;
    p_self->size *= len;
  }
  va_end(va_ptr);
  p_self->array = (float*)malloc(p_self->size * sizeof(float));
}

void Ndarray_init_as_zeros(Ndarray* p_self, const int dim, const int* shape) {
  if (dim == 0) {
    Ndarray_init_as_scalar(p_self);
    return;
  }
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

void Ndarray_init_as_scalar(Ndarray* p_self) {
  p_self->shape = (int*)malloc(sizeof(int));
  p_self->dim = 0;
  p_self->size = 1;
  p_self->shape[0] = 1;
  p_self->array = (float*)malloc(sizeof(float));
  p_self->array[0] = 0.0;
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

Ndarray Ndarray_square(const Ndarray a) {
  Ndarray c;

  Ndarray_init(&c, a.dim, a.shape);
  for (int i = 0; i < c.size; i++)
    c.array[i] = a.array[i] * a.array[i];
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
    // assert(a.array[i] >= 0);
    // assert(a.array[i] != 0 || b.array[i] > 0);
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
    b.array[i] = (float)func(a.array[i]);
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
  if (p_self->dim == 0) {
    printf("%.2f\n", p_self->array[0]);
  } else {
    ndarray_print(p_self->array, p_self->dim, p_self->size, p_self->shape, TRUE);
    putchar('\n');
  }
}

Ndarray Ndarray_reshape(const Ndarray a, const int dim, const int* shape) {
  Ndarray b;
  Ndarray_init(&b, dim, shape);
  assert(a.size == b.size);
  for (int i = 0; i < b.size; i++)
    b.array[i] = a.array[i];
  return b;
}

Ndarray Ndarray_transpose2d(const Ndarray a) {
  assert(a.dim == 2);
  Ndarray b;
  Ndarray_init_shape(&b, 2, a.shape[1], a.shape[0]);
  for (int i = 0; i < a.size; i++)
    b.array[i % a.shape[1] * a.shape[0] +  i / a.shape[1]] = a.array[i];
  return b;
}

static int array_mul(const int* array, const int start, const int end) {
  int ret = 1;
  for (int i = start; i < end; i++)
    ret *= array[i];
  return ret;
}

Ndarray Ndarray_transpose(const Ndarray a, const int* axes) {
  Ndarray b;
  int* shape;
  shape = (int*)malloc(a.dim * sizeof(int));
  for (int i = 0; i < a.dim; i++)
    shape[i] = a.shape[axes[i]];
  
  Ndarray_init(&b, a.dim, shape);

  int* a_idx;
  int* b_idx;
  int* a_sizes;
  int* b_sizes;
  a_idx = (int*)malloc(a.dim * sizeof(int));
  b_idx = (int*)malloc(b.dim * sizeof(int));
  a_sizes = (int*)malloc((a.dim + 1) * sizeof(int));
  b_sizes = (int*)malloc((b.dim + 1) * sizeof(int));

  for (int i = 0; i <= a.dim; i++)
    a_sizes[i] = array_mul(a.shape, i, a.dim);
  for (int i = 0; i <= b.dim; i++)
    b_sizes[i] = array_mul(b.shape, i, b.dim);

  for (int i = 0; i < a.size; i++) {
    for (int j = 0; j < a.dim; j++)
      a_idx[j] = i % a_sizes[j] / a_sizes[j + 1];
    for (int j = 0; j < b.dim; j++)
      b_idx[j] = a_idx[axes[j]];
    int idx = 0;
    for (int j = 0; j < b.dim; j++)
      idx += b_idx[j] * b_sizes[j+1];
    b.array[idx] = a.array[i];
  }

  free(shape);
  free(a_idx);
  free(b_idx);
  free(a_sizes);
  free(b_sizes);
  return b;
}

Ndarray Ndarray_sum(Ndarray a, const int axis, const bool keepdims) {
  assert(0 <= axis && axis < a.dim);
  Ndarray b;
  int* shape;
  int cnt = 0;
  if (a.dim > 1) {
    if (!keepdims) {
      shape = (int*)malloc((a.dim-1) * sizeof(int));
      for (int i = 0; i < a.dim; i++) {
        if (i != axis)
          shape[cnt++] = a.shape[i];
      }
      Ndarray_init_as_zeros(&b, a.dim-1, shape);
    } else {
      shape = (int*)malloc(a.dim * sizeof(int));
      for (int i = 0; i < a.dim; i++) {
        if (i != axis) {
          shape[i] = a.shape[i];
        } else {
          shape[i] = 1;
        }
      }
      Ndarray_init_as_zeros(&b, a.dim, shape);
    }
    int block_size = array_mul(a.shape, axis, a.dim);
    int mini_block_size = block_size / a.shape[axis];
    for (int i = 0; i < b.size; i++) {
      for (int j = 0; j < a.shape[axis]; j++)
        b.array[i] += a.array[(i / mini_block_size) * block_size + i % mini_block_size + j * mini_block_size];
    }
  } else {
    shape = (int*)malloc(sizeof(int));
    shape[0] = 1;
    if (!keepdims) {
      Ndarray_init_as_scalar(&b);
    } else {
      Ndarray_init(&b, 1, shape);
    }
    for (int i = 0; i < a.size; i++)
      b.array[0] += a.array[i];
  }
  free(shape);
  return b;
}