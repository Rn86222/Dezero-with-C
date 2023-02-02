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
#include "utils/enable_backdrop/config.h"
#include "utils/manage_memory/manage_memory.h"

#define GNUPLOT "gnuplot -persist"

Variable* predict(Variable* x, Layer* model) {
  Variable* y;
  y = Layer_call(model, x)[0];
  return y;
}

int main() {
  srand(0);
  Ndarray x_data, y_data;
  Ndarray_init_shape_rand_as_static(&x_data, 2, 100, 1);
  Ndarray_init_shape_as_static(&y_data, 2, 100, 1);
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
  Variable_init_as_static(&x, x_data, "x");
  Variable_init_as_static(&y, y_data, "y");
  x.isConst = TRUE;
  y.isConst = TRUE;

  // LinearL l1;
  // LinearL_init(&l1, 10, 0);
  // LinearL l2;
  // LinearL_init(&l2, 1, 0);
  // Layer model;
  // Layer_init(&model, 1, 1, 0, 2);
  // Layer_add_layer(&model, (Layer*)&l1);
  // Layer_add_layer(&model, (Layer*)&l2);

  TwoLayerNet model;
  TwoLayerNet_init(&model, 30, 1);

  int output_sizes[] = {5, 5, 1};
  MLP model2;
  MLP_init(&model2, 3, output_sizes);
  
  float lr = 0.05;
  int iters = 50000;

  Variable* y_pred;
  Variable* loss;

  for (int i = 0; i < iters; i++) {
    y_pred = predict(&x, (Layer*)&model2);
    loss = mse(&y, y_pred);

    Layer_cleargrads((Layer*)&model2);

    Variable_backward(loss, FALSE, TRUE);

    if (i == 0) {
      plot_dot_graph(loss, TRUE, TRUE, "loss_graph.png");
      // plot_dot_graph(x.p_grad, TRUE, TRUE, "xgrad_graph.png");
    }

    // for (int i = 0; i < ((Layer*)&model)->layer_num; i++) {
    //   for (int j = 0; j < ((Layer*)&model)->p_layers[i]->param_num; j++) {
    //     Ndarray param_data = *(((Layer*)&model)->p_layers[i]->p_params[j]->p_data);
    //     Ndarray param_grad = *(((Layer*)&model)->p_layers[i]->p_params[j]->p_grad->p_data);
    //      *(((Layer*)&model)->p_layers[i]->p_params[j]->p_data) = Ndarray_sub(param_data, Ndarray_constant_mul(param_grad, lr));
    //   }
    // }
    Layer_update_params((Layer*)&model2, lr);

    if (i % 1000 == 0) {
      Ndarray_print(loss->p_data);
      // printf("\033[%dA" ,1); //カーソルを1行だけ上に移動
    }
    
    // Variable_destroy(loss, TRUE);
    leak_detect_all_free();
  }

  for (int i = 0; i < 100; i++)
    fprintf(gp, "%f\t%f\n", x_data.array[i], predict(&x, (Layer*)&model2)->p_data->array[i]);

  fprintf(gp, "set terminal windows\n");

  fprintf(gp, "set output\n");

  if (pclose(gp) == EOF) {
    fprintf(stderr, "Error: cannot close \"%s\".\n", GNUPLOT);
    exit(2);
  }

  return 0;
}