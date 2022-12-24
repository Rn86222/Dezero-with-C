#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "function/square.h"
#include "variable/variable.h"
#include "function/function.h"
#include "function/add.h"
#include "function/mul.h"
#include "function/neg.h"
#include "function/sub.h"
#include "ndarray/ndarray.h"

#define FC1(p_func, variable_name, p_v) Function_call((Function*)p_func, variable_name, p_v)
#define FC10(p_func, variable_name, p_v) Function_call((Function*)p_func, variable_name, p_v)[0]
#define fc1(p_func, p_v) Function_call((Function*)p_func, "", p_v)
#define fc10(p_func, p_v) Function_call((Function*)p_func, "", p_v)[0]
#define FC2(p_func, variable_name, p_v0, p_v1) Function_call((Function*)p_func, variable_name, p_v0, p_v1)
#define FC20(p_func, variable_name, p_v0, p_v1) Function_call((Function*)p_func, variable_name, p_v0, p_v1)[0]
#define fc2(p_func, p_v0, p_v1) Function_call((Function*)p_func, "", p_v0, p_v1)
#define fc20(p_func, p_v0, p_v1) Function_call((Function*)p_func, "", p_v0, p_v1)[0]
#define FD(p_func) Function_destroy((Function*)p_func)
#define VM(func) (Variable**)malloc(func.function.output_num * sizeof(Variable*))

int main() {
  Variable x;
  Ndarray x_data;
  int x_data_shape[1] = {1};
  Ndarray_init(&x_data, 1, x_data_shape);
  x_data.array[0] = 1.0;

  Variable a;
  Ndarray a_data;
  int a_data_shape[1] = {1};
  Ndarray_init(&a_data, 1, a_data_shape);
  a_data.array[0] = 1.0;

  Variable b;
  Variable_init_as_one_constant(&b, 0.26);

  Variable c;
  Variable_init_as_one_constant(&c, 0.48);

  Variable_init(&x, x_data, "x");
  Variable_init(&a, a_data, "a");

  Square sq0;
  Square_init(&sq0);
  Square sq1;
  Square_init(&sq1);
  Add add;
  Add_init(&add);
  Sub sub;
  Sub_init(&sub);
  Mul mul0;
  Mul_init(&mul0);
  Mul mul1;
  Mul_init(&mul1);
  Mul mul2;
  Mul_init(&mul2);

  Variable** y;
  y = VM(sub);
  y = FC2(&sub, "y", fc20(&mul0, &b, fc20(&add, fc10(&sq0, &x), fc10(&sq1, &a))), fc20(&mul1, &c, fc20(&mul2, &x, &a)));

  Variable_backward(y[0], FALSE);

  Ndarray_print(x.p_grad);
  Ndarray_print(a.p_grad);

  Variable_print(&x);
  Variable_print(y[0]);
  
  printf("\nmain end\n");
  return 0;
}