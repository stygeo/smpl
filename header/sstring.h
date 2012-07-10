#pragma once

#include <string.h>
#include <iostream.h>

// Extremely simple string class
class String {
public:
   String()   {s = new char [1]; s[0] = 0;}
   String(char *_s)  {s = new char [1]; s[0] = 0; assign (_s);}
   ~String()  {delete[] s;}
   char *val ()   {return s;}
   int   len ()   {return strlen(s);}
   void  assign (String &n)   {int l; delete[] s; l = n.len(); s = new char[l+1]; strcpy (s, n.val());}
   void  assign (char *n)     {int l; delete[] s; l = strlen(n); s = new char[l+1]; strcpy (s, n);}
   void  concatenate (String &n)   {
      int nl = len() + n.len();
      char *t = new char [nl + 1];
      strcpy (t, s); strcat (t, n.val());
      delete[] s; s = t;
   }
   void  concatenate (char *n)   {
      String t; t.assign (n); concatenate(t);
   }
   void print ()   {cout << s;}
   void input ()   {delete[]s; s = new char[81]; cin.getline(s,80);}
private:
   char *s;
};

