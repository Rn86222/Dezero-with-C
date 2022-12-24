#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "variable/variable.h"
#include "function/function.h"
#include "function/functions.h"
#include "ndarray/ndarray.h"
#include "macro/constant.h"
#include "dot/dot.h"

#define GNUPLOT "gnuplot -persist"
#define MAX_LOOP 3

int main() {
  Variable x;
  Ndarray x_data;
  int x_data_shape[1] = {101};
  Ndarray_init(&x_data, 1, x_data_shape);
  for (int i = 0; i <= 100; i++) {
    x_data.array[i] = (float)i / 100 * 2 * M_PI;
  }
  Variable_init(&x, x_data, "x");

  // Variable y;
  // Ndarray y_data;
  // int y_data_shape[1] = {1};
  // Ndarray_init(&y_data, 1, y_data_shape);
  // y_data.array[0] = 1.0;
  // Variable_init(&y, y_data, "y");

  Variable** z;
  z = (Variable**)malloc(1 * sizeof(Variable*));
  z[0] = sineN("z", &x);

  FILE *gp;
 
  if ((gp = popen(GNUPLOT, "w")) == NULL) {
    fprintf(stderr, "Error: cannot open \"%s\".\n", GNUPLOT);
    exit(1);
  }

  fprintf(gp, "set terminal png\n");
  fprintf(gp, "\n");
  fprintf(gp, "set out 'graph.png'\n");
  fprintf(gp, "set xrange [%f:%f]\n", 0.0, 2 * M_PI);
  fprintf(gp, "set yrange [-1.2:1.2]\n");
  fprintf(gp, "plot '-' with lines title \"y=sin(x)\", '-' with lines title \"y\'\", '-' with lines title \"y\'\'\", '-' with lines title \"y\'\'\'\"\n");
  for (int i = 0; i <= 100; i++) {
    fprintf(gp, "%f\t%f\n", x.p_data->array[i], z[0]->p_data->array[i]);
  }
  Variable_backward(z[0], FALSE);
  for (int i = 0; i < MAX_LOOP; i++) {
    fprintf(gp, "e\n");
    
    for (int j = 0; j <= 100; j++) {
      fprintf(gp, "%f\t%f\n", x.p_data->array[j], x.p_grad->p_data->array[j]);
    }
    Variable_cleargrad(&x);
    Variable_backward(x.p_grad, FALSE);
  }
 
  fprintf(gp, "set terminal windows\n");

  fprintf(gp, "set output\n");


  if (pclose(gp) == EOF) {
    fprintf(stderr, "Error: cannot close \"%s\".\n", GNUPLOT);
    exit(2);
  }
  // Variable_backward(z[0], FALSE);
  // z[0] = squareN("z", &x);
  // z[0] = mulN("z", addLC(1.0, mul(square(add(addLC(1.0, &x), &y)), add(add(subLC(19.0, mulLC(14.0, &x)), sub(mulLC(3.0, square(&x)), mulLC(14.0, &y))), add(mulLC(6.0, mul(&x, &y)), mulLC(3.0, square(&y)))))),
  //                  addLC(30.0, mul(square(sub(mulLC(2.0, &x), mulLC(3.0, &y))), add(add(subLC(18.0, mulLC(32.0, &x)), add(mulLC(12.0, square(&x)), mulLC(48.0, &y))), sub(mulLC(27.0, square(&y)), mulLC(36.0, mul(&x, &y)))))));


  // Variable_backward(z[0], FALSE);
  
  // plot_dot_graph(z[0], FALSE, FALSE, "graph.png");
  // Variable_print(x.p_grad);

  // Variable_cleargrad(&x);

  // plot_dot_graph(x.p_grad, FALSE, FALSE, "graph2.png");
  // Variable_backward(x.p_grad, FALSE);
  // Variable_print(x.p_grad);
  // Variable_print(z[0]);

  return 0;
}