#include "../variable/variable.h"
#include "../function/function.h"
#include "../function/pfunctionheap.h"
#include "../macro/constant.h"
#include "dot.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void dot_var(char* line, const Variable* v, const bool verbose) {
  char tmp[10];
  sprintf(tmp, "%p", v);
  sprintf(line, "%d", strtol(tmp, NULL, 16));
  int len = strlen(line);
  strcpy(line+len, " [label=\"");
  len = strlen(line);
  strcpy(line+len, v->name);
  len = strlen(line);
  if (verbose) {
    strcpy(line+len, ": [");
    len = strlen(line);;
    for (int i = 0; i < v->p_data->dim - 1; i++) {
      sprintf(line+len, "%d", v->p_data->shape[i]);
      len = strlen(line);
      strcpy(line+len, ", ");
      len = strlen(line);
    }
    sprintf(line+len, "%d", v->p_data->shape[v->p_data->dim-1]);
    len = strlen(line);
    strcpy(line+len, "]");
  }
  len = strlen(line);
  strcpy(line+len, "\", color=orange, style=filled]\n");
}

void dot_func(char* line, const Function* f) {
  char tmp[10];
  sprintf(tmp, "%p", f);
  sprintf(line, "%d", strtol(tmp, NULL, 16));
  int len = strlen(line);
  strcpy(line+len, " [label=\"");
  len = strlen(line);
  strcpy(line+len, f->name);
  len = strlen(line);
  strcpy(line+len, "\", color=lightblue, style=filled, shape=box]\n");
  len = strlen(line);
  for (int i = 0; i < f->input_num; i++) {
    sprintf(tmp, "%p", f->p_io[0][i]);
    sprintf(line+len, "%d", strtol(tmp, NULL, 16));
    len = strlen(line);
    strcpy(line+len, " -> ");
    len = strlen(line);
    sprintf(tmp, "%p", f);
    sprintf(line+len, "%d", strtol(tmp, NULL, 16));
    len = strlen(line);
    strcpy(line+len, "\n");
    len = strlen(line);
  }
  for (int i = 0; i < f->output_num; i++) {
    sprintf(tmp, "%p", f);
    sprintf(line+len, "%d", strtol(tmp, NULL, 16));
    len = strlen(line);
    strcpy(line+len, " -> ");
    len = strlen(line);
    sprintf(tmp, "%p", f->p_io[1][i]);
    sprintf(line+len, "%d", strtol(tmp, NULL, 16));
    len = strlen(line);
    strcpy(line+len, "\n");
    len = strlen(line);
  }
}

void get_dot_graph(char* txt, const Variable* output, const bool verbose) {
  PFunctionHeap fh;
  PFunctionHeap_init(&fh, FUNCTION_HEAP_SIZE);
  PFunctionHeap_insert(&fh, output->p_creator);
  Function* p_f;

  Function** seen_fs;
  seen_fs = (Function**)malloc(FUNCTION_HEAP_SIZE * sizeof(Function*));
  seen_fs[0] = output->p_creator;
  int cnt = 1;

  strcpy(txt, "digraph g {\n");
  int len = strlen(txt);
  dot_var(txt+len, output, verbose);
  len = strlen(txt);

  while (fh.last != -1) {
    p_f = PFunctionHeap_deletemax(&fh);
    dot_func(txt+len, p_f);
    len = strlen(txt);
    for (int i = 0; i < p_f->input_num; i++) {
      dot_var(txt+len, p_f->p_io[0][i], verbose);
      len = strlen(txt);
      if (p_f->p_io[0][i]->creator_exists) {
        bool found = FALSE;
        for (int j = 0; j < cnt; j++) {
          if (seen_fs[j] == p_f->p_io[0][i]->p_creator) {
            found = TRUE;
            break;
          }
        }
        if (!found) {
          PFunctionHeap_insert(&fh, p_f->p_io[0][i]->p_creator);
          seen_fs[cnt++] = p_f->p_io[0][i]->p_creator;
        }
      }
    }
  }
  strcpy(txt+len, "}");
  free(seen_fs);
}

void plot_dot_graph(const Variable* output, const bool verbose, const bool retain_dot, char* to_file) {
  FILE *fp;
  fp = fopen("tmp_graph.dot", "w");

  char* txt;
  txt = (char*)malloc(10000000 * sizeof(char));
  get_dot_graph(txt, output, verbose);
  fprintf(fp, txt);
  fclose(fp);
  char cmd[50];
  strcpy(cmd, "dot tmp_graph.dot -T png -o ");
  if (strcmp(to_file, "") != 0) {
    strcat(cmd, to_file);
  } else {
    strcat(cmd, "graph.png");
  }
  system(cmd);
  if (!retain_dot)
    system("del tmp_graph.dot");
  free(txt);
}