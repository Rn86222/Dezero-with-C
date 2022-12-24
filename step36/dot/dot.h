#include "../variable/variable.h"
#include "../macro/constant.h"

#ifndef _DOT_H_
#define _DOT_H_

void dot_var(char* line, const Variable* v, const bool verbose);
void dot_func(char* line, const Function* f);
void get_dot_graph(char* txt, const Variable* output, const bool verbose);
void plot_dot_graph(const Variable* output, const bool verbose, const bool retain_dot, char* to_file);

#endif // _DOT_H_