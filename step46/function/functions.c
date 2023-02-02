#include "functions.h"
#include "../utils/manage_memory/manage_memory.h"
#include <stdlib.h>

Variable** add_list(Variable* x, Variable* y) {
  Add* pf;
  pf = (Add*)mymalloc(sizeof(Add));
  Add_init(pf);
  return Function_call((Function*)pf, "", x, y);
}

Variable* add(Variable* x, Variable* y) {
  Add* pf;
  pf = (Add*)mymalloc(sizeof(Add));
  Add_init(pf);
  return Function_call((Function*)pf, "", x, y)[0];
}

Variable* addLC(const float c, Variable* x) {
  Add* pf;
  pf = (Add*)mymalloc(sizeof(Add));
  Add_init(pf);
  return Function_call_with_Lconstant((Function*)pf, "", c, x)[0];
}

Variable* addRC(Variable* x, const float c) {
  Add* pf;
  pf = (Add*)mymalloc(sizeof(Add));
  Add_init(pf);
  return Function_call_with_Rconstant((Function*)pf, "", x, c)[0];
}

Variable* addN(const char* name, Variable* x, Variable* y) {
  Add* pf;
  pf = (Add*)mymalloc(sizeof(Add));
  Add_init(pf);
  return Function_call((Function*)pf, name, x, y)[0];
}

Variable* addNLC(const char* name, const float c, Variable* x) {
  Add* pf;
  pf = (Add*)mymalloc(sizeof(Add));
  Add_init(pf);
  return Function_call_with_Lconstant((Function*)pf, name, c, x)[0];
}

Variable* addNRC(const char* name, Variable* x, const float c) {
  Add* pf;
  pf = (Add*)mymalloc(sizeof(Add));
  Add_init(pf);
  return Function_call_with_Rconstant((Function*)pf, name, x, c)[0];
}

Variable** divi_list(Variable* x, Variable* y) {
  Div* pf;
  pf = (Div*)mymalloc(sizeof(Div));
  Div_init(pf);
  return Function_call((Function*)pf, "", x, y);
}

Variable* divi(Variable* x, Variable* y) {
  Div* pf;
  pf = (Div*)mymalloc(sizeof(Div));
  Div_init(pf);
  return Function_call((Function*)pf, "", x, y)[0];
}

Variable* diviLC(const float c, Variable* x) {
  Div* pf;
  pf = (Div*)mymalloc(sizeof(Div));
  Div_init(pf);
  return Function_call_with_Lconstant((Function*)pf, "", c, x)[0];
}

Variable* diviRC(Variable* x, const float c) {
  Div* pf;
  pf = (Div*)mymalloc(sizeof(Div));
  Div_init(pf);
  return Function_call_with_Rconstant((Function*)pf, "", x, c)[0];
}

Variable* diviN(const char* name, Variable* x, Variable* y) {
  Div* pf;
  pf = (Div*)mymalloc(sizeof(Div));
  Div_init(pf);
  return Function_call((Function*)pf, name, x, y)[0];
}

Variable* diviNLC(const char* name, const float c, Variable* x) {
  Div* pf;
  pf = (Div*)mymalloc(sizeof(Div));
  Div_init(pf);
  return Function_call_with_Lconstant((Function*)pf, name, c, x)[0];
}

Variable* diviNRC(const char* name, Variable* x, const float c) {
  Div* pf;
  pf = (Div*)mymalloc(sizeof(Div));
  Div_init(pf);
  return Function_call_with_Rconstant((Function*)pf, name, x, c)[0];
}

Variable** expo_list(Variable* x) {
  Exp* pf;
  pf = (Exp*)mymalloc(sizeof(Exp));
  Exp_init(pf);
  return Function_call((Function*)pf, "", x);
}

Variable* expo(Variable* x) {
  Exp* pf;
  pf = (Exp*)mymalloc(sizeof(Exp));
  Exp_init(pf);
  return Function_call((Function*)pf, "", x)[0];
}

Variable* expoN(const char* name, Variable* x) {
  Exp* pf;
  pf = (Exp*)mymalloc(sizeof(Exp));
  Exp_init(pf);
  return Function_call((Function*)pf, name, x)[0];
}

Variable** ln_list(Variable* x) {
  Log* pf;
  pf = (Log*)mymalloc(sizeof(Log));
  Log_init(pf);
  return Function_call((Function*)pf, "", x);
}

Variable* ln(Variable* x) {
  Log* pf;
  pf = (Log*)mymalloc(sizeof(Log));
  Log_init(pf);
  return Function_call((Function*)pf, "", x)[0];
}

Variable* lnN(const char* name, Variable* x) {
  Log* pf;
  pf = (Log*)mymalloc(sizeof(Log));
  Log_init(pf);
  return Function_call((Function*)pf, name, x)[0];
}

Variable** mul_list(Variable* x, Variable *y) {
  Mul* pf;
  pf = (Mul*)mymalloc(sizeof(Mul));
  Mul_init(pf);
  return Function_call((Function*)pf, "", x, y);
}

Variable* mul(Variable* x, Variable *y) {
  Mul* pf;
  pf = (Mul*)mymalloc(sizeof(Mul));
  Mul_init(pf);
  return Function_call((Function*)pf, "", x, y)[0];
}

Variable* mulLC(const float c, Variable *x) {
  Mul* pf;
  pf = (Mul*)mymalloc(sizeof(Mul));
  Mul_init(pf);
  return Function_call_with_Lconstant((Function*)pf, "", c, x)[0];
}

Variable* mulRC(Variable* x, const float c) {
  Mul* pf;
  pf = (Mul*)mymalloc(sizeof(Mul));
  Mul_init(pf);
  return Function_call_with_Rconstant((Function*)pf, "", x, c)[0];
}

Variable* mulN(const char* name, Variable* x, Variable *y) {
  Mul* pf;
  pf = (Mul*)mymalloc(sizeof(Mul));
  Mul_init(pf);
  return Function_call((Function*)pf, name, x, y)[0];
}

Variable* mulNLC(const char* name, const float c, Variable *x) {
  Mul* pf;
  pf = (Mul*)mymalloc(sizeof(Mul));
  Mul_init(pf);
  return Function_call_with_Lconstant((Function*)pf, name, c, x)[0];
}

Variable* mulNRC(const char* name, Variable* x, const float c) {
  Mul* pf;
  pf = (Mul*)mymalloc(sizeof(Mul));
  Mul_init(pf);
  return Function_call_with_Rconstant((Function*)pf, name, x, c)[0];
}

Variable** neg_list(Variable* x) {
  Neg* pf;
  pf = (Neg*)mymalloc(sizeof(Neg));
  Neg_init(pf);
  return Function_call((Function*)pf, "", x);
}

Variable* neg(Variable* x) {
  Neg* pf;
  pf = (Neg*)mymalloc(sizeof(Neg));
  Neg_init(pf);
  return Function_call((Function*)pf, "", x)[0];
}

Variable* negN(const char* name, Variable* x) {
  Neg* pf;
  pf = (Neg*)mymalloc(sizeof(Neg));
  Neg_init(pf);
  return Function_call((Function*)pf, name, x)[0];
}

Variable** powe_list(Variable* x, Variable* y) {
  Pow* pf;
  pf = (Pow*)mymalloc(sizeof(Pow));
  Pow_init(pf);
  return Function_call((Function*)pf, "", x, y);
}

Variable* powe(Variable* x, Variable* y) {
  Pow* pf;
  pf = (Pow*)mymalloc(sizeof(Pow));
  Pow_init(pf);
  return Function_call((Function*)pf, "", x, y)[0];
}

Variable* poweLC(const float c, Variable* x) {
  Pow* pf;
  pf = (Pow*)mymalloc(sizeof(Pow));
  Pow_init(pf);
  return Function_call_with_Lconstant((Function*)pf, "", c, x)[0];
}

Variable* poweRC(Variable* x, const float c) {
  Pow* pf;
  pf = (Pow*)mymalloc(sizeof(Pow));
  Pow_init(pf);
  return Function_call_with_Rconstant((Function*)pf, "", x, c)[0];
}

Variable* poweN(const char* name, Variable* x, Variable* y) {
  Pow* pf;
  pf = (Pow*)mymalloc(sizeof(Pow));
  Pow_init(pf);
  return Function_call((Function*)pf, name, x, y)[0];
}

Variable* poweNLC(const char* name, const float c, Variable* x) {
  Pow* pf;
  pf = (Pow*)mymalloc(sizeof(Pow));
  Pow_init(pf);
  return Function_call_with_Lconstant((Function*)pf, name, c, x)[0];
}

Variable* poweNRC(const char* name, Variable* x, const float c) {
  Pow* pf;
  pf = (Pow*)mymalloc(sizeof(Pow));
  Pow_init(pf);
  return Function_call_with_Rconstant((Function*)pf, name, x, c)[0];
}

Variable** sine_list(Variable* x) {
  Sin* pf;
  pf = (Sin*)mymalloc(sizeof(Sin));
  Sin_init(pf);
  return Function_call((Function*)pf, "", x);
}

Variable* sine(Variable* x) {
  Sin* pf;
  pf = (Sin*)mymalloc(sizeof(Sin));
  Sin_init(pf);
  return Function_call((Function*)pf, "", x)[0];
}

Variable* sineN(const char* name, Variable* x) {
  Sin* pf;
  pf = (Sin*)mymalloc(sizeof(Sin));
  Sin_init(pf);
  return Function_call((Function*)pf, name, x)[0];
}

Variable** cosi_list(Variable* x) {
  Cos* pf;
  pf = (Cos*)mymalloc(sizeof(Cos));
  Cos_init(pf);
  return Function_call((Function*)pf, "", x);
}

Variable* cosi(Variable* x) {
  Cos* pf;
  pf = (Cos*)mymalloc(sizeof(Cos));
  Cos_init(pf);
  return Function_call((Function*)pf, "", x)[0];
}

Variable* cosiN(const char* name, Variable* x) {
  Cos* pf;
  pf = (Cos*)mymalloc(sizeof(Cos));
  Cos_init(pf);
  return Function_call((Function*)pf, name, x)[0];
}

Variable** square_list(Variable* x) {
  Square* pf;
  pf = (Square*)mymalloc(sizeof(Square));
  Square_init(pf);
  return Function_call((Function*)pf, "", x);
}

Variable* square(Variable* x) {
  Square* pf;
  pf = (Square*)mymalloc(sizeof(Square));
  Square_init(pf);
  return Function_call((Function*)pf, "", x)[0];
}

Variable* squareN(const char* name, Variable* x) {
  Square* pf;
  pf = (Square*)mymalloc(sizeof(Square));
  Square_init(pf);
  return Function_call((Function*)pf, name, x)[0];
}

Variable** sub_list(Variable* x, Variable* y) {
  Sub* pf;
  pf = (Sub*)mymalloc(sizeof(Sub));
  Sub_init(pf);
  return Function_call((Function*)pf, "", x, y);
}

Variable* sub(Variable* x, Variable* y) {
  Sub* pf;
  pf = (Sub*)mymalloc(sizeof(Sub));
  Sub_init(pf);
  return Function_call((Function*)pf, "", x, y)[0];
}

Variable* subLC(const float c, Variable* x) {
  Sub* pf;
  pf = (Sub*)mymalloc(sizeof(Sub));
  Sub_init(pf);
  return Function_call_with_Lconstant((Function*)pf, "", c, x)[0];
}

Variable* subRC(Variable* x, const float c) {
  Sub* pf;
  pf = (Sub*)mymalloc(sizeof(Sub));
  Sub_init(pf);
  return Function_call_with_Rconstant((Function*)pf, "", x, c)[0];
}

Variable* subN(const char* name, Variable* x, Variable* y) {
  Sub* pf;
  pf = (Sub*)mymalloc(sizeof(Sub));
  Sub_init(pf);
  return Function_call((Function*)pf, name, x, y)[0];
}

Variable* subNLC(const char* name, const float c, Variable* x) {
  Sub* pf;
  pf = (Sub*)mymalloc(sizeof(Sub));
  Sub_init(pf);
  return Function_call_with_Lconstant((Function*)pf, name, c, x)[0];
}

Variable* subNRC(const char* name, Variable* x, const float c) {
  Sub* pf;
  pf = (Sub*)mymalloc(sizeof(Sub));
  Sub_init(pf);
  return Function_call_with_Rconstant((Function*)pf, name, x, c)[0];
}

Variable** tanhy_list(Variable* x) {
  Tanh* pf;
  pf = (Tanh*)mymalloc(sizeof(Tanh));
  Tanh_init(pf);
  return Function_call((Function*)pf, "", x);
}

Variable* tanhy(Variable* x) {
  Tanh* pf;
  pf = (Tanh*)mymalloc(sizeof(Tanh));
  Tanh_init(pf);
  return Function_call((Function*)pf, "", x)[0];
}

Variable* tanhyN(const char* name, Variable* x) {
  Tanh* pf;
  pf = (Tanh*)mymalloc(sizeof(Tanh));
  Tanh_init(pf);
  return Function_call((Function*)pf, name, x)[0];
}

Variable** reshape_list(Variable* x, const int dim, const int* shape) {
  Reshape* pf;
  pf = (Reshape*)mymalloc(sizeof(Reshape));
  Reshape_init(pf, dim, shape);
  return Function_call((Function*)pf, "", x);
}

Variable* reshape(Variable* x, const int dim, const int* shape) {
  Reshape* pf;
  pf = (Reshape*)mymalloc(sizeof(Reshape));
  Reshape_init(pf, dim, shape);
  return Function_call((Function*)pf, "", x)[0];
}

Variable* reshapeN(const char* name, Variable* x, const int dim, const int* shape) {
  Reshape* pf;
  pf = (Reshape*)mymalloc(sizeof(Reshape));
  Reshape_init(pf, dim, shape);
  return Function_call((Function*)pf, name, x)[0];
}

Variable** transpose2d_list(Variable* x) {
  Transpose2d* pf;
  pf = (Transpose2d*)mymalloc(sizeof(Transpose2d));
  Transpose2d_init(pf);
  return Function_call((Function*)pf, "", x);
}

Variable* transpose2d(Variable* x) {
  Transpose2d* pf;
  pf = (Transpose2d*)mymalloc(sizeof(Transpose2d));
  Transpose2d_init(pf);
  return Function_call((Function*)pf, "", x)[0];
}

Variable* transpose2dN(const char* name, Variable* x) {
  Transpose2d* pf;
  pf = (Transpose2d*)mymalloc(sizeof(Transpose2d));
  Transpose2d_init(pf);
  return Function_call((Function*)pf, name, x)[0];
}

Variable** transpose_list(Variable* x, const int dim, const int* axes) {
  Transpose* pf;
  pf = (Transpose*)mymalloc(sizeof(Transpose));
  Transpose_init(pf, dim, axes);
  return Function_call((Function*)pf, "", x);
}

Variable* transpose(Variable* x, const int dim, const int* axes) {
  Transpose* pf;
  pf = (Transpose*)mymalloc(sizeof(Transpose));
  Transpose_init(pf, dim, axes);
  return Function_call((Function*)pf, "", x)[0];
}

Variable* transposeN(const char* name, Variable* x, const int dim, const int* axes) {
  Transpose* pf;
  pf = (Transpose*)mymalloc(sizeof(Transpose));
  Transpose_init(pf, dim, axes);
  return Function_call((Function*)pf, name, x)[0];
}

Variable** sum_list(Variable* x, const int axis, const bool keepdims) {
  Sum* pf;
  pf = (Sum*)mymalloc(sizeof(Sum));
  Sum_init(pf, axis, keepdims);
  return Function_call((Function*)pf, "", x);
}

Variable* sum(Variable* x, const int axis, const bool keepdims) {
  Sum* pf;
  pf = (Sum*)mymalloc(sizeof(Sum));
  Sum_init(pf, axis, keepdims);
  return Function_call((Function*)pf, "", x)[0];
}

Variable* sumN(const char* name, Variable* x, const int axis, const bool keepdims) {
  Sum* pf;
  pf = (Sum*)mymalloc(sizeof(Sum));
  Sum_init(pf, axis, keepdims);
  return Function_call((Function*)pf, name, x)[0];
}

Variable** broadcast_to_list(Variable* x, const int dim, const int* shape) {
  BroadcastTo* pf;
  pf = (BroadcastTo*)mymalloc(sizeof(BroadcastTo));
  BroadcastTo_init(pf, dim, shape);
  return Function_call((Function*)pf, "", x);
}

Variable* broadcast_to(Variable* x, const int dim, const int* shape) {
  BroadcastTo* pf;
  pf = (BroadcastTo*)mymalloc(sizeof(BroadcastTo));
  BroadcastTo_init(pf, dim, shape);
  return Function_call((Function*)pf, "", x)[0];
}

Variable* broadcast_toN(const char* name, Variable* x, const int dim, const int* shape) {
  BroadcastTo* pf;
  pf = (BroadcastTo*)mymalloc(sizeof(BroadcastTo));
  BroadcastTo_init(pf, dim, shape);
  return Function_call((Function*)pf, name, x)[0];
}

Variable** sum_to_list(Variable* x, const int dim, const int* shape) {
  SumTo* pf;
  pf = (SumTo*)mymalloc(sizeof(SumTo));
  SumTo_init(pf, dim, shape);
  return Function_call((Function*)pf, "", x);
}

Variable* sum_to(Variable* x, const int dim, const int* shape) {
  SumTo* pf;
  pf = (SumTo*)mymalloc(sizeof(SumTo));
  SumTo_init(pf, dim, shape);
  return Function_call((Function*)pf, "", x)[0];
}

Variable* sum_toN(const char* name, Variable* x, const int dim, const int* shape) {
  SumTo* pf;
  pf = (SumTo*)mymalloc(sizeof(SumTo));
  SumTo_init(pf, dim, shape);
  return Function_call((Function*)pf, name, x)[0];
}

Variable** matmul_list(Variable* x, Variable* W) {
  MatMul* pf;
  pf = (MatMul*)mymalloc(sizeof(MatMul));
  MatMul_init(pf);
  return Function_call((Function*)pf, "", x, W);
}

Variable* matmul(Variable* x, Variable* W) {
  MatMul* pf;
  pf = (MatMul*)mymalloc(sizeof(MatMul));
  MatMul_init(pf);
  return Function_call((Function*)pf, "", x, W)[0];
}

Variable* matmulN(const char* name, Variable* x, Variable* W) {
  MatMul* pf;
  pf = (MatMul*)mymalloc(sizeof(MatMul));
  MatMul_init(pf);
  return Function_call((Function*)pf, name, x, W)[0];
}

Variable** mse_list(Variable* x0, Variable* x1) {
  MSE* pf;
  pf = (MSE*)mymalloc(sizeof(MSE));
  MSE_init(pf);
  return Function_call((Function*)pf, "", x0, x1);
}

Variable* mse(Variable* x0, Variable* x1) {
  MSE* pf;
  pf = (MSE*)mymalloc(sizeof(MSE));
  MSE_init(pf);
  return Function_call((Function*)pf, "", x0, x1)[0];
}

Variable* mseN(const char* name, Variable* x0, Variable* x1) {
  MSE* pf;
  pf = (MSE*)mymalloc(sizeof(MSE));
  MSE_init(pf);
  return Function_call((Function*)pf, name, x0, x1)[0];
}

Variable** linear_list(Variable* x, Variable* W, Variable* b) {
  Linear* pf;
  pf = (Linear*)mymalloc(sizeof(Linear));
  Linear_init(pf);
  return Function_call((Function*)pf, "", x, W, b);
}

Variable* linear(Variable* x, Variable* W, Variable* b) {
  Linear* pf;
  pf = (Linear*)mymalloc(sizeof(Linear));
  Linear_init(pf);
  return Function_call((Function*)pf, "", x, W, b)[0];
}

Variable* linearN(const char* name, Variable* x, Variable* W, Variable* b) {
  Linear* pf;
  pf = (Linear*)mymalloc(sizeof(Linear));
  Linear_init(pf);
  return Function_call((Function*)pf, name, x, W, b)[0];
}

Variable** sigmoid_list(Variable* x) {
  Sigmoid* pf;
  pf = (Sigmoid*)mymalloc(sizeof(Sigmoid));
  Sigmoid_init(pf);
  return Function_call((Function*)pf, "", x);
}

Variable* sigmoid(Variable* x) {
  Sigmoid* pf;
  pf = (Sigmoid*)mymalloc(sizeof(Sigmoid));
  Sigmoid_init(pf);
  return Function_call((Function*)pf, "", x)[0];
}

Variable* sigmoidN(const char* name, Variable* x) {
  Sigmoid* pf;
  pf = (Sigmoid*)mymalloc(sizeof(Sigmoid));
  Sigmoid_init(pf);
  return Function_call((Function*)pf, name, x)[0];
}

Variable* map(Variable* x, double (*func)(double)) {
  Variable* y;
  y = (Variable*)mymalloc(sizeof(Variable));
  Variable_init(y, Ndarray_map(*(x->p_data), func), "");
  return y;
}

Variable* mapN(const char* name, Variable* x, double (*func)(double)) {
  Variable* y;
  y = (Variable*)mymalloc(sizeof(Variable));
  Variable_init(y, Ndarray_map(*(x->p_data), func), name);
  return y;
}