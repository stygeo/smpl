/* Parser for smpl */

%{

// Includes
#include <string.h>

#include "lex.h"     // the lexer
#include "symtab.h"  // the symbol table
#include "syntree.h" // the syntax tree

SymTab st;
SyntTree tree;

// Yacc (bison) defines
#define YYDEBUG 1       // Generate debug code; needed for YYERROR_VERBOSE
#define YYERROR_VERBOSE // Give more specific parse error messages

// Error-reporting function must be defined by the caller
void error(char *format, ...);
// Forward references
void yyerror(char *msg);
char *make_name();

%}

/* -----------------------------------
   Yacc declarations
   -----------------------------------*/

%union {
  char     *str;     // a char string
  SymDesc  *symbol;  // entry from symbol table
  TreeNode *tnode;   // node in the syntax tree
}

/* Token definitions */
%token ERROR_TOKEN IF ELSE PRINT INPUT ASSIGN EQUAL
%token CONCAT END_STMT OPEN_PAR CLOSE_PAR
%token BEGIN_CS END_CS 
%token <str> ID STRING

/* Rule type definitions */
%type <symbol> identifier string
%type <tnode>  program statement_list statement
%type <tnode>  if_statement optional_else_statement compound_statement
%type <tnode>  expression equal_expression assign_expression
%type <tnode>  concat_expression simple_expression

%expect 1 /* shift/reduce conflict: dangling ELSE */
          /* declaration */

%%

/* -----------------------------------
   Yacc grammer rules
   -----------------------------------*/

program
      : statement_list              {tree = $1;}
    ;

statement_list
      : statement_list statement    {$$ = new TreeNode(STMT_LIST, $1, $2);}
      | /* Empty */                 {$$ = new TreeNode(EMPTY_STMT);}
      ;

statement
      : END_STMT                    {$$ = new TreeNode(EMPTY_STMT);}
      | expression END_STMT         {$$ = new TreeNode(EXPR_STMT, $1);}
      | PRINT expression END_STMT   {$$ = new TreeNode(PRINT_STMT, $2);}
      | INPUT identifier END_STMT   {$$ = new TreeNode(INPUT_STMT); $$->symbol = $2;}
      | if_statement                {$$ = $1;}
      | compound_statement          {$$ = $1;}
      | error END_STMT              {$$ = new TreeNode(ERROR_STMT);}
      ;

/* NOTE: This rule causes an unresolvable shift/reduce conflict;
   That's why %expect 1 was added (see above) */
if_statement
      : IF OPEN_PAR expression CLOSE_PAR statement optional_else_statement
        {
          if($6 != NULL)
            $$ = new TreeNode(IFTHENELSE_STMT, $3, $5, $6);
          else
            $$ = new TreeNode(IFTHEN_STMT, $3, $5);
        }
      ;

optional_else_statement
      : ELSE statement      {$$ = $2;}
      | /* Empty */         {$$ = NULL;}
      ;

compound_statement
      : BEGIN_CS statement_list END_CS  {$$ = $2;}
      ;

expression
      : equal_expression                {$$ = $1;}
      ;

equal_expression
      : expression EQUAL assign_expression  {$$ = new TreeNode(EQUAL_EXPR, $1, $3);}
      | assign_expression                   {$$ = $1;}
      ;

assign_expression
      : identifier ASSIGN assign_expression {$$ = new TreeNode(ASSIGN_EXPR, $3); $$->symbol = $1;}
      | concat_expression                   {$$ = $1;}
      ;

concat_expression
      : concat_expression CONCAT simple_expression  {$$ = new TreeNode(CONCAT_EXPR, $1, $3);}
      | simple_expression                           {$$ = $1;}
      ;

simple_expression
      : identifier                    {$$ = new TreeNode(IDENT_EXPR); $$->symbol = $1;}      
      | string                        {$$ = new TreeNode(STR_EXPR); $$->symbol = $1;}
      | OPEN_PAR expression CLOSE_PAR {$$ = $2;}
      ;

identifier
      : ID
        {
          $$ = st.find($1);
          if($$ == NULL) {
            $$ = new SymDesc($1, STR_VAR, NULL, lineno);
            st.add($$);
          }
        }
      ;

string
      : STRING
        {
          $$ = new SymDesc(make_name(), STR_CONST, $1, lineno);
          st.add($$);
        }
      ;

%%


char *make_name() {
  char *name = new char[10], num[4];
  static int n = 0;
  sprintf(num, "%d", ++n);
  strcpy(name, "strconst"); strcat(name, num);
  return name;
}
