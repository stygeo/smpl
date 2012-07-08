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

extern SymTab st;
extern IntInstr *intcode;

// Read a program
// TODO: Disc from compiler
void VMachine::read()   {
  int i = 0;

  SymDesc *s = st.get_first();
  while(s != NULL) {
    // Content not empty, string constant
    if(s->cont != NULL) {
      str[i] = new String(s->cont);
    } else { // Boolean
      str[i] = new String();
    }
    // Set the number so we can find it back (TODO, don't use indices,
    // but pointers instead.
    s->set_no(i);
    i++;
    s = st.get_next();
  }

  ninstr = intcode->len();
  instr  = new Instr[ninstr];
  IntInstr *cinstr = intcode;
  for(i = 0; i < ninstr; i++) {
    switch(cinstr->opcode) {
      case OP_NOP:              // No operation
        instr[i] = Instr(OP_NOP, 0);
        break;
      case OP_PUSH:             // push string [var]
        instr[i] = Instr(OP_PUSH, cinstr->str->get_no());
        break;
      case OP_GETTOP:           // get string from top of stack (=assign) [var]
        instr[i] = Instr(OP_GETTOP, cinstr->str->get_no());
        break;
      case OP_DISCARD:          // discard top value from the stack
        instr[i] = Instr(OP_DISCARD);
        break;
      case OP_PRINT:            // print a string
        instr[i] = Instr(OP_PRINT);
        break;
      case OP_INPUT:            // input a string [var]
        instr[i] = Instr(OP_INPUT, cinstr->str->get_no());
        break;
      case OP_JMP:              // unconditional jump [dest]
        instr[i] = Instr(OP_JMP, cinstr->target->n - i);
        break;
      case OP_JMPF:             // jump if false [dest]
        instr[i] = Instr(OP_JMPF, cinstr->target->n - i);
        break;
      case OP_STR_EQUAL:        // test whether two strings are equal
        instr[i] = Instr(OP_STR_EQUAL);
        break;
      case OP_BOOL_EQUAL:       // test whether two bools are equal
        instr[i] = Instr(OP_BOOL_EQUAL);
        break;
      case OP_CONCAT:           // concatinate two strings
        instr[i] = Instr(OP_CONCAT);
        break;
      case OP_BOOL2STR:
        instr[i] = Instr(OP_BOOL2STR);
        break;
      case JUMPTARGET:
        instr[i] = Instr(OP_NOP);
        break;
    }
    cinstr = cinstr->next;
  }
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

