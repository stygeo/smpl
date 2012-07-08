#include <stdio.h>
#include "syntree.h"
#include "symtab.h"

void error(char *format, ...);

// Node names        
char *name[] = {
   "statement list",
   "empty statement",
   "expression statement",
   "print statement",
   "input statement",
   "if..then statement",
   "if..then..else statement",
   "error statement",

   "equals",
   "assign",
   "concatenate",
   "identifier",
   "string constant"
};

// Numbers of children per node type
int children[] = {
   2, 0, 1, 1, 0, 2, 3, 0, 2, 1, 2, 0, 0
};

// Recursively show the contents of the syntax tree
void TreeNode::show(int level)   {
   int i,nl;
   if(type != STMT_LIST)   {
      for(i = 0; i < level; i++)   printf("   ");
      printf("%s", name[type]);
      switch(type)  {
      case INPUT_STMT: case ASSIGN_EXPR: case IDENT_EXPR:
         printf("(%s)", symbol->name); break;
      case STR_EXPR:
         printf("(\"%s\")", symbol->cont); break;
      }
      nl = level + 1;
      printf("\n");
   } else nl = level;
   for(i = 0; i < children[type]; i++)   child[i]->show(nl);
}

// Check the semantics of this node
int TreeNode::coerce_to_string(int childno) {
  if(child[childno]->rettype == T_STRING)
    return 1;
  if(child[childno]->rettype != T_BOOL)
    return 0;
  child[childno] = new TreeNode(COERCE_TO_STR, child[childno]);
  return 1;
}

void TreeNode::check() {
  switch(type)  {
    case STMT_LIST: case EMPTY_STMT: case EXPR_STMT:
    case PRINT_STMT: case INPUT_STMT: case IFTHEN_STMT:
    case IFTHENELSE_STMT: case ERROR_STMT:
      rettype = T_VOID;  // statements have no value
      break;
    case EQUAL_EXPR:
      rettype = T_BOOL;
      break;
    case CONCAT_EXPR:
    case ASSIGN_EXPR:
      rettype = T_STRING;
      break;
    case IDENT_EXPR:
    case STR_EXPR:
      rettype = T_STRING;
      break;
    case COERCE_TO_STR:
      rettype = T_STRING;
  }

  // Now, check the semantics
  switch(type)  {
    case IFTHEN_STMT:
    case IFTHENELSE_STMT:
      if(child[0]->rettype != T_BOOL)
        error("if: Condition should be boolean");
      break;
    case EQUAL_EXPR: // no coercions here, types have to be equal
      if(child[0]->rettype != child[1]->rettype)
        error("==: Different types");
      break;
    case CONCAT_EXPR: // coerce both expressions to string
      // Note: these error messages should never appear
      if(!coerce_to_string(0))   
        error("+: Can't coerce first argument to string");
      if(!coerce_to_string(1))   
        error("+: Can't coerce second argument to string");
    case ASSIGN_EXPR: // coerce expression to string
      if(!coerce_to_string(0))   
        error("=: Can't coerce to string");
      break;
  }
}
