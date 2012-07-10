#include <stdio.h>
#include <iostream.h>
#include <stdarg.h>
#include "lex.h"
#include "parse.h"
#include "symtab.h"
#include "syntree.h"
#include "intcode.h"
#include "vm.h"

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

void yyerror(const char *msg) {
  error((char*)msg);
}

// This function is called by the lexer when the end-of-file
// is reached; you can reset yyin (the input FILE*) and return 0
// if you want to process another file; otherwise just return 1.
extern "C" int yywrap(void) {
  return 1;
}

SymTab st;
SyntTree tree;

IntInstr *intcode;

int main(int argc, char *argv[]) {
  bool debug = true;

  yyin = NULL;
  if(argc == 2)
    yyin = fopen(argv[1], "rt");
  if(yyin == NULL)
    yyin = stdin;

  yyparse();
  error_summary();

  if(debug) {
    st.show();
    tree->show();
  }

  if(!errors) {
    intcode = gen_int_code(tree);
    intcode->number(1);

    if(debug) intcode->show();

    VMachine vm;
    vm.read();
    vm.execute();

    return 0;
  }

  return 1;
}
