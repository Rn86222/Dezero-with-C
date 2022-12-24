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
#include "layer/linearl.h"

#define GNUPLOT "gnuplot -persist"

Variable* predict(Variable* x, LinearL* l1, LinearL* l2) {
  Variable* y;
  y = Layer_call((Layer*)l1, x)[0];
  y = sigmoid(y);
  y = Layer_call((Layer*)l2, y)[0];
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

  LinearL l1;
  LinearL_init(&l1, 10);
  LinearL l2;
  LinearL_init(&l2, 1);
  
  float lr = 0.2;
  int iters = 10000;

  Variable* y_pred;
  Variable* loss;

  for (int i = 0; i < iters; i++) {
   
    y_pred = predict(&x, &l1, &l2);
    loss = mse(&y, y_pred);

    Layer_cleargrads((Layer*)&l1);
    Layer_cleargrads((Layer*)&l2);

    Variable_backward(loss, FALSE);

    for (int j = 0; j < ((Layer*)&l1)->param_num; j++) {
      Ndarray param_data = *(((Layer*)&l1)->params[j]->p_data);
      Ndarray param_grad = *(((Layer*)&l1)->params[j]->p_grad->p_data);
      *(((Layer*)&l1)->params[j]->p_data) = Ndarray_sub(param_data, Ndarray_constant_mul(param_grad, lr));
    }
    for (int j = 0; j < ((Layer*)&l2)->param_num; j++) {
      Ndarray param_data = *(((Layer*)&l2)->params[j]->p_data);
      Ndarray param_grad = *(((Layer*)&l2)->params[j]->p_grad->p_data);
      *(((Layer*)&l2)->params[j]->p_data) = Ndarray_sub(param_data, Ndarray_constant_mul(param_grad, lr));
    }

    if (i % 1000 == 0)
      Ndarray_print(loss->p_data);
  }

  for (int i = 0; i < 100; i++) {
    fprintf(gp, "%f\t%f\n", x_data.array[i], predict(&x, &l1, &l2)->p_data->array[i]);
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