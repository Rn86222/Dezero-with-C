#include "../variable/variable.h"
#include "../function/function.h"
#include "../function/pfunctionheap.h"
#include "../macro/constant.h"
#include "dot.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void copy(char* s1, const char* s2) {
  int len = strlen(s1);
  strcpy(s1+len, s2);
}

void dot_var(char* line, const Variable* v, const bool verbose) {
  char tmp[20];
  sprintf(tmp, "%p", v);
  sprintf(line, "%d", (int)strtol(tmp, NULL, 16));
  int len ;
  copy(line, " [label=\"");
  if (strlen(v->name) == 0) {
    copy(line, "None");
  } else {
    copy(line, v->name);
  }
  if (verbose) {
    copy(line, ": [");
    for (int i = 0; i < v->p_data->dim - 1; i++) {
      len = strlen(line);
      sprintf(line+len, "%d", v->p_data->shape[i]);
      copy(line, ", ");
    }
    len = strlen(line);
    if (v->p_data->dim != 0) {
      sprintf(line+len, "%d", v->p_data->shape[v->p_data->dim-1]);
    } else {
      sprintf(line+len, "None");
    }
    copy(line, "]");
  }
  len = strlen(line);
  copy(line, "\", color=orange, style=filled]\n");
}

void dot_func(char* line, const Function* f) {
  char tmp[20];
  sprintf(tmp, "%p", f);
  sprintf(line, "%d", (int)strtol(tmp, NULL, 16));
  int len ;
  copy(line, " [label=\"");
  copy(line, f->name);
  copy(line, "\", color=lightblue, style=filled, shape=box]\n");
  for (int i = 0; i < f->input_num; i++) {
    sprintf(tmp, "%p", f->p_io[0][i]);
    len = strlen(line);
    sprintf(line+len, "%d", (int)strtol(tmp, NULL, 16));
    copy(line, " -> ");
    sprintf(tmp, "%p", f);
    len = strlen(line);
    sprintf(line+len, "%d", (int)strtol(tmp, NULL, 16));
    copy(line, "\n");
  }
  for (int i = 0; i < f->output_num; i++) {
    sprintf(tmp, "%p", f);
    len = strlen(line);
    sprintf(line+len, "%d", (int)strtol(tmp, NULL, 16));
    copy(line, " -> ");
    sprintf(tmp, "%p", f->p_io[1][i]);
    len = strlen(line);
    sprintf(line+len, "%d", (int)strtol(tmp, NULL, 16));
    copy(line, "\n");
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

  while (fh.last != -1) {
    p_f = PFunctionHeap_deletemax(&fh);
    len = strlen(txt);
    dot_func(txt+len, p_f);
    for (int i = 0; i < p_f->input_num; i++) {
      len = strlen(txt);
      dot_var(txt+len, p_f->p_io[0][i], verbose);
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
  copy(txt, "}");
  free(seen_fs);
}

void plot_dot_graph(const Variable* output, const bool verbose, const bool retain_dot, char* to_file) {
  FILE *fp;
  fp = fopen("tmp_graph.dot", "w");

  char* txt;
  txt = (char*)malloc(DOT_TEXT_SIZE * sizeof(char));
  get_dot_graph(txt, output, verbose);
  fprintf(fp, "%s", txt);
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
    system("rm tmp_graph.dot");
  free(txt);
}