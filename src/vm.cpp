#include <iostream.h>
#include <string.h>
#include "vm.h"

VMachine::VMachine() {
  instr = NULL; ninstr = 0;
  int i;
  for(i = 0; i < MAX_STR; i++) {
    str[i]=NULL;
  }
}

VMachine::~VMachine() {
  reset();
}

void VMachine::reset() {
  int i;
  for(i = 0; i < MAX_STR; i++) {
    if(str[i] != NULL) { delete str[i]; str[i] = NULL; }
  }
  if(instr != NULL) { delete[] instr; instr = NULL; ninstr = 0; }
  stack.empty();
}

// Read a program from stdin
// (hardwired for testing purposes)
void VMachine::read()   {
   str[0] = new String("Answer to the Ultimate Question"
      " of Life, the Universe and Everything > ");
   str[1] = new String;
   str[2] = new String("42");
   str[3] = new String("Right!\n");
   str[4] = new String("Wrong!\n");

   // A very simple program for testing purposes
   ninstr = 11;
   instr = new Instr[ninstr];
   instr[0] = Instr (OP_PUSH,  0);   // print "...";
   instr[1] = Instr (OP_PRINT);
   instr[2] = Instr (OP_INPUT, 1);   // input answer;
   instr[3] = Instr (OP_PUSH,  1);   // if (answer == "42")
   instr[4] = Instr (OP_PUSH,  2);
   instr[5] = Instr (OP_STR_EQUAL);
   instr[6] = Instr (OP_JMPF,  3);
   instr[7] = Instr (OP_PUSH,  3);   //      print "Right!\n";
   instr[8] = Instr (OP_JMP,   2);
   instr[9] = Instr (OP_PUSH,  4);   // else print "Wrong!\n";
   instr[10]= Instr (OP_PRINT);
}

void VMachine::execute ()   {
   int ip; // instruction pointer
   VM_stack stack;  // the stack
   int ipc; // instruction pointer change
   int i,j,k;

   ip = 0; // start at instruction 0
   while (ip < ninstr)   {
      ipc = 1; // default: add one to ip
      switch (instr[ip].opcode)   {
      case OP_NOP:
         // No OPeration
         break;
      case OP_PUSH:
         // Push a variable onto the stack
         stack.push (new_temp_copy(instr[ip].operand));
         break;
      case OP_GETTOP:
         str[instr[ip].operand]->assign (*str[stack.get_top()]);
         break;
      case OP_DISCARD:
         del_temp_copy(stack.pop());
         break;
      case OP_PRINT:
         i = stack.pop();
         str[i]->print();
         del_temp_copy(i);
         break;
      case OP_INPUT:
         str[instr[ip].operand]->input ();
         break;
      case OP_JMP:
         ipc = instr[ip].operand;
         break;
      case OP_JMPF:
         i = stack.pop();
         if (i == ST_FALSE)   ipc = instr[ip].operand;
         break;
      case OP_STR_EQUAL:
         i = stack.pop(); j = stack.pop();
         if (strcmp (str[i]->val(), str[j]->val()) == 0)   k = ST_TRUE; else k = ST_FALSE;
         del_temp_copy(i); del_temp_copy(j);
         stack.push (k);
         break;
      case OP_BOOL_EQUAL:
         i = stack.pop(); j = stack.pop();
         if (i == j)   k = ST_TRUE; else k = ST_FALSE;
         stack.push (k);
         break;
      case OP_CONCAT:
         i = stack.pop(); j = stack.pop();
         k = new_temp_copy(j); str[k]->concatenate (*str[i]);
         del_temp_copy(i); del_temp_copy(j);
         stack.push (k);
         break;
      case OP_BOOL2STR:
         i = stack.pop();
         if (i == ST_FALSE)   i = new_temp_copy("false"); else i = new_temp_copy("true");
         stack.push (i);
         break;
      }
      ip += ipc;
   }
}

int VMachine::new_temp_copy() {
  int i;
  for(i = 0; i < MAX_STR; i++) {
    if(str[i] == NULL) {
      str[i] = new String;
      break;
    }
  }
  if(i == MAX_STR)
    return -1;
  else return i;
}

int VMachine::new_temp_copy(int j) {
  int i = new_temp_copy();
  if(i>=0) str[i]->assign(*str[j]);
  return i;
}

int VMachine::new_temp_copy(char *s) {
  int i = new_temp_copy();
  if(i>=0) str[i]->assign(s);
  return i;
}

void VMachine::del_temp_copy(int i) {
  if(str[i] != NULL)  { delete str[i]; str[i] = NULL; }
}

