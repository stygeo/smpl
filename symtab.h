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

private:
   SymDesc *start;
};
