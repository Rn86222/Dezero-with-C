#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <math.h>
#include <stdarg.h>
#include "../macro/constant.h"
#include "ndarray.h"
#include "../utils/manage_memory/manage_memory.h"

void Ndarray_init(Ndarray* p_self, const int dim, const int* shape) {
  if (dim == 0) {
    Ndarray_init_as_scalar(p_self);
    return;
  }
  p_self->shape = (int*)mymalloc(dim * sizeof(int));
  assert(dim > 0);
  p_self->dim = dim;
  p_self->size = 1;
  for (int i = 0; i < dim; i++) {
    if (shape[i] == 0) {
      printf("shape[%d]=0 dim=%d\n", i, dim);
      Ndarray_print(p_self);
    }
    assert(shape[i] != 0);
    p_self->shape[i] = shape[i];
    p_self->size *= shape[i];
  }
  p_self->array = (float*)mymalloc(p_self->size * sizeof(float));
}

void Ndarray_init_as_static(Ndarray* p_self, const int dim, const int* shape) {
  if (dim == 0) {
    Ndarray_init_as_scalar_as_static(p_self);
    return;
  }
  p_self->shape = (int*)malloc(dim * sizeof(int));
  assert(dim > 0);
  p_self->dim = dim;
  p_self->size = 1;
  for (int i = 0; i < dim; i++) {
    if (shape[i] == 0) {
      printf("shape[%d]=0 dim=%d\n", i, dim);
      Ndarray_print(p_self);
    }
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
  assert(dim > 0);
  va_list va_ptr;
  va_start(va_ptr, dim);
  p_self->dim = dim;
  p_self->size = 1;
  p_self->shape = (int*)mymalloc(dim * sizeof(int));
  for (int i = 0; i < dim; i++) {
    int len = va_arg(va_ptr, int);
    assert(len != 0);
    p_self->shape[i] = len;
    p_self->size *= len;
  }
  va_end(va_ptr);
  p_self->array = (float*)mymalloc(p_self->size * sizeof(float));
}

void Ndarray_init_shape_as_static(Ndarray* p_self, const int dim, ...) {
  if (dim == 0) {
    Ndarray_init_as_scalar_as_static(p_self);
    return;
  }
  assert(dim > 0);
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

void Ndarray_init_shape_rand(Ndarray* p_self, const int dim, ...) {
  if (dim == 0) {
    Ndarray_init_as_scalar(p_self);
    p_self->array[0] = (float)rand() / RAND_MAX;
    return;
  }
  assert(dim > 0);
  va_list va_ptr;
  va_start(va_ptr, dim);
  p_self->dim = dim;
  p_self->size = 1;
  p_self->shape = (int*)mymalloc(dim * sizeof(int));
  for (int i = 0; i < dim; i++) {
    int len = va_arg(va_ptr, int);
    assert(len != 0);
    p_self->shape[i] = len;
    p_self->size *= len;
  }
  va_end(va_ptr);
  p_self->array = (float*)mymalloc(p_self->size * sizeof(float));
  for (int i = 0; i < p_self->size; i++)
    p_self->array[i] = (float)rand() / RAND_MAX;
}

void Ndarray_init_shape_rand_as_static(Ndarray* p_self, const int dim, ...) {
  if (dim == 0) {
    Ndarray_init_as_scalar_as_static(p_self);
    p_self->array[0] = (float)rand() / RAND_MAX;
    return;
  }
  assert(dim > 0);
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
  for (int i = 0; i < p_self->size; i++)
    p_self->array[i] = (float)rand() / RAND_MAX;
}

void Ndarray_init_shape_randn(Ndarray* p_self, const int dim, ...) {
  if (dim == 0) {
    Ndarray_init_as_scalar(p_self);
    float u1 = (float)rand() / RAND_MAX;
    float u2 = (float)rand() / RAND_MAX;
    p_self->array[0] = sqrt(-2.0 * log(u1)) * cos(2 * M_PI * u2);
    return;
  }
  assert(dim > 0);
  va_list va_ptr;
  va_start(va_ptr, dim);
  p_self->dim = dim;
  p_self->size = 1;
  p_self->shape = (int*)mymalloc(dim * sizeof(int));
  for (int i = 0; i < dim; i++) {
    int len = va_arg(va_ptr, int);
    assert(len != 0);
    p_self->shape[i] = len;
    p_self->size *= len;
  }
  va_end(va_ptr);
  p_self->array = (float*)mymalloc(p_self->size * sizeof(float));
  for (int i = 0; i < p_self->size; i++) {
    float u1 = (float)rand() / RAND_MAX;
    float u2 = (float)rand() / RAND_MAX;
    p_self->array[i] = sqrt(-2.0 * log(u1)) * cos(2 * M_PI * u2);
  }
}

void Ndarray_init_shape_randn_as_static(Ndarray* p_self, const int dim, ...) {
  if (dim == 0) {
    Ndarray_init_as_scalar_as_static(p_self);
    float u1 = (float)rand() / RAND_MAX;
    float u2 = (float)rand() / RAND_MAX;
    p_self->array[0] = sqrt(-2.0 * log(u1)) * cos(2 * M_PI * u2);
    return;
  }
  assert(dim > 0);
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
  for (int i = 0; i < p_self->size; i++) {
    float u1 = (float)rand() / RAND_MAX;
    float u2 = (float)rand() / RAND_MAX;
    p_self->array[i] = sqrt(-2.0 * log(u1)) * cos(2 * M_PI * u2);
  }
}

void Ndarray_init_shape_zero(Ndarray* p_self, const int dim, ...) {
  if (dim == 0) {
    Ndarray_init_as_scalar(p_self);
    p_self->array[0] = 0.0;
    return;
  }
  assert(dim > 0);
  va_list va_ptr;
  va_start(va_ptr, dim);
  p_self->dim = dim;
  p_self->size = 1;
  p_self->shape = (int*)mymalloc(dim * sizeof(int));
  for (int i = 0; i < dim; i++) {
    int len = va_arg(va_ptr, int);
    assert(len != 0);
    p_self->shape[i] = len;
    p_self->size *= len;
  }
  va_end(va_ptr);
  p_self->array = (float*)mymalloc(p_self->size * sizeof(float));
  for (int i = 0; i < p_self->size; i++)
    p_self->array[i] = 0.0;
}

void Ndarray_init_shape_zero_as_static(Ndarray* p_self, const int dim, ...) {
  if (dim == 0) {
    Ndarray_init_as_scalar_as_static(p_self);
    p_self->array[0] = 0.0;
    return;
  }
  assert(dim > 0);
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
  for (int i = 0; i < p_self->size; i++)
    p_self->array[i] = 0.0;
}

void Ndarray_init_as_zeros(Ndarray* p_self, const int dim, const int* shape) {
  if (dim == 0) {
    Ndarray_init_as_scalar(p_self);
    return;
  }
  p_self->shape = (int*)mymalloc(dim * sizeof(int));
  assert(dim > 0);
  p_self->dim = dim;
  p_self->size = 1;
  for (int i = 0; i < dim; i++) {
    assert(shape[i] != 0);
    p_self->shape[i] = shape[i];
    p_self->size *= shape[i];
  }
  p_self->array = (float*)mymalloc(p_self->size * sizeof(float));
  for (int i = 0; i < p_self->size; i++) {
    p_self->array[i] = 0.0;
  }
}

void Ndarray_init_as_scalar(Ndarray* p_self) {
  p_self->shape = (int*)mymalloc(sizeof(int));
  p_self->dim = 0;
  p_self->size = 1;
  p_self->shape[0] = 1;
  p_self->array = (float*)mymalloc(sizeof(float));
  p_self->array[0] = 0.0;
}

void Ndarray_init_as_scalar_as_static(Ndarray* p_self) {
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

static void ndarray_auto_broadcast(Ndarray* p_new_a, Ndarray* p_new_b, const Ndarray a, const Ndarray b) {
  if (a.size < b.size) {
    *p_new_a = Ndarray_broadcast_to(a, b.dim, b.shape);
    Ndarray_init(p_new_b, b.dim, b.shape);
    for (int i = 0; i < b.size; i++)
      p_new_b->array[i] = b.array[i];
  } else {
    *p_new_b = Ndarray_broadcast_to(b, a.dim, a.shape);
    Ndarray_init(p_new_a, a.dim, a.shape);
    for (int i = 0; i < a.size; i++)
      p_new_a->array[i] = a.array[i];
  }
}

Ndarray Ndarray_add(const Ndarray a, const Ndarray b) {
  Ndarray new_a, new_b, c;
  ndarray_auto_broadcast(&new_a, &new_b, a, b);

  Ndarray_init(&c, new_a.dim, new_a.shape);
  for (int i = 0; i < c.size; i++)
    c.array[i] = new_a.array[i] + new_b.array[i];
  return c;
}

Ndarray Ndarray_sub(const Ndarray a, const Ndarray b) {
  Ndarray new_a, new_b, c;
  ndarray_auto_broadcast(&new_a, &new_b, a, b);

  Ndarray_init(&c, new_a.dim, new_a.shape);
  for (int i = 0; i < c.size; i++)
    c.array[i] = new_a.array[i] - new_b.array[i];
  return c;
} 

Ndarray Ndarray_sub_as_static(const Ndarray a, const Ndarray b) {
  Ndarray new_a, new_b, c;
  ndarray_auto_broadcast(&new_a, &new_b, a, b);

  Ndarray_init_as_static(&c, new_a.dim, new_a.shape);
  for (int i = 0; i < c.size; i++)
    c.array[i] = new_a.array[i] - new_b.array[i];
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
  Ndarray new_a, new_b, c;
  ndarray_auto_broadcast(&new_a, &new_b, a, b);

  Ndarray_init(&c, new_a.dim, new_a.shape);
  for (int i = 0; i < c.size; i++)
    c.array[i] = new_a.array[i] * new_b.array[i];
  return c;
}

Ndarray Ndarray_div(const Ndarray a, const Ndarray b) {
  Ndarray new_a, new_b, c;
  ndarray_auto_broadcast(&new_a, &new_b, a, b);

  Ndarray_init(&c, new_a.dim, new_a.shape);
  for (int i = 0; i < c.size; i++) {
    assert(new_b.array[i] != 0);
    c.array[i] = new_a.array[i] / new_b.array[i];
  }
  return c;
}

Ndarray Ndarray_pow(const Ndarray a, const Ndarray b) {
  Ndarray new_a, new_b, c;
  ndarray_auto_broadcast(&new_a, &new_b, a, b);

  Ndarray_init(&c, new_a.dim, new_a.shape);
  for (int i = 0; i < c.size; i++) {
    // assert(a.array[i] >= 0);
    // assert(a.array[i] != 0 || b.array[i] > 0);
    c.array[i] = pow(new_a.array[i], new_b.array[i]);
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

Ndarray Ndarray_constant_mul_as_static(const Ndarray a, float c) {
  Ndarray b;
  Ndarray_init_as_static(&b, a.dim, a.shape);
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
  free(down_shape);
  free(down_array);
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

static void ndarray_broadcast(const int size, const int dim,  const int* shape, float* array,  const int ori_size, const int* ori_shape, const float* ori_array) {
  if (dim == 1) {
    assert(ori_shape[0] == shape[0] || ori_shape[0] == 1);
    if (ori_shape[0] != shape[0]) {
      for (int i = 0; i < shape[0]; i++)
        array[i] = ori_array[0];
    } else {
      for (int i = 0; i < shape[0]; i++)
        array[i] = ori_array[i];
    }
    return;
  }
  if (ori_shape[0] != shape[0]) {
    for (int i = 0; i < shape[0]; i++)
      ndarray_broadcast(size / shape[0], dim - 1, shape + 1, array + i * size / shape[0], ori_size, ori_shape + 1, ori_array);
  } else {
    for (int i = 0; i < shape[0]; i++)
      ndarray_broadcast(size / shape[0], dim - 1, shape + 1, array + i * size / shape[0],  ori_size / shape[0], ori_shape + 1, ori_array + i * ori_size / shape[0]);
  }
}

Ndarray Ndarray_broadcast_to(const Ndarray a, const int dim, const int* shape) {
  if (dim == 0)
    return a;
  Ndarray b;
  Ndarray_init(&b, dim, shape);

  if (dim == 1) {
    assert(a.shape[0] == shape[0] || a.shape[0] == 1);
    if (a.shape[0] != shape[0]) {
      for (int i = 0; i < shape[0]; i++)
        b.array[i] = a.array[0];
    } else {
      for (int i = 0; i < shape[0]; i++)
        b.array[i] = a.array[i];
    }
    return b;
  }

  int size = 1;
  int b_size = a.size;
  for (int i = 0; i < a.dim; i++) {
    if (a.shape[a.dim - i - 1] != shape[dim - i - 1] && a.shape[a.dim - i - 1] != 1)
      printf("a.shape[%d-%d-1]=%d %d shape[%d-%d-1]=%d\n", a.dim, i, a.shape[a.dim-i-1], a.shape[1], dim, i, shape[dim-i-1]);
    assert(a.shape[a.dim - i - 1] == shape[dim - i - 1] || a.shape[a.dim - i - 1] == 1);
  }
  for (int i = 0; i < dim; i++) 
    size *= shape[i];
  int* b_shape;
  b_shape = (int*)malloc(dim * sizeof(int));
  for (int i = 0; i < dim - a.dim; i++)
    b_shape[i] = 1;
  for (int i = dim - a.dim; i < dim; i++)
    b_shape[i] = a.shape[i - dim + a.dim];

  if (b_shape[0] != shape[0]) {
    for (int i = 0; i < shape[0]; i++)
      ndarray_broadcast(size / shape[0], dim - 1, shape + 1, b.array + i * size / shape[0], a.size, b_shape + 1, a.array);
  } else {
    for (int i = 0; i < shape[0]; i++)
      ndarray_broadcast(size / shape[0], dim - 1, shape + 1, b.array + i * size / shape[0], a.size / shape[0], b_shape + 1, a.array + i * a.size / shape[0]);
  }
  free(b_shape);
  return b;
}

Ndarray Ndarray_sum_to(const Ndarray a, const int dim, const int* shape) {
  Ndarray b = a;
  int ddim = a.dim - dim;
  assert(ddim >= 0);
  for (int i = 0; i < a.dim; i++) {
    if (i < ddim) {
      b = Ndarray_sum(b, 0, FALSE);
    } else {
      if (shape[i - ddim] != a.shape[i]) {
        assert(shape[i - ddim] == 1);
        b = Ndarray_sum(b, i - ddim, TRUE);
      }
    }
  }
  return b;
}

Ndarray Ndarray_dot(const Ndarray a, const Ndarray b) {
  Ndarray c;
  int* shape;
  shape = (int*)malloc(a.dim * sizeof(int));

  if (a.dim == 1) {
    assert(b.dim == 1 && a.size == b.size);
    shape[0] = 1;
    Ndarray_init(&c, 0, shape);
    for (int i = 0; i < a.size; i++)
      c.array[0] += a.array[i] * b.array[i];
    return c;
  } else if (a.dim == 2) {
    assert(b.dim == 2 && a.shape[1] == b.shape[0]);
    shape[0] = a.shape[0];
    shape[1] = b.shape[1];
    Ndarray_init_as_zeros(&c, 2, shape);
    for (int i = 0; i < a.shape[0]; i++) {
      for (int j = 0; j < b.shape[1]; j++) {
        for (int k = 0; k < a.shape[1]; k++)
          c.array[i * shape[1] + j] += a.array[i * a.shape[1] + k] * b.array[k * b.shape[1] + j];
      }
    }
    free(shape);
    return c;
  } else {
    free(shape);
    printf("Ndarray_dot error: can't manipulate 3- or more- dimention-array.");
    return a;
  }
}

void Ndarray_destroy(Ndarray* p_self) {
  if (p_self != NULL) {
    if (p_self->array != NULL) {
      free(p_self->array);
      p_self->array = NULL;
    }
    if (p_self->shape != NULL) {
      free(p_self->shape);
      p_self->shape = NULL;
    }
    p_self->size = 0;
    p_self->dim = 0;
    if (p_self != NULL) {
      free(p_self);
    }
  }
}