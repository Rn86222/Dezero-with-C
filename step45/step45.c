#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "variable/variable.h"
#include "function/functions.h"
#include "ndarray/ndarray.h"
#include "macro/constant.h"
#include "dot/dot.h"
#include "layer/layers.h"

#define GNUPLOT "gnuplot -persist"

Variable* predict(Variable* x, Layer* model) {
  Variable* y;
  y = Layer_call(model, x)[0];
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

  // LinearL l1;
  // LinearL_init(&l1, 10, 0);
  // LinearL l2;
  // LinearL_init(&l2, 1, 0);
  // Layer model;
  // Layer_init(&model, 1, 1, 0, 2);
  // Layer_add_layer(&model, (Layer*)&l1);
  // Layer_add_layer(&model, (Layer*)&l2);

  TwoLayerNet model;
  TwoLayerNet_init(&model, 10, 1);
  
  float lr = 0.2;
  int iters = 20000;

  Variable* y_pred;
  Variable* loss;

  for (int i = 0; i < iters; i++) {
    
    y_pred = predict(&x, (Layer*)&model);
    loss = mse(&y, y_pred);

    Layer_cleargrads((Layer*)&model);

    Variable_backward(loss, FALSE);

    // for (int i = 0; i < ((Layer*)&model)->layer_num; i++) {
    //   for (int j = 0; j < ((Layer*)&model)->p_layers[i]->param_num; j++) {
    //     Ndarray param_data = *(((Layer*)&model)->p_layers[i]->p_params[j]->p_data);
    //     Ndarray param_grad = *(((Layer*)&model)->p_layers[i]->p_params[j]->p_grad->p_data);
    //      *(((Layer*)&model)->p_layers[i]->p_params[j]->p_data) = Ndarray_sub(param_data, Ndarray_constant_mul(param_grad, lr));
    //   }
    // }
    Layer_update_params((Layer*)&model, lr);

    if (i % 1000 == 0) {
      Ndarray_print(loss->p_data);
      // printf("\033[%dA" ,1); //カーソルを1行だけ上に移動
    }
    
    Variable_destroy(loss, TRUE);
  }

  for (int i = 0; i < 100; i++)
    fprintf(gp, "%f\t%f\n", x_data.array[i], predict(&x, (Layer*)&model)->p_data->array[i]);

  fprintf(gp, "set terminal windows\n");

  fprintf(gp, "set output\n");

  if (pclose(gp) == EOF) {
    fprintf(stderr, "Error: cannot close \"%s\".\n", GNUPLOT);
    exit(2);
  }

  // plot_dot_graph(loss, FALSE, FALSE, "loss_graph.png");
  return 0;
}