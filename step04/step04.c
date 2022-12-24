#include <stdio.h>
#include <math.h>
#include "variable.h"
#include "square.h"
#include "function.h"
#include "exp.h"

float numerical_diff(Function* f, Variable x) {
  float eps = pow(10, -4);
  Variable x0;
  Variable_init(&x0, x.data - eps);
  Variable x1;
  Variable_init(&x1, x.data + eps);
  Variable y0 = Function_call(f, x0);
  Variable y1 = Function_call(f, x1);
  return (y1.data - y0.data) / (2 * eps);
}

typedef struct abc {
  Function function;
} ABC;

static float abc_forward(Function* const p_self, const float x) {
  Variable input;
  Variable_init(&input, x);
  Square A;
  Square_init(&A);
  Exp B;
  Exp_init(&B);
  Square C;
  Square_init(&C);

  Variable a = Function_call((Function*)&A, input);
  Variable b = Function_call((Function*)&B, a);
  Variable y = Function_call((Function*)&C, b);

  return y.data;
}

static const FunctionMethods ABC_METHODS = {
  abc_forward
};

void ABC_init(ABC* p_self) {
  ((Function*)p_self)->p_methods = &ABC_METHODS;
}

int main() {
  Variable x;
  Variable_init(&x, 0.5);

  ABC f;
  ABC_init(&f);

  float dy = numerical_diff((Function*)&f, x);

  printf("%.10f\n", dy);
  return 0;
}