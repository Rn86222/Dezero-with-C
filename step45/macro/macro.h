#include "../function/function.h"
#include "../variable/variable.h"

#ifndef _MACRO_H_
#define _MACRO_H_

#define FC1(p_func, variable_name, p_v) Function_call((Function*)p_func, variable_name, p_v)
#define FC10(p_func, variable_name, p_v) Function_call((Function*)p_func, variable_name, p_v)[0]
#define fc1(p_func, p_v) Function_call((Function*)p_func, "", p_v)
#define fc10(p_func, p_v) Function_call((Function*)p_func, "", p_v)[0]
#define FC2(p_func, variable_name, p_v0, p_v1) Function_call((Function*)p_func, variable_name, p_v0, p_v1)
#define FC20(p_func, variable_name, p_v0, p_v1) Function_call((Function*)p_func, variable_name, p_v0, p_v1)[0]
#define fc2(p_func, p_v0, p_v1) Function_call((Function*)p_func, "", p_v0, p_v1)
#define fc20(p_func, p_v0, p_v1) Function_call((Function*)p_func, "", p_v0, p_v1)[0]
#define FC2C(p_func, variable_name, p_v, constant) Function_call_with_Rconstant((Function*)p_func, variable_name, p_v, constant)
#define FC2C0(p_func, variable_name, p_v, constant) Function_call_with_Rconstant((Function*)p_func, variable_name, p_v, constant)[0]
#define fc2c(p_func, p_v, constant) Function_call_with_Rconstant((Function*)p_func, "", p_v, constant)
#define fc2c0(p_func, p_v, constant) Function_call_with_Rconstant((Function*)p_func, "", p_v, constant)[0]
#define FC2Cl(p_func, variable_name, constant, p_v) Function_call_with_Lconstant((Function*)p_func, variable_name, constant, p_v)
#define FC2Cl0(p_func, variable_name, constant, p_v) Function_call_with_Lconstant((Function*)p_func, variable_name, constant, p_v)[0]
#define fc2cl(p_func, constant, p_v) Function_call_with_Lconstant((Function*)p_func, "", constant, p_v)
#define fc2cl0(p_func, constant, p_v) Function_call_with_Lconstant((Function*)p_func, "", constant, p_v)[0]
#define FD(p_func) Function_destroy((Function*)p_func)
#define VM(func) (Variable**)malloc(func.function.output_num * sizeof(Variable*))

#endif // _MACRO_H_