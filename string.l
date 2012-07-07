/* Lexical analyzer */
%{

// Includes
#include <string.h>
#include <io.h>

#define _LEX_CPP_
#include "lex.h"
#include "lexsymb.h"

extern "C" int yywrap(); // Declare yywrap

// Forwards
void identifier();
void string_constant()
void eat_comment();

%}

/* ------------------------------------
   Macros (Standard regexp)
   ------------------------------------*/

LETTER    [a-zA-Z]
DIGIT     [0-9]
IDENT     {LETTER}({LETTER}|{DIGIT})*
STR       \"[^\"]*\"
WSPACE    [ \t]+

/* ------------------------------------
   Lexer rules
   ------------------------------------*/

%%

"if"            {return IF;}
"else"          {return ELSE;}
"print"         {return PRINT;}
"input"         {return INPUT;}
"="             {return ASSIGN;}
