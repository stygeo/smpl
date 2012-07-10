/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison GLR parsers in C

   Copyright (C) 2002, 2003, 2004, 2005, 2006 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     ERROR_TOKEN = 258,
     IF = 259,
     ELSE = 260,
     PRINT = 261,
     INPUT = 262,
     ASSIGN = 263,
     EQUAL = 264,
     CONCAT = 265,
     END_STMT = 266,
     OPEN_PAR = 267,
     CLOSE_PAR = 268,
     BEGIN_CS = 269,
     END_CS = 270,
     DEF = 271,
     THEN = 272,
     END = 273,
     COMMA = 274,
     ID = 275,
     STRING = 276
   };
#endif


/* Copy the first part of user declarations.  */
#line 3 "rules/string.y"


#pragma once
// Includes
#include <string.h>

#include "lex.h"     // the lexer
#include "symtab.h"  // the symbol table
#include "syntree.h" // the syntax tree

extern SymTab st;
extern SyntTree tree;

// Yacc (bison) defines
#define YYDEBUG 1       // Generate debug code; needed for YYERROR_VERBOSE
#define YYERROR_VERBOSE // Give more specific parse error messages

// Error-reporting function must be defined by the caller
void error(char *format, ...);
// Forward references
void yyerror(const char *msg);
char *make_name();



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE 
#line 32 "rules/string.y"
{
  char     *str;     // a char string
  SymDesc  *symbol;  // entry from symbol table
  TreeNode *tnode;   // node in the syntax tree
}
/* Line 2616 of glr.c.  */
#line 101 "src/parser.hpp"
	YYSTYPE;
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{

  char yydummy;

} YYLTYPE;
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;



