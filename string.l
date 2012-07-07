/* Lexical analyzer */
%{

/* Includes */
#include <string.h>
#include <iostream>

#define _LEX_CPP_
#include "lex.h"
#include "lexsymb.h"

extern "C" int yywrap(); // Declare yywrap

/* Forwards */
void identifier();
void string_constant();
void eat_comment();

%}

/* ------------------------------------
   Macros (Standard regexp)
   ------------------------------------*/

LETTER   [a-zA-Z_]
DIGIT    [0-9]
IDENT    {LETTER}({LETTER}|{DIGIT})*
STR      \"[^\"]*\"
WSPACE   [ \t]+

/* ------------------------------------
   Lexer rules
   ------------------------------------*/

%%

"if"      {return IF;}
"else"    {return ELSE;}
"print"   {return PRINT;}
"input"   {return INPUT;}
"="       {return ASSIGN;}
"=="      {return EQUAL;}
"+"       {return CONCAT;}
";"       {return END_STMT;}
"\n"      {return END_STMT;}
"("       {return OPEN_PAR;}
")"       {return CLOSE_PAR;}
"{"       {return BEGIN_CS;}
"}"       {return END_CS;}
{IDENT}   {identifier();
          return STRING;}
{STR}     {string_constant();
          return STRING;}
"//"      {eat_comment();}
\n        {lineno++;}
{WSPACE}  {}
.         {return ERROR_TOKEN;}

%%

/* ------------------------------------
   Functions
   ------------------------------------*/

void eat_comment() {
  char c;

  while((c == yyinput()) != '\n' && c != 0);
  lineno++;
}

/* Pass ID */
void identifier() {
  yylval.str = new char[strlen(yytext+1)];
  strcpy(yylval.str, yytext);
}

/* Pass string const */
void string_constant() {
  int l = strlen(yytext)-2;
  yylval.str = new char[l+1];
  strncpy(yylval.str, &yytext[1], l); yylval.str[l] = 0;
}
