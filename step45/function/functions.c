#include "functions.h"
#include "../utils/enable_backdrop/config.h"
#include <stdlib.h>
#include <stdio.h>

Variable** add_list(Variable* x, Variable* y) {
  Add* pf;
  pf = (Add*)malloc(sizeof(Add));
  Add_init(pf);
  Variable** ret = Function_call((Function*)pf, "", x, y);
  if (ENABLE_BACKDROP) {
    return ret;
  } else {
    free(pf);
    return ret;
  }
}

Variable* add(Variable* x, Variable* y) {
  Add* pf;
  pf = (Add*)malloc(sizeof(Add));
  Add_init(pf);
  Variable* ret =  Function_call((Function*)pf, "", x, y)[0];
  if (ENABLE_BACKDROP) {
    return ret;
  } else {
    free(pf);
    return ret;
  }
}

Variable* addLC(const float c, Variable* x) {
  Add* pf;
  pf = (Add*)malloc(sizeof(Add));
  Add_init(pf);
  Variable* ret = Function_call_with_Lconstant((Function*)pf, "", c, x)[0];
  if (ENABLE_BACKDROP) {
    return ret;
  } else {
    free(pf);
    return ret;
  }
}

Variable* addRC(Variable* x, const float c) {
  Add* pf;
  pf = (Add*)malloc(sizeof(Add));
  Add_init(pf);
  Variable* ret = Function_call_with_Rconstant((Function*)pf, "", x, c)[0];
  if (ENABLE_BACKDROP) {
    return ret;
  } else {
    free(pf);
    return ret;
  }
}

Variable* addN(const char* name, Variable* x, Variable* y) {
  Add* pf;
  pf = (Add*)malloc(sizeof(Add));
  Add_init(pf);
  Variable* ret = Function_call((Function*)pf, name, x, y)[0];
  if (ENABLE_BACKDROP) {
    return ret;
  } else {
    free(pf);
    return ret;
  }
}

Variable* addNLC(const char* name, const float c, Variable* x) {
  Add* pf;
  pf = (Add*)malloc(sizeof(Add));
  Add_init(pf);
  Variable* ret = Function_call_with_Lconstant((Function*)pf, name, c, x)[0];
  if (ENABLE_BACKDROP) {
    return ret;
  } else {
    free(pf);
    return ret;
  }
}

Variable* addNRC(const char* name, Variable* x, const float c) {
  Add* pf;
  pf = (Add*)malloc(sizeof(Add));
  Add_init(pf);
  Variable* ret = Function_call_with_Rconstant((Function*)pf, name, x, c)[0];
  if (ENABLE_BACKDROP) {
    return ret;
  } else {
    free(pf);
    return ret;
  }
}

Variable** divi_list(Variable* x, Variable* y) {
  Div* pf;
  pf = (Div*)malloc(sizeof(Div));
  Div_init(pf);
  Variable** ret = Function_call((Function*)pf, "", x, y);
  if (ENABLE_BACKDROP) {
    return ret;
  } else {
    free(pf);
    return ret;
  }
}

Variable* divi(Variable* x, Variable* y) {
  Div* pf;
  pf = (Div*)malloc(sizeof(Div));
  Div_init(pf);
  Variable* ret = Function_call((Function*)pf, "", x, y)[0];
  if (ENABLE_BACKDROP) {
    return ret;
  } else {
    free(pf);
    return ret;
  }
}

Variable* diviLC(const float c, Variable* x) {
  Div* pf;
  pf = (Div*)malloc(sizeof(Div));
  Div_init(pf);
  Variable* ret = Function_call_with_Lconstant((Function*)pf, "", c, x)[0];
  if (ENABLE_BACKDROP) {
    return ret;
  } else {
    free(pf);
    return ret;
  }
}

Variable* diviRC(Variable* x, const float c) {
  Div* pf;
  pf = (Div*)malloc(sizeof(Div));
  Div_init(pf);
  Variable* ret = Function_call_with_Rconstant((Function*)pf, "", x, c)[0];
  if (ENABLE_BACKDROP) {
    return ret;
  } else {
    free(pf);
    return ret;
  }
}

Variable* diviN(const char* name, Variable* x, Variable* y) {
  Div* pf;
  pf = (Div*)malloc(sizeof(Div));
  Div_init(pf);
  Variable* ret = Function_call((Function*)pf, name, x, y)[0];
  if (ENABLE_BACKDROP) {
    return ret;
  } else {
    free(pf);
    return ret;
  }
}

Variable* diviNLC(const char* name, const float c, Variable* x) {
  Div* pf;
  pf = (Div*)malloc(sizeof(Div));
  Div_init(pf);
  Variable* ret = Function_call_with_Lconstant((Function*)pf, name, c, x)[0];
  if (ENABLE_BACKDROP) {
    return ret;
  } else {
    free(pf);
    return ret;
  }
}

Variable* diviNRC(const char* name, Variable* x, const float c) {
  Div* pf;
  pf = (Div*)malloc(sizeof(Div));
  Div_init(pf);
  Variable* ret = Function_call_with_Rconstant((Function*)pf, name, x, c)[0];
  if (ENABLE_BACKDROP) {
    return ret;
  } else {
    free(pf);
    return ret;
  }
}

Variable** expo_list(Variable* x) {
  Exp* pf;
  pf = (Exp*)malloc(sizeof(Exp));
  Exp_init(pf);
  Variable** ret = Function_call((Function*)pf, "", x);
  if (ENABLE_BACKDROP) {
    return ret;
  } else {
    free(pf);
    return ret;
  }
}

Variable* expo(Variable* x) {
  Exp* pf;
  pf = (Exp*)malloc(sizeof(Exp));
  Exp_init(pf);
  Variable* ret = Function_call((Function*)pf, "", x)[0];
  if (ENABLE_BACKDROP) {
    return ret;
  } else {
    free(pf);
    return ret;
  }
}

Variable* expoN(const char* name, Variable* x) {
  Exp* pf;
  pf = (Exp*)malloc(sizeof(Exp));
  Exp_init(pf);
  Variable* ret = Function_call((Function*)pf, name, x)[0];
  if (ENABLE_BACKDROP) {
    return ret;
  } else {
    free(pf);
    return ret;
  }
}

Variable** ln_list(Variable* x) {
  Log* pf;
  pf = (Log*)malloc(sizeof(Log));
  Log_init(pf);
  Variable** ret = Function_call((Function*)pf, "", x);
  if (ENABLE_BACKDROP) {
    return ret;
  } else {
    free(pf);
    return ret;
  }
}

Variable* ln(Variable* x) {
  Log* pf;
  pf = (Log*)malloc(sizeof(Log));
  Log_init(pf);
  Variable* ret = Function_call((Function*)pf, "", x)[0];
  if (ENABLE_BACKDROP) {
    return ret;
  } else {
    free(pf);
    return ret;
  }
}

Variable* lnN(const char* name, Variable* x) {
  Log* pf;
  pf = (Log*)malloc(sizeof(Log));
  Log_init(pf);
  Variable* ret = Function_call((Function*)pf, name, x)[0];
  if (ENABLE_BACKDROP) {
    return ret;
  } else {
    free(pf);
    return ret;
  }
}

Variable** mul_list(Variable* x, Variable *y) {
  Mul* pf;
  pf = (Mul*)malloc(sizeof(Mul));
  Mul_init(pf);
  Variable** ret = Function_call((Function*)pf, "", x, y);
  if (ENABLE_BACKDROP) {
    return ret;
  } else {
    free(pf);
    return ret;
  }
}

Variable* mul(Variable* x, Variable *y) {
  Mul* pf;
  pf = (Mul*)malloc(sizeof(Mul));
  Mul_init(pf);
  Variable* ret = Function_call((Function*)pf, "", x, y)[0];
  if (ENABLE_BACKDROP) {
    return ret;
  } else {
    free(pf);
    return ret;
  }
}

Variable* mulLC(const float c, Variable *x) {
  Mul* pf;
  pf = (Mul*)malloc(sizeof(Mul));
  Mul_init(pf);
  Variable* ret = Function_call_with_Lconstant((Function*)pf, "", c, x)[0];
  if (ENABLE_BACKDROP) {
    return ret;
  } else {
    free(pf);
    return ret;
  }
}

Variable* mulRC(Variable* x, const float c) {
  Mul* pf;
  pf = (Mul*)malloc(sizeof(Mul));
  Mul_init(pf);
  Variable* ret = Function_call_with_Rconstant((Function*)pf, "", x, c)[0];
  if (ENABLE_BACKDROP) {
    return ret;
  } else {
    free(pf);
    return ret;
  }
}

Variable* mulN(const char* name, Variable* x, Variable *y) {
  Mul* pf;
  pf = (Mul*)malloc(sizeof(Mul));
  Mul_init(pf);
  Variable* ret = Function_call((Function*)pf, name, x, y)[0];
  if (ENABLE_BACKDROP) {
    return ret;
  } else {
    free(pf);
    return ret;
  }
}

Variable* mulNLC(const char* name, const float c, Variable *x) {
  Mul* pf;
  pf = (Mul*)malloc(sizeof(Mul));
  Mul_init(pf);
  Variable* ret = Function_call_with_Lconstant((Function*)pf, name, c, x)[0];
  if (ENABLE_BACKDROP) {
    return ret;
  } else {
    free(pf);
    return ret;
  }
}

Variable* mulNRC(const char* name, Variable* x, const float c) {
  Mul* pf;
  pf = (Mul*)malloc(sizeof(Mul));
  Mul_init(pf);
  Variable* ret = Function_call_with_Rconstant((Function*)pf, name, x, c)[0];
  if (ENABLE_BACKDROP) {
    return ret;
  } else {
    free(pf);
    return ret;
  }
}

Variable** neg_list(Variable* x) {
  Neg* pf;
  pf = (Neg*)malloc(sizeof(Neg));
  Neg_init(pf);
  Variable** ret = Function_call((Function*)pf, "", x);
  if (ENABLE_BACKDROP) {
    return ret;
  } else {
    free(pf);
    return ret;
  }
}

Variable* neg(Variable* x) {
  Neg* pf;
  pf = (Neg*)malloc(sizeof(Neg));
  Neg_init(pf);
  Variable* ret = Function_call((Function*)pf, "", x)[0];
  if (ENABLE_BACKDROP) {
    return ret;
  } else {
    free(pf);
    return ret;
  }
}

Variable* negN(const char* name, Variable* x) {
  Neg* pf;
  pf = (Neg*)malloc(sizeof(Neg));
  Neg_init(pf);
  Variable* ret = Function_call((Function*)pf, name, x)[0];
  if (ENABLE_BACKDROP) {
    return ret;
  } else {
    free(pf);
    return ret;
  }
}

Variable** powe_list(Variable* x, Variable* y) {
  Pow* pf;
  pf = (Pow*)malloc(sizeof(Pow));
  Pow_init(pf);
  Variable** ret = Function_call((Function*)pf, "", x, y);
  if (ENABLE_BACKDROP) {
    return ret;
  } else {
    free(pf);
    return ret;
  }
}

Variable* powe(Variable* x, Variable* y) {
  Pow* pf;
  pf = (Pow*)malloc(sizeof(Pow));
  Pow_init(pf);
  Variable* ret = Function_call((Function*)pf, "", x, y)[0];
  if (ENABLE_BACKDROP) {
    return ret;
  } else {
    free(pf);
    return ret;
  }
}

Variable* poweLC(const float c, Variable* x) {
  Pow* pf;
  pf = (Pow*)malloc(sizeof(Pow));
  Pow_init(pf);
  Variable* ret = Function_call_with_Lconstant((Function*)pf, "", c, x)[0];
  if (ENABLE_BACKDROP) {
    return ret;
  } else {
    free(pf);
    return ret;
  }
}

Variable* poweRC(Variable* x, const float c) {
  Pow* pf;
  pf = (Pow*)malloc(sizeof(Pow));
  Pow_init(pf);
  Variable* ret = Function_call_with_Rconstant((Function*)pf, "", x, c)[0];
  if (ENABLE_BACKDROP) {
    return ret;
  } else {
    free(pf);
    return ret;
  }
}

Variable* poweN(const char* name, Variable* x, Variable* y) {
  Pow* pf;
  pf = (Pow*)malloc(sizeof(Pow));
  Pow_init(pf);
  Variable* ret = Function_call((Function*)pf, name, x, y)[0];
  if (ENABLE_BACKDROP) {
    return ret;
  } else {
    free(pf);
    return ret;
  }
}

Variable* poweNLC(const char* name, const float c, Variable* x) {
  Pow* pf;
  pf = (Pow*)malloc(sizeof(Pow));
  Pow_init(pf);
  Variable* ret = Function_call_with_Lconstant((Function*)pf, name, c, x)[0];
  if (ENABLE_BACKDROP) {
    return ret;
  } else {
    free(pf);
    return ret;
  }
}

Variable* poweNRC(const char* name, Variable* x, const float c) {
  Pow* pf;
  pf = (Pow*)malloc(sizeof(Pow));
  Pow_init(pf);
  Variable* ret = Function_call_with_Rconstant((Function*)pf, name, x, c)[0];
  if (ENABLE_BACKDROP) {
    return ret;
  } else {
    free(pf);
    return ret;
  }
}

Variable** sine_list(Variable* x) {
  Sin* pf;
  pf = (Sin*)malloc(sizeof(Sin));
  Sin_init(pf);
  Variable** ret = Function_call((Function*)pf, "", x);
  if (ENABLE_BACKDROP) {
    return ret;
  } else {
    free(pf);
    return ret;
  }
}

Variable* sine(Variable* x) {
  Sin* pf;
  pf = (Sin*)malloc(sizeof(Sin));
  Sin_init(pf);
  Variable* ret = Function_call((Function*)pf, "", x)[0];
  if (ENABLE_BACKDROP) {
    return ret;
  } else {
    free(pf);
    return ret;
  }
}

Variable* sineN(const char* name, Variable* x) {
  Sin* pf;
  pf = (Sin*)malloc(sizeof(Sin));
  Sin_init(pf);
  Variable* ret = Function_call((Function*)pf, name, x)[0];
  if (ENABLE_BACKDROP) {
    return ret;
  } else {
    free(pf);
    return ret;
  }
}

Variable** cosi_list(Variable* x) {
  Cos* pf;
  pf = (Cos*)malloc(sizeof(Cos));
  Cos_init(pf);
  Variable** ret = Function_call((Function*)pf, "", x);
  if (ENABLE_BACKDROP) {
    return ret;
  } else {
    free(pf);
    return ret;
  }
}

Variable* cosi(Variable* x) {
  Cos* pf;
  pf = (Cos*)malloc(sizeof(Cos));
  Cos_init(pf);
  Variable* ret = Function_call((Function*)pf, "", x)[0];
  if (ENABLE_BACKDROP) {
    return ret;
  } else {
    free(pf);
    return ret;
  }
}

Variable* cosiN(const char* name, Variable* x) {
  Cos* pf;
  pf = (Cos*)malloc(sizeof(Cos));
  Cos_init(pf);
  Variable* ret = Function_call((Function*)pf, name, x)[0];
  if (ENABLE_BACKDROP) {
    return ret;
  } else {
    free(pf);
    return ret;
  }
}

Variable** square_list(Variable* x) {
  Square* pf;
  pf = (Square*)malloc(sizeof(Square));
  Square_init(pf);
  Variable** ret = Function_call((Function*)pf, "", x);
  if (ENABLE_BACKDROP) {
    return ret;
  } else {
    free(pf);
    return ret;
  }
}

Variable* square(Variable* x) {
  Square* pf;
  pf = (Square*)malloc(sizeof(Square));
  Square_init(pf);
  Variable* ret = Function_call((Function*)pf, "", x)[0];
  if (ENABLE_BACKDROP) {
    return ret;
  } else {
    free(pf);
    return ret;
  }
}

Variable* squareN(const char* name, Variable* x) {
  Square* pf;
  pf = (Square*)malloc(sizeof(Square));
  Square_init(pf);
  Variable* ret = Function_call((Function*)pf, name, x)[0];
  if (ENABLE_BACKDROP) {
    return ret;
  } else {
    free(pf);
    return ret;
  }
}

Variable** sub_list(Variable* x, Variable* y) {
  Sub* pf;
  pf = (Sub*)malloc(sizeof(Sub));
  Sub_init(pf);
  Variable** ret = Function_call((Function*)pf, "", x, y);
  if (ENABLE_BACKDROP) {
    return ret;
  } else {
    free(pf);
    return ret;
  }
}

Variable* sub(Variable* x, Variable* y) {
  Sub* pf;
  pf = (Sub*)malloc(sizeof(Sub));
  Sub_init(pf);
  Variable* ret = Function_call((Function*)pf, "", x, y)[0];
  if (ENABLE_BACKDROP) {
    return ret;
  } else {
    free(pf);
    return ret;
  }
}

Variable* subLC(const float c, Variable* x) {
  Sub* pf;
  pf = (Sub*)malloc(sizeof(Sub));
  Sub_init(pf);
  Variable* ret = Function_call_with_Lconstant((Function*)pf, "", c, x)[0];
  if (ENABLE_BACKDROP) {
    return ret;
  } else {
    free(pf);
    return ret;
  }
}

Variable* subRC(Variable* x, const float c) {
  Sub* pf;
  pf = (Sub*)malloc(sizeof(Sub));
  Sub_init(pf);
  Variable* ret = Function_call_with_Rconstant((Function*)pf, "", x, c)[0];
  if (ENABLE_BACKDROP) {
    return ret;
  } else {
    free(pf);
    return ret;
  }
}

Variable* subN(const char* name, Variable* x, Variable* y) {
  Sub* pf;
  pf = (Sub*)malloc(sizeof(Sub));
  Sub_init(pf);
  Variable* ret = Function_call((Function*)pf, name, x, y)[0];
  if (ENABLE_BACKDROP) {
    return ret;
  } else {
    free(pf);
    return ret;
  }
}

Variable* subNLC(const char* name, const float c, Variable* x) {
  Sub* pf;
  pf = (Sub*)malloc(sizeof(Sub));
  Sub_init(pf);
  Variable* ret = Function_call_with_Lconstant((Function*)pf, name, c, x)[0];
  if (ENABLE_BACKDROP) {
    return ret;
  } else {
    free(pf);
    return ret;
  }
}

Variable* subNRC(const char* name, Variable* x, const float c) {
  Sub* pf;
  pf = (Sub*)malloc(sizeof(Sub));
  Sub_init(pf);
  Variable* ret = Function_call_with_Rconstant((Function*)pf, name, x, c)[0];
  if (ENABLE_BACKDROP) {
    return ret;
  } else {
    free(pf);
    return ret;
  }
}

Variable** tanhy_list(Variable* x) {
  Tanh* pf;
  pf = (Tanh*)malloc(sizeof(Tanh));
  Tanh_init(pf);
  Variable** ret = Function_call((Function*)pf, "", x);
  if (ENABLE_BACKDROP) {
    return ret;
  } else {
    free(pf);
    return ret;
  }
}

Variable* tanhy(Variable* x) {
  Tanh* pf;
  pf = (Tanh*)malloc(sizeof(Tanh));
  Tanh_init(pf);
  Variable* ret = Function_call((Function*)pf, "", x)[0];
  if (ENABLE_BACKDROP) {
    return ret;
  } else {
    free(pf);
    return ret;
  }
}

Variable* tanhyN(const char* name, Variable* x) {
  Tanh* pf;
  pf = (Tanh*)malloc(sizeof(Tanh));
  Tanh_init(pf);
  Variable* ret = Function_call((Function*)pf, name, x)[0];
  if (ENABLE_BACKDROP) {
    return ret;
  } else {
    free(pf);
    return ret;
  }
}

Variable** reshape_list(Variable* x, const int dim, const int* shape) {
  Reshape* pf;
  pf = (Reshape*)malloc(sizeof(Reshape));
  Reshape_init(pf, dim, shape);
  Variable** ret = Function_call((Function*)pf, "", x);
  if (ENABLE_BACKDROP) {
    return ret;
  } else {
    free(pf);
    return ret;
  }
}

Variable* reshape(Variable* x, const int dim, const int* shape) {
  Reshape* pf;
  pf = (Reshape*)malloc(sizeof(Reshape));
  Reshape_init(pf, dim, shape);
  Variable* ret = Function_call((Function*)pf, "", x)[0];
  if (ENABLE_BACKDROP) {
    return ret;
  } else {
    free(pf);
    return ret;
  }
}

Variable* reshapeN(const char* name, Variable* x, const int dim, const int* shape) {
  Reshape* pf;
  pf = (Reshape*)malloc(sizeof(Reshape));
  Reshape_init(pf, dim, shape);
  Variable* ret = Function_call((Function*)pf, name, x)[0];
  if (ENABLE_BACKDROP) {
    return ret;
  } else {
    free(pf);
    return ret;
  }
}

Variable** transpose2d_list(Variable* x) {
  Transpose2d* pf;
  pf = (Transpose2d*)malloc(sizeof(Transpose2d));
  Transpose2d_init(pf);
  Variable** ret = Function_call((Function*)pf, "", x);
  if (ENABLE_BACKDROP) {
    return ret;
  } else {
    free(pf);
    return ret;
  }
}

Variable* transpose2d(Variable* x) {
  Transpose2d* pf;
  pf = (Transpose2d*)malloc(sizeof(Transpose2d));
  Transpose2d_init(pf);
  Variable* ret = Function_call((Function*)pf, "", x)[0];
  if (ENABLE_BACKDROP) {
    return ret;
  } else {
    free(pf);
    return ret;
  }
}

Variable* transpose2dN(const char* name, Variable* x) {
  Transpose2d* pf;
  pf = (Transpose2d*)malloc(sizeof(Transpose2d));
  Transpose2d_init(pf);
  Variable* ret = Function_call((Function*)pf, name, x)[0];
  if (ENABLE_BACKDROP) {
    return ret;
  } else {
    free(pf);
    return ret;
  }
}

Variable** transpose_list(Variable* x, const int dim, const int* axes) {
  Transpose* pf;
  pf = (Transpose*)malloc(sizeof(Transpose));
  Transpose_init(pf, dim, axes);
  Variable** ret = Function_call((Function*)pf, "", x);
  if (ENABLE_BACKDROP) {
    return ret;
  } else {
    free(pf);
    return ret;
  }
}

Variable* transpose(Variable* x, const int dim, const int* axes) {
  Transpose* pf;
  pf = (Transpose*)malloc(sizeof(Transpose));
  Transpose_init(pf, dim, axes);
  Variable* ret = Function_call((Function*)pf, "", x)[0];
  if (ENABLE_BACKDROP) {
    return ret;
  } else {
    free(pf);
    return ret;
  }
}

Variable* transposeN(const char* name, Variable* x, const int dim, const int* axes) {
  Transpose* pf;
  pf = (Transpose*)malloc(sizeof(Transpose));
  Transpose_init(pf, dim, axes);
  Variable* ret = Function_call((Function*)pf, name, x)[0];
  if (ENABLE_BACKDROP) {
    return ret;
  } else {
    free(pf);
    return ret;
  }
}

Variable** sum_list(Variable* x, const int axis, const bool keepdims) {
  Sum* pf;
  pf = (Sum*)malloc(sizeof(Sum));
  Sum_init(pf, axis, keepdims);
  Variable** ret = Function_call((Function*)pf, "", x);
  if (ENABLE_BACKDROP) {
    return ret;
  } else {
    free(pf);
    return ret;
  }
}

Variable* sum(Variable* x, const int axis, const bool keepdims) {
  Sum* pf;
  pf = (Sum*)malloc(sizeof(Sum));
  Sum_init(pf, axis, keepdims);
  Variable* ret = Function_call((Function*)pf, "", x)[0];
  if (ENABLE_BACKDROP) {
    return ret;
  } else {
    free(pf);
    return ret;
  }
}

Variable* sumN(const char* name, Variable* x, const int axis, const bool keepdims) {
  Sum* pf;
  pf = (Sum*)malloc(sizeof(Sum));
  Sum_init(pf, axis, keepdims);
  Variable* ret = Function_call((Function*)pf, name, x)[0];
  if (ENABLE_BACKDROP) {
    return ret;
  } else {
    free(pf);
    return ret;
  }
}

Variable** broadcast_to_list(Variable* x, const int dim, const int* shape) {
  BroadcastTo* pf;
  pf = (BroadcastTo*)malloc(sizeof(BroadcastTo));
  BroadcastTo_init(pf, dim, shape);
  Variable** ret = Function_call((Function*)pf, "", x);
  if (ENABLE_BACKDROP) {
    return ret;
  } else {
    free(pf);
    return ret;
  }
}

Variable* broadcast_to(Variable* x, const int dim, const int* shape) {
  BroadcastTo* pf;
  pf = (BroadcastTo*)malloc(sizeof(BroadcastTo));
  BroadcastTo_init(pf, dim, shape);
  Variable* ret = Function_call((Function*)pf, "", x)[0];
  if (ENABLE_BACKDROP) {
    return ret;
  } else {
    free(pf);
    return ret;
  }
}

Variable* broadcast_toN(const char* name, Variable* x, const int dim, const int* shape) {
  BroadcastTo* pf;
  pf = (BroadcastTo*)malloc(sizeof(BroadcastTo));
  BroadcastTo_init(pf, dim, shape);
  Variable* ret = Function_call((Function*)pf, name, x)[0];
  if (ENABLE_BACKDROP) {
    return ret;
  } else {
    free(pf);
    return ret;
  }
}

Variable** sum_to_list(Variable* x, const int dim, const int* shape) {
  SumTo* pf;
  pf = (SumTo*)malloc(sizeof(SumTo));
  SumTo_init(pf, dim, shape);
  Variable** ret = Function_call((Function*)pf, "", x);
  if (ENABLE_BACKDROP) {
    return ret;
  } else {
    free(pf);
    return ret;
  }
}

Variable* sum_to(Variable* x, const int dim, const int* shape) {
  SumTo* pf;
  pf = (SumTo*)malloc(sizeof(SumTo));
  SumTo_init(pf, dim, shape);
  Variable* ret = Function_call((Function*)pf, "", x)[0];
  if (ENABLE_BACKDROP) {
    return ret;
  } else {
    free(pf);
    return ret;
  }
}

Variable* sum_toN(const char* name, Variable* x, const int dim, const int* shape) {
  SumTo* pf;
  pf = (SumTo*)malloc(sizeof(SumTo));
  SumTo_init(pf, dim, shape);
  Variable* ret = Function_call((Function*)pf, name, x)[0];
  if (ENABLE_BACKDROP) {
    return ret;
  } else {
    free(pf);
    return ret;
  }
}

Variable** matmul_list(Variable* x, Variable* W) {
  MatMul* pf;
  pf = (MatMul*)malloc(sizeof(MatMul));
  MatMul_init(pf);
  Variable** ret = Function_call((Function*)pf, "", x, W);
  if (ENABLE_BACKDROP) {
    return ret;
  } else {
    free(pf);
    return ret;
  }
}

Variable* matmul(Variable* x, Variable* W) {
  MatMul* pf;
  pf = (MatMul*)malloc(sizeof(MatMul));
  MatMul_init(pf);
  Variable* ret = Function_call((Function*)pf, "", x, W)[0];
  if (ENABLE_BACKDROP) {
    return ret;
  } else {
    free(pf);
    return ret;
  }
}

Variable* matmulN(const char* name, Variable* x, Variable* W) {
  MatMul* pf;
  pf = (MatMul*)malloc(sizeof(MatMul));
  MatMul_init(pf);
  Variable* ret = Function_call((Function*)pf, name, x, W)[0];
  if (ENABLE_BACKDROP) {
    return ret;
  } else {
    free(pf);
    return ret;
  }
}

Variable** mse_list(Variable* x0, Variable* x1) {
  MSE* pf;
  pf = (MSE*)malloc(sizeof(MSE));
  MSE_init(pf);
  Variable** ret = Function_call((Function*)pf, "", x0, x1);
  if (ENABLE_BACKDROP) {
    return ret;
  } else {
    free(pf);
    return ret;
  }
}

Variable* mse(Variable* x0, Variable* x1) {
  MSE* pf;
  pf = (MSE*)malloc(sizeof(MSE));
  MSE_init(pf);
  Variable* ret = Function_call((Function*)pf, "", x0, x1)[0];
  if (ENABLE_BACKDROP) {
    return ret;
  } else {
    free(pf);
    return ret;
  }
}

Variable* mseN(const char* name, Variable* x0, Variable* x1) {
  MSE* pf;
  pf = (MSE*)malloc(sizeof(MSE));
  MSE_init(pf);
  Variable* ret = Function_call((Function*)pf, name, x0, x1)[0];
  if (ENABLE_BACKDROP) {
    return ret;
  } else {
    free(pf);
    return ret;
  }
}

Variable** linear_list(Variable* x, Variable* W, Variable* b) {
  Linear* pf;
  pf = (Linear*)malloc(sizeof(Linear));
  Linear_init(pf);
  Variable** ret = Function_call((Function*)pf, "", x, W, b);
  if (ENABLE_BACKDROP) {
    return ret;
  } else {
    free(pf);
    return ret;
  }
}

Variable* linear(Variable* x, Variable* W, Variable* b) {
  Linear* pf;
  pf = (Linear*)malloc(sizeof(Linear));
  Linear_init(pf);
  Variable* ret = Function_call((Function*)pf, "", x, W, b)[0];
  if (ENABLE_BACKDROP) {
    return ret;
  } else {
    free(pf);
    return ret;
  }
}

Variable* linearN(const char* name, Variable* x, Variable* W, Variable* b) {
  Linear* pf;
  pf = (Linear*)malloc(sizeof(Linear));
  Linear_init(pf);
  Variable* ret = Function_call((Function*)pf, name, x, W, b)[0];
}

Variable** sigmoid_list(Variable* x) {
  Sigmoid* pf;
  pf = (Sigmoid*)malloc(sizeof(Sigmoid));
  Sigmoid_init(pf);
  Variable** ret = Function_call((Function*)pf, "", x);
  if (ENABLE_BACKDROP) {
    return ret;
  } else {
    free(pf);
    return ret;
  }
}

Variable* sigmoid(Variable* x) {
  Sigmoid* pf;
  pf = (Sigmoid*)malloc(sizeof(Sigmoid));
  Sigmoid_init(pf);
  Variable* ret = Function_call((Function*)pf, "", x)[0];
  if (ENABLE_BACKDROP) {
    return ret;
  } else {
    free(pf);
    return ret;
  }
}

Variable* sigmoidN(const char* name, Variable* x) {
  Sigmoid* pf;
  pf = (Sigmoid*)malloc(sizeof(Sigmoid));
  Sigmoid_init(pf);
  Variable* ret = Function_call((Function*)pf, name, x)[0];
  if (ENABLE_BACKDROP) {
    return ret;
  } else {
    free(pf);
    return ret;
  }
}

Variable* map(Variable* x, double (*func)(double)) {
  Variable* y;
  y = (Variable*)malloc(sizeof(Variable));
  Variable_init(y, Ndarray_map(*(x->p_data), func), "");
  return y;
}

Variable* mapN(const char* name, Variable* x, double (*func)(double)) {
  Variable* y;
  y = (Variable*)malloc(sizeof(Variable));
  Variable_init(y, Ndarray_map(*(x->p_data), func), name);
  return y;
}