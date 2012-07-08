/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

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
     ID = 274,
     STRING = 275
   };
#endif
/* Tokens.  */
#define ERROR_TOKEN 258
#define IF 259
#define ELSE 260
#define PRINT 261
#define INPUT 262
#define ASSIGN 263
#define EQUAL 264
#define CONCAT 265
#define END_STMT 266
#define OPEN_PAR 267
#define CLOSE_PAR 268
#define BEGIN_CS 269
#define END_CS 270
#define DEF 271
#define THEN 272
#define END 273
#define ID 274
#define STRING 275




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 31 "rules/string.y"
{
  char     *str;     // a char string
  SymDesc  *symbol;  // entry from symbol table
  TreeNode *tnode;   // node in the syntax tree
}
/* Line 1529 of yacc.c.  */
#line 95 "src/parser.hpp"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

