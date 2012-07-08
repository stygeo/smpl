#include <stdio.h>
#include <iostream.h>
#include <stdarg.h>
#include "lex.h"
#include "parse.h"
#include "symtab.h"
#include "syntree.h"

int errors = 0;
void error(char *format, ...) {
  va_list args;

  errors++;
  printf("Line: %d: ", lineno);
  va_start(args, format);
  vfprintf(stdout, format, args);
  va_end(args);
  printf("\n");
}

void error_summary() {
  printf("%d error(s) were found.\n", errors);
}

void yyerror(char *msg) {
  error(msg);
}

// This function is called by the lexer when the end-of-file
// is reached; you can reset yyin (the input FILE*) and return 0
// if you want to process another file; otherwise just return 1.
extern "C" int yywrap(void) {
  return 1;
}

extern SymTab st;
extern SyntTree tree;

using namespace std;
int main(int argc, char *argv[]) {
  yyin = NULL;
  if(argc == 2)
    yyin = fopen(argv[1], "rt");
  if(yyin == NULL)
    yyin = stdin;

  yyparse();
  error_summary();

  st.show();
  tree->show();

  return errors ? 1 : 0;
}
