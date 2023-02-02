#include "../macro/constant.h"

#ifndef _NDARRAY_H_
#define _NDARRAY_H_

typedef struct ndarray {
  float* array;
  int size;
  int dim;
  int* shape;
} Ndarray;

void Ndarray_init(Ndarray* p_self, const int dim, const int* shape);
void Ndarray_init_as_static(Ndarray* p_self, const int dim, const int* shape);
void Ndarray_init_shape(Ndarray* p_self, const int dim, ...);
void Ndarray_init_shape_as_static(Ndarray* p_self, const int dim, ...);
void Ndarray_init_shape_rand(Ndarray* p_self, const int dim, ...);
void Ndarray_init_shape_rand_as_static(Ndarray* p_self, const int dim, ...);
void Ndarray_init_shape_randn(Ndarray* p_self, const int dim, ...);
void Ndarray_init_shape_randn_as_static(Ndarray* p_self, const int dim, ...);
void Ndarray_init_shape_zero(Ndarray* p_self, const int dim, ...);
void Ndarray_init_shape_zero_as_static(Ndarray* p_self, const int dim, ...);
void Ndarray_init_as_zeros(Ndarray* p_self, const int dim, const int* shape);
void Ndarray_init_as_scalar(Ndarray* p_self);
void Ndarray_init_as_scalar_as_static(Ndarray* p_self);
void Ndarray_copy(Ndarray* p_self, const Ndarray original);
Ndarray Ndarray_add(const Ndarray a, const Ndarray b);
Ndarray Ndarray_sub(const Ndarray a, const Ndarray b);
Ndarray Ndarray_sub_as_static(const Ndarray a, const Ndarray b);
Ndarray Ndarray_square(const Ndarray a);
Ndarray Ndarray_mul(const Ndarray a, const Ndarray b);
Ndarray Ndarray_div(const Ndarray a, const Ndarray b);
Ndarray Ndarray_pow(const Ndarray a, const Ndarray b);
Ndarray Ndarray_constant_add(const Ndarray a, float c);
Ndarray Ndarray_constant_mul(const Ndarray a, float c);
Ndarray Ndarray_constant_mul_as_static(const Ndarray a, float c);
Ndarray Ndarray_neg(const Ndarray a);
Ndarray Ndarray_map(const Ndarray a, double (*func)(double));
void Ndarray_print(const Ndarray* p_self);
Ndarray Ndarray_reshape(const Ndarray a, const int dim, const int* shape);
Ndarray Ndarray_transpose2d(const Ndarray a);
Ndarray Ndarray_transpose(const Ndarray a, const int* axes);
Ndarray Ndarray_sum(Ndarray a, const int axis, const bool keepdims);
Ndarray Ndarray_broadcast_to(const Ndarray a, const int dim, const int* shape);
Ndarray Ndarray_sum_to(const Ndarray a, const int dim, const int* shape);
Ndarray Ndarray_dot(const Ndarray a, const Ndarray b);
void Ndarray_destroy(Ndarray* p_self);

#endif // _NDARRAY_H_