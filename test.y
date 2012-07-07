/* Parser for StringC */

%{

/* ------------------------------------------------------------------
   Initial code (copied verbatim to the output file)
   ------------------------------------------------------------------ */

// Includes
#include <malloc.h>  // _alloca is used by the parser
#include <string.h>  // strcpy

#include "lex.h"     // the lexer

// Some yacc (bison) defines
#define YYDEBUG 1	      // Generate debug code; needed for YYERROR_VERBOSE
#define YYERROR_VERBOSE // Give a more specific parse error message 

// Error-reporting function must be defined by the caller
void Error (char *format, ...);

// Forward references
void yyerror (char *msg);

%}

/* ------------------------------------------------------------------
   Yacc declarations
   ------------------------------------------------------------------ */

/* The structure for passing value between lexer and parser */
%union {
   char *str;
}

%token ERROR_TOKEN IF ELSE PRINT INPUT ASSIGN EQUAL
%token CONCAT END_STMT OPEN_PAR CLOSE_PAR
%token BEGIN_CS END_CS 
%token <str> ID STRING

/*%type <type> type simple_type cast*/

%expect 1  /* shift/reduce conflict: dangling ELSE */
           /*    declaration */
%%

/* ------------------------------------------------------------------
   Yacc grammar rules
   ------------------------------------------------------------------ */

program
      : statement_list
		;

statement_list
      : statement_list statement
      | /* empty */
      ;

statement
      : END_STMT                    {puts ("Empty statement");}
      | expression END_STMT         {puts ("Expression statement");}
      | PRINT expression END_STMT   {puts ("Print statement");}
      | INPUT identifier END_STMT   {puts ("Input statement");}
      | if_statement                {puts ("If statement");}
      | compound_statement          {puts ("Compound statement");}
      | error END_STMT              {puts ("Error statement");}
      ;

/* NOTE: This rule causes an unresolvable shift/reduce conflict;
   That's why %expect 1 was added (see above) */
if_statement
      : IF OPEN_PAR expression CLOSE_PAR statement optional_else_statement
      ;

optional_else_statement
      : ELSE statement
      | /* empty */
      ;

compound_statement
      : BEGIN_CS statement_list END_CS
      ;

expression
      : equal_expression
      | OPEN_PAR expression CLOSE_PAR
      ;

equal_expression
      : expression EQUAL assign_expression
      | assign_expression
      ;

assign_expression
      : identifier ASSIGN assign_expression
      | concat_expression
      ;

concat_expression
      : concat_expression CONCAT simple_expression
      | simple_expression
      ;

simple_expression
      : identifier
      | string
      ;

identifier
      : ID              {}
      ;

string
      : STRING          {}
      ;

%%
/* ------------------------------------------------------------------
   Additional code (again copied verbatim to the output file)
   ------------------------------------------------------------------ */

