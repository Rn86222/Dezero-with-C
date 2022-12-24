#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "variable/variable.h"
#include "function/function.h"
#include "function/functions.h"
#include "ndarray/ndarray.h"
#include "macro/constant.h"
#include "dot/dot.h"
#include "function/reshape.h"

#define GNUPLOT "gnuplot -persist"

Variable* predict(Variable* x, Variable* W1, Variable* b1, Variable* W2, Variable* b2) {
  Variable* y;
  y = linear(x, W1, b1);
  y = sigmoid(y);
  y = linear(y, W2, b2);
  return y;
}

int main() {
  srand(0);
  Ndarray x_data, y_data;
  Ndarray_init_shape_rand(&x_data, 2, 100, 1);
  Ndarray_init_shape(&y_data, 2, 100, 1);
  for (int i = 0; i < x_data.size; i++)
    y_data.array[i] = sin(2 * M_PI * x_data.array[i]) + (float)rand() / RAND_MAX;

  FILE *gp;
 
  if ((gp = popen(GNUPLOT, "w")) == NULL) {
    fprintf(stderr, "Error: cannot open \"%s\".\n", GNUPLOT);
    exit(1);
  }

  fprintf(gp, "set terminal png\n");
  fprintf(gp, "\n");
  fprintf(gp, "set out 'regression.png'\n");
  fprintf(gp, "set xrange [%f:%f]\n", 0.0, 1.0);
  fprintf(gp, "set yrange [-1.0:2.0]\n");
  fprintf(gp, "plot '-' with points pt 3 title \"sample\", '-' with points pt 1 title \"regression\"\n");
  for (int i = 0; i < 100; i++)
    fprintf(gp, "%f\t%f\n", x_data.array[i], y_data.array[i]);
  fprintf(gp, "e\n");

  Variable x, y;
  Variable_init(&x, x_data, "x");
  Variable_init(&y, y_data, "y");

  int I = 1;
  int H = 10;
  int O = 1;

  Variable W1, b1, W2, b2;
  Ndarray W1_data, b1_data, W2_data, b2_data;

  Ndarray_init_shape_randn(&W1_data, 2, I, H);
  W1_data = Ndarray_constant_mul(W1_data, 0.01);
  Variable_init(&W1, W1_data, "W1");
  Ndarray_init_shape_zero(&b1_data, 1, H);
  Variable_init(&b1, b1_data, "b1");
  Ndarray_init_shape_randn(&W2_data, 2, H, O);
  W2_data = Ndarray_constant_mul(W2_data, 0.01);
  Variable_init(&W2, W2_data, "W2");
  Ndarray_init_shape_zero(&b2_data, 1, O);
  Variable_init(&b2, b2_data, "b2");

  float lr = 0.2;
  int iters = 10000;

  Variable* y_pred;
  Variable* loss;

  for (int i = 0; i < iters; i++) {
   
    y_pred = predict(&x, &W1, &b1, &W2, &b2);
    loss = mse(&y, y_pred);

    Variable_cleargrad(&W1);
    Variable_cleargrad(&b1);
    Variable_cleargrad(&W2);
    Variable_cleargrad(&b2);

    Variable_backward(loss, FALSE);

    *(W1.p_data) = Ndarray_sub(*(W1.p_data), Ndarray_constant_mul(*(W1.p_grad->p_data), lr));
    *(b1.p_data) = Ndarray_sub(*(b1.p_data), Ndarray_constant_mul(*(b1.p_grad->p_data), lr));
    *(W2.p_data) = Ndarray_sub(*(W2.p_data), Ndarray_constant_mul(*(W2.p_grad->p_data), lr));
    *(b2.p_data) = Ndarray_sub(*(b2.p_data), Ndarray_constant_mul(*(b2.p_grad->p_data), lr));

    if (i % 1000 == 0)
      Ndarray_print(loss->p_data);
  }

  for (int i = 0; i < 100; i++) {
    fprintf(gp, "%f\t%f\n", x_data.array[i], predict(&x, &W1, &b1, &W2, &b2)->p_data->array[i]);
  }

  fprintf(gp, "set terminal windows\n");

  fprintf(gp, "set output\n");

  if (pclose(gp) == EOF) {
    fprintf(stderr, "Error: cannot close \"%s\".\n", GNUPLOT);
    exit(2);
  }

  // plot_dot_graph(loss, FALSE, FALSE, "loss_graph.png");
  return 0;
}