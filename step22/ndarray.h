#ifndef _NDARRAY_H_
#define _NDARRAY_H_

typedef struct ndarray {
  float* array;
  int size;
  int dim;
  int* shape;
} Ndarray;

void Ndarray_init(Ndarray* p_self, const int dim, const int* shape);
void Ndarray_init_as_zeros(Ndarray* p_self, const int dim, const int* shape);
void Ndarray_copy(Ndarray* p_self, const Ndarray original);
Ndarray Ndarray_add(const Ndarray a, const Ndarray b);
Ndarray Ndarray_sub(const Ndarray a, const Ndarray b);
Ndarray Ndarray_mul(const Ndarray a, const Ndarray b);
Ndarray Ndarray_div(const Ndarray a, const Ndarray b);
Ndarray Ndarray_pow(const Ndarray a, const Ndarray b);
Ndarray Ndarray_constant_add(const Ndarray a, float c);
Ndarray Ndarray_constant_mul(const Ndarray a, float c);
Ndarray Ndarray_neg(const Ndarray a);
Ndarray Ndarray_map(const Ndarray a, double (*func)(double));
void Ndarray_print(const Ndarray* p_self);

#endif // _NDARRAY_H_