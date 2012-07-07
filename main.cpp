#include <stdio.h>
#include <iostream.h>
#include "lex.h"
#include "lexsymb.h"

char *name[] = {
  "IF", "ELSE", "PRINT", "INPUT", "ASSIGN", "EQUAL",
  "CONCAT", "END_STMT", "OPEN_PAR", "CLOSE_PAR", "BEGIN_CS", "END_CS",
  "ID", "STRING",
};

YYSTYPE yylval; // Union in which strings are passed.

// This function is called by the lexer when the end-of-file
// is reached; you can reset yyin (the input FILE*) and return 0
// if you want to process another file; otherwise just return 1.
extern "C" int yywrap(void) {
  return 1;
}

using namespace std;
int main(int argc, char *argv[]) {
  int token;

  yyin = NULL;
  if(argc == 2) {
    yyin = fopen(argv[1], "rt");
  }
  if(yyin == NULL)
    yyin = stdin;

  while((token = yylex()) != 0) {
    cout << "Token: ";
    switch(token) {
      case ID:
        cout << name[token-IF] << " = " << yylval.str << endl;
        delete [] yylval.str;
        break;
      case ERROR_TOKEN:
        cout << "Error parsing: " << token << endl;
        break;
      default:
        cout << name[token-IF] << endl;
        break;
    }
  }
  return 0;
}
