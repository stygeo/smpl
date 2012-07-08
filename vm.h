#pragma once

#include "stack.h"
#include "sstring.h"
#include "intcode.h"

class Instr {
  public:
    Instr()     { opcode = OP_NOP; operand = 0; }
    Instr(Opcode _opcode)    { opcode = _opcode; operand = 0; }
    Instr(Opcode _opcode, int _operand)    { opcode = _opcode; operand = _operand; }

    Opcode    opcode;     // the opcode
    int       operand;    // string number or target instruction
};

// some defines and consts.
// Hacky
// TODO real stack pointers
typedef Stack<int> VM_stack; // <  0 : boolean
                             // >= 0 : index to string

const int ST_TRUE  = -1,     // Stack codes for true/false
          ST_FALSE = -2;

const int MAX_STR = 100;     // Max num of strings in mem (incl. temp)

// Virtual machine
class VMachine {
  public:
    VMachine();
    ~VMachine();
    void read();
    void execute();
    void reset();
  private:
    // TODO real stack pointers
    int new_temp_copy();
    int new_temp_copy(int j);   // String
    int new_temp_copy(char *s); // boolean
    void del_temp_copy(int i);

    Instr *instr;     // The instructions.
    int    ninstr;    // Num. of instructions.
    String *str[MAX_STR]; // the string table (NULL=entry not used)
    VM_stack stack;   // The stack
};

