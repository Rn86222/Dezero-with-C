#include "function.h"
#include "add.h"
#include "div.h"
#include "exp.h"
#include "log.h"
#include "mul.h"
#include "neg.h"
#include "pow.h"
#include "sin.h"
#include "square.h"
#include "sub.h"
#include "cos.h"
#include "tanh.h"
#include "reshape.h"
#include "transpose2d.h"
#include "transpose.h"
#include "../variable/variable.h"

#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

Variable** add_list(Variable* x, Variable* y);
Variable* add(Variable* x, Variable* y);
Variable* addLC(const float c, Variable* x);
Variable* addRC(Variable* x, const float c);
Variable* addN(const char* name, Variable* x, Variable* y);
Variable* addNLC(const char* name, const float c, Variable* x);
Variable* addNRC(const char* name, Variable* x, const float c);

Variable** divi_list(Variable* x, Variable* y);
Variable* divi(Variable* x, Variable* y);
Variable* diviLC(const float c, Variable* x);
Variable* diviRC(Variable* x, const float c);
Variable* diviN(const char* name, Variable* x, Variable* y);
Variable* diviNLC(const char* name, const float c, Variable* x);
Variable* diviNRC(const char* name, Variable* x, const float c);

Variable** expo_list(Variable* x);
Variable* expo(Variable* x);
Variable* expoN(const char* name, Variable* x);

Variable** ln_list(Variable* x);
Variable* ln(Variable* x);
Variable* lnN(const char* name, Variable* x);

Variable** mul_list(Variable* x, Variable *y);
Variable* mul(Variable* x, Variable *y);
Variable* mulLC(const float c, Variable *x);
Variable* mulRC(Variable* x, const float c);
Variable* mulN(const char* name, Variable* x, Variable *y);
Variable* mulNLC(const char* name, const float c, Variable *x);
Variable* mulNRC(const char* name, Variable* x, const float c);

Variable** neg_list(Variable* x);
Variable* neg(Variable* x);
Variable* negN(const char* name, Variable* x);

Variable** powe_list(Variable* x, Variable* y);
Variable* powe(Variable* x, Variable* y);
Variable* poweLC(const float c, Variable* x);
Variable* poweRC(Variable* x, const float c);
Variable* poweN(const char* name, Variable* x, Variable* y);
Variable* poweNLC(const char* name, const float c, Variable* x);
Variable* poweNRC(const char* name, Variable* x, const float c);

Variable** sine_list(Variable* x);
Variable* sine(Variable* x);
Variable* sineN(const char* name, Variable* x);

Variable** cosi_list(Variable* x);
Variable* cosi(Variable* x);
Variable* cosiN(const char* name, Variable* x);

Variable** square_list(Variable* x);
Variable* square(Variable* x);
Variable* squareN(const char* name, Variable* x);

Variable** sub_list(Variable* x, Variable* y);
Variable* sub(Variable* x, Variable* y);
Variable* subLC(const float c, Variable* x);
Variable* subRC(Variable* x, const float c);
Variable* subN(const char* name, Variable* x, Variable* y);
Variable* subNLC(const char* name, const float c, Variable* x);
Variable* subNRC(const char* name, Variable* x, const float c);

Variable** tanhy_list(Variable* x);
Variable* tanhy(Variable* x);
Variable* tanhyN(const char* name, Variable* x);

Variable** reshape_list(Variable* x, const int dim, const int* shape);
Variable* reshape(Variable* x, const int dim, const int* shape);
Variable* reshapeN(const char* name, Variable* x, const int dim, const int* shape);

Variable** transpose2d_list(Variable* x);
Variable* transpose2d(Variable* x);
Variable* transpose2dN(const char* name, Variable* x);

Variable** transpose_list(Variable* x, const int dim, const int* axes);
Variable* transpose(Variable* x, const int dim, const int* axes);
Variable* transposeN(const char* name, Variable* x, const int dim, const int* axes);

Variable* map(Variable* x, double (*func)(double));
Variable* mapN(const char* name, Variable* x, double (*func)(double));

#endif