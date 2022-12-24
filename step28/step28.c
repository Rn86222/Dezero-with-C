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
#include "function/sin.h"
#include "ndarray/ndarray.h"
#include "macro/macro.h"
#include "macro/constant.h"
#include "dot/dot.h"
#include "function/pow.h"

#define MAX_LOOP 30000

int main() {
  Variable x;
  Ndarray x_data;
  int x_data_shape[1] = {1};
  Ndarray_init(&x_data, 1, x_data_shape);
  x_data.array[0] = 0.0;

  Variable y;
  Ndarray y_data;
  int y_data_shape[1] = {1};
  Ndarray_init(&y_data, 1, y_data_shape);
  y_data.array[0] = 2.0;

  Variable_init(&x, x_data, "x");
  Variable_init(&y, y_data, "y");

  
  Sub sub[2];
  for (int i = 0; i < 2; i++)
    Sub_init(&sub[i]);
  // Pow mpow[4];
  // for (int i = 0; i < 4; i++)
  //   Pow_init(&mpow[i]);
  Square sq[3];
  for (int i = 0; i < 3; i++)
    Square_init(&sq[i]);
  Add add;
  Add_init(&add);
  // Sub sub[5];
  // for (int i = 0; i < 5; i++)
  //   Sub_init(&sub[i]);
  Mul mul;
  Mul_init(&mul);
  // Sin sin;
  // Sin_init(&sin);
  
  // Variable** z;
  // z = VM(mul[0]);
  // z = FC2(&mul[0], "z", fc2cl0(&add[0], 1.0, fc20(&mul[1], fc10(&sq[0], fc20(&add[1], &x, fc2c0(&add[2], &y, 1.0))), fc20(&add[3], fc2cl0(&sub[0], 19.0, fc2cl0(&mul[2], 14.0, &x)), fc20(&add[4], fc20(&sub[1], fc2cl0(&mul[3], 3.0, fc10(&sq[1], &x)), fc2cl0(&mul[4], 14.0, &y)), fc20(&add[5], fc2cl0(&mul[5], 6.0, fc20(&mul[6], &x, &y)), fc2cl0(&mul[7], 3.0, fc10(&sq[2], &y))))))), 
  //                       fc2cl0(&add[6], 30.0, fc20(&mul[8], fc10(&sq[3], fc20(&sub[2], fc2c0(&mul[9], &x, 2.0), fc2cl0(&mul[10], 3.0, &y))), fc20(&add[7], fc2cl0(&sub[3], 18.0, fc2cl0(&mul[11], 32.0, &x)), fc20(&add[8], fc20(&add[9], fc2cl0(&mul[12], 12.0, fc10(&sq[4], &x)), fc2cl0(&mul[13], 48.0, &y)), fc20(&sub[4], fc2cl0(&mul[14], 27.0, fc10(&sq[5], &y)), fc2cl0(&mul[15], 36.0, fc20(&mul[16], &x, &y))))))));

  float lr = 0.0001;

  Variable** z;
  z = VM(add);

  for (int i = 0; i < MAX_LOOP; i++) {
    // Ndarray_print(x.p_data);
    // Ndarray_print(y.p_data);
    z = FC2(&add, "z", fc2cl0(&mul, 100.0, fc10(&sq[0], fc20(&sub[0], &x, fc10(&sq[1], &y)))), fc10(&sq[2], fc2c0(&sub[1], &x, 1.0)));
    Variable_cleargrad(&x);
    Variable_cleargrad(&y);
    Variable_backward(z[0], FALSE);
    *(x.p_data) = Ndarray_sub(*(x.p_data), Ndarray_constant_mul(*(x.p_grad), lr));
    *(y.p_data) = Ndarray_sub(*(y.p_data), Ndarray_constant_mul(*(y.p_grad), lr));
  }

  Variable_backward(z[0], FALSE);
  
  plot_dot_graph(z[0], FALSE, FALSE, "graph.png");

  Ndarray_print(x.p_grad);
  Ndarray_print(y.p_grad);

  Variable_print(&x);
  Variable_print(&y);
  Variable_print(z[0]);

  // printf("\nmain end\n");
  return 0;
}