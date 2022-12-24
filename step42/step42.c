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

Variable* predict(Variable* x, Variable* W, Variable* b) {
  return add(matmul(x, W), b);
}

int main() {
  srand(0);
  Ndarray x_data, y_data;
  Ndarray_init_shape_rand(&x_data, 2, 100, 1);
  Ndarray_init_shape(&y_data, 2, 100, 1);
  for (int i = 0; i < x_data.size; i++)
    y_data.array[i] = 5 + 2 * x_data.array[i] + (float)rand() / RAND_MAX;

  FILE *gp;
 
  if ((gp = popen(GNUPLOT, "w")) == NULL) {
    fprintf(stderr, "Error: cannot open \"%s\".\n", GNUPLOT);
    exit(1);
  }

  fprintf(gp, "set terminal png\n");
  fprintf(gp, "\n");
  fprintf(gp, "set out 'regression.png'\n");
  fprintf(gp, "set xrange [%f:%f]\n", 0.0, 1.0);
  fprintf(gp, "set yrange [5.0:8.0]\n");
  fprintf(gp, "plot '-' with points pt 3 title \"sample\", '-' with line title \"regression\"\n");
  for (int i = 0; i < 100; i++)
    fprintf(gp, "%f\t%f\n", x_data.array[i], y_data.array[i]);
  fprintf(gp, "e\n");
 

  Variable x, y;
  Variable_init(&x, x_data, "x");
  Variable_init(&y, y_data, "y");

  Variable W, b;
  Ndarray W_data, b_data;
  Ndarray_init_shape_zero(&W_data, 2, 1, 1);
  Variable_init(&W, W_data, "W");
  Ndarray_init_shape_zero(&b_data, 1, 1);
  Variable_init(&b, b_data, "b");


  float lr = 0.1;
  int iters = 100;

  Variable* y_pred;
  Variable* loss;

  for (int i = 0; i < iters; i++) {
    y_pred = predict(&x, &W, &b);
    loss = mse(y_pred, &y);

    Variable_cleargrad(&W);
    Variable_cleargrad(&b);

    Variable_backward(loss, FALSE);

    *(W.p_data) = Ndarray_sub(*(W.p_data), Ndarray_constant_mul(*(W.p_grad->p_data), lr));
    *(b.p_data) = Ndarray_sub(*(b.p_data), Ndarray_constant_mul(*(b.p_grad->p_data), lr));
    Ndarray_print(W.p_data);
    Ndarray_print(b.p_data);
    Ndarray_print(loss->p_data);
  }

  fprintf(gp, "%f\t%f\n", 0.0, b.p_data->array[0]);
  fprintf(gp, "%f\t%f\n", 1.0, W.p_data->array[0] + b.p_data->array[0]);

  fprintf(gp, "set terminal windows\n");

  fprintf(gp, "set output\n");

  if (pclose(gp) == EOF) {
    fprintf(stderr, "Error: cannot close \"%s\".\n", GNUPLOT);
    exit(2);
  }

  plot_dot_graph(loss, FALSE, FALSE, "loss_graph.png");
  return 0;
}