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
#include "macro/macro.h"

int main() {
  Variable x;
  Ndarray x_data;
  int x_data_shape[1] = {1};
  Ndarray_init(&x_data, 1, x_data_shape);
  x_data.array[0] = 1.0;

  Variable y;
  Ndarray y_data;
  int y_data_shape[1] = {1};
  Ndarray_init(&y_data, 1, y_data_shape);
  y_data.array[0] = 1.0;

  Variable_init(&x, x_data, "x");
  Variable_init(&y, y_data, "y");

  Square sq[6];
  for (int i = 0; i < 6; i++)
    Square_init(&sq[i]);
  Add add[10];
  for(int i = 0; i < 10; i++)
    Add_init(&add[i]);
  Sub sub[5];
  for (int i = 0; i < 5; i++)
    Sub_init(&sub[i]);
  Mul mul[17];
  for (int i = 0; i < 17; i++)
    Mul_init(&mul[i]);
  
  Variable** z;
  z = VM(mul[0]);
  z = FC2(&mul[0], "z", fc2cl0(&add[0], 1.0, fc20(&mul[1], fc10(&sq[0], fc20(&add[1], &x, fc2c0(&add[2], &y, 1.0))), fc20(&add[3], fc2cl0(&sub[0], 19.0, fc2cl0(&mul[2], 14.0, &x)), fc20(&add[4], fc20(&sub[1], fc2cl0(&mul[3], 3.0, fc10(&sq[1], &x)), fc2cl0(&mul[4], 14.0, &y)), fc20(&add[5], fc2cl0(&mul[5], 6.0, fc20(&mul[6], &x, &y)), fc2cl0(&mul[7], 3.0, fc10(&sq[2], &y))))))), 
                        fc2cl0(&add[6], 30.0, fc20(&mul[8], fc10(&sq[3], fc20(&sub[2], fc2c0(&mul[9], &x, 2.0), fc2cl0(&mul[10], 3.0, &y))), fc20(&add[7], fc2cl0(&sub[3], 18.0, fc2cl0(&mul[11], 32.0, &x)), fc20(&add[8], fc20(&add[9], fc2cl0(&mul[12], 12.0, fc10(&sq[4], &x)), fc2cl0(&mul[13], 48.0, &y)), fc20(&sub[4], fc2cl0(&mul[14], 27.0, fc10(&sq[5], &y)), fc2cl0(&mul[15], 36.0, fc20(&mul[16], &x, &y))))))));

  Variable_backward(z[0], TRUE);

  Ndarray_print(x.p_grad);
  Ndarray_print(y.p_grad);

  Variable_print(&x);
  Variable_print(z[0]);
  
  printf("\nmain end\n");
  return 0;
}