#pragma once

#include <iostream.h>
#include <string.h>

enum SymType   {
  STR_VAR,    // String variable
  STR_CONST,  // String constant
};

class SymDesc {
  public:
    SymDesc (char *_name, SymType _type, char *_cont, int _line);
    ~SymDesc ();
    void show ();
    void set_no(int n) {no=n;}
    int  get_no() {return no;}
    int no;

    char    *name;   // name of the symbol
    char    *cont;   // contents (if string constant)
    SymType  type;   // type of the symbol
    int      line;   // line it was first encountered
    SymDesc *next;   // next symbol in list
};

class SymTab  {
  public:
    SymTab();
    ~SymTab();
    bool add (SymDesc *symb);
    SymDesc *find (char *name);
    void show ();
    SymDesc *get_first()   { current = start; return current; }
    SymDesc *get_next() {
      if(current != NULL)
        current = current->next;
      return current;
    }

  private:
    SymDesc *start;
    SymDesc *current;
};
