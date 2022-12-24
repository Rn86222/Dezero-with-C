#include "square.h"
#include "function.h"
#include "math.h"

static float square_forward(Function* const p_self, const float x) {
  return pow(x, 2);
}

static const FunctionMethods SQUARE_METHODS = {
  square_forward
};

void Square_init(Square* p_self) {
  ((Function*)p_self)->p_methods = &SQUARE_METHODS;
}