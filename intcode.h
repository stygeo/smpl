#pragma once

#include "symtab.h"
#include "syntree.h"

enum Opcode  {
   OP_NOP,           // no operation
   OP_PUSH,          // push string [var]
   OP_GETTOP,        // get string from top of stack (=assign) [var]
   OP_DISCARD,       // discard top value from the stack
   OP_PRINT,         // print a string
   OP_INPUT,         // input a string [var]
   OP_JMP,           // unconditional jump [dest]
   OP_JMPF,          // jump if false [dest]
   OP_STR_EQUAL,     // test whether two strings are equal
   OP_BOOL_EQUAL,    // test whether two bools are equal
   OP_CONCAT,        // concatenate two strings
   OP_BOOL2STR,      // convert bool to string
   JUMPTARGET        // not an opcode but a jump target;
                     // the target field points to the jump instruction
};

// Intermediate code instruction
class IntInstr {
public:
   IntInstr ()   {opcode = OP_NOP; next=NULL; target=NULL; str=NULL;}
   IntInstr (Opcode _opcode)   {opcode = _opcode; next=NULL; target=NULL; str=NULL;}
   IntInstr (Opcode _opcode, IntInstr *_target)   {opcode = _opcode; target=_target; next=NULL; str=NULL;}
   IntInstr (Opcode _opcode, SymDesc *_str)   {opcode = _opcode; str = _str; next=NULL; target=NULL;}
   void show ();
   void number (int ln); // number the lines of this code block

   int       n;         // line number
   Opcode    opcode;    // the opcode
   SymDesc  *str;       // string operand
   IntInstr *target;    // jump target operand
   IntInstr *next;      // the next instruction
};

IntInstr *gen_int_code(SyntTree tree);
