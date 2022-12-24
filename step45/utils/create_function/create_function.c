#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static void copy(char* s1, const char* s2) {
  int len = strlen(s1);
  strcpy(s1+len, s2);
}

static char upper(char c) {
  if ('a' <= c && c <= 'z')
    return c + 'A' - 'a';
  return c;
}

static char* upper_first(char* s) {
  char* s2;
  int len = strlen(s);
  s2 = (char*)malloc(len * sizeof(char));
  s2[0] = upper(s[0]);
  for (int i = 1; i < len; i++)
    s2[i] = s[i];
  s2[len] = '\0';
  return s2;
}

static char* strupper(char* s) {
  char* s2;
  int len = strlen(s);
  s2 = (char*)malloc(len * sizeof(char));
  s2[0] = '\0';
  for (int i = 0; i < len; i++)
    s2[i] = upper(s[i]);
  s2[len] = '\0';
  return s2;
}


int main() {
  char cfile_path[100] = "\0";
  char hfile_path[100] = "\0";
  char func_name[50] = "\0";
  int input_num;
  int output_num;
  int len;
  printf("input function name: ");
  scanf("%s", func_name);
  printf("input num: ");
  scanf("%d",&input_num);
  printf("output num: ");
  scanf("%d",&output_num);
  copy(cfile_path, "function/");
  copy(cfile_path, func_name);
  copy(cfile_path, ".c");
  copy(hfile_path, "function/");
  copy(hfile_path, func_name);
  copy(hfile_path, ".h");
  
  char ctxt[5000] = "\0";
  char htxt[3000] = "\0";

  copy(ctxt, "#include \"");
  copy(ctxt, func_name);
  copy(ctxt, ".h\"\n");
  copy(ctxt, "#include \"function.h\"\n#include \"functions.h\"\n#include \"../variable/variable.h\"\n#include \"../ndarray/ndarray.h\"\n#include <math.h>\n#include <assert.h>\n#include <stdlib.h>\n#include <string.h>\n\n");
  
  copy(ctxt, "static Ndarray* ");
  copy(ctxt, func_name);
  copy(ctxt, "_forward(Function* const p_self, const Ndarray* xs) {\n\tNdarray* ys;\n\tys = (Ndarray*)malloc(p_self->output_num * sizeof(Ndarray));\n\tys[0] = xs[0];\n\treturn ys;\n}\n\n");
  
  copy(ctxt, "static Variable** ");
  copy(ctxt, func_name);
  copy(ctxt, "_backward(Function* const p_self, Variable** gys) {\n\tVariable** gxs;\n\tgxs = (Variable**)malloc(p_self->input_num * sizeof(Variable*));\n\tgxs[0] = gys[0];\n\treturn gxs;\n}\n\n");
  copy(ctxt, "static const FunctionMethods ");
  copy(ctxt, strupper(func_name));
  copy(ctxt, "_METHODS = {\n\t");
  copy(ctxt, func_name);
  copy(ctxt, "_forward,\n\t");
  copy(ctxt, func_name);
  copy(ctxt, "_backward\n};\n\n");
  
  copy(ctxt, "void ");
  copy(ctxt, upper_first(func_name));
  copy(ctxt, "_init(");
  copy(ctxt, upper_first(func_name));
  copy(ctxt, "* p_self) {\n\t((Function*)p_self)->p_methods = &");
  copy(ctxt, strupper(func_name));
  copy(ctxt, "_METHODS;\n\tFunction_init((Function*)p_self, ");
  len = strlen(ctxt);
  sprintf(ctxt+len, "%d, %d);\n\t", input_num, output_num);
  copy(ctxt, "strcpy(((Function*)p_self)->name, \"");
  copy(ctxt, upper_first(func_name));
  copy(ctxt, "\");\n}\n");

  copy(htxt, "#include \"function.h\"\n\n");
  copy(htxt, "#ifndef _");
  copy(htxt, strupper(func_name));
  copy(htxt, "_H_\n");
  copy(htxt, "#define _");
  copy(htxt, strupper(func_name));

  copy(htxt, "_H_\n\ntypedef struct ");
  copy(htxt, func_name);
  copy(htxt, " {\n\tFunction function;\n} ");
  copy(htxt, upper_first(func_name));
  copy(htxt, ";\n\n");

  copy(htxt, "void ");
  copy(htxt, upper_first(func_name));
  copy(htxt, "_init(");
  copy(htxt, upper_first(func_name));
  copy(htxt, "* p_self);\n\n#endif // _");
  copy(htxt, strupper(func_name));
  copy(htxt, "_H_");

  FILE *cfp;
  cfp = fopen(cfile_path, "w");
  fprintf(cfp, ctxt);
  fclose(cfp);

  FILE *hfp;
  hfp = fopen(hfile_path, "w");
  fprintf(hfp, htxt);
  fclose(hfp);  
  return 0;
}
