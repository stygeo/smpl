#pragma once

#include <stdlib.h>

// Link class used to construct the stack
template<class t>
class ll_link {
  public:
    t       data;
    ll_link *next;
};

// Stack class
template<class t>
class Stack {
  public:
    Stack()     { llstart = NULL; n = 0; }
    ~Stack()    { empty(); }
    void empty();             // make empty stack
    void push(t node);        // push item on stack
    t pop();                  // pop item from stack
    inline t get_top()        { return llstart->data; }
    t get_no(int e);          // get item no. n from stack
    void do_for_all(void(*process)(t));
    void do_for_all_arg(void(*process)(t,void*), void *arg);
    inline int len()          { return n; }
    inline bool is_empty()    { return n == 0; }
//    friend inline void operator << (Stack<t> &stack, t node);   // =Push
//    friend inline t operator << (t &node, Stack<t>);              // =Pop
  private:
    ll_link<t> *llstart;      // Start list< last in >
    int n;                    // Number of links
};

template<class t>
void Stack<t>::empty ()  {
   ll_link<t> *search, *del;

   search = llstart;
   while (search != NULL)    {
      del = search;
      search = search->next;
      delete del;
   }
   llstart = NULL; n = 0;
}

template<class t>
void Stack<t>::do_for_all(void(*process)(t)) {
  ll_link<t> *search;

  search = llstart;
  while(search != NULL) {
    process(search->data);
    search = search->next;
  }
}

template<class t>
void Stack<t>::do_for_all_arg(void(*process)(t, void*), void *arg) {
  ll_link<t> *search;

  search = llstart;
  while(search != NULL) {
    process(search->data, arg);
    search = search->next;
  }
}

template<class t>
t Stack<t>::pop() {
  t rv; ll_link<t> *del;

  rv = llstart->data;
  del = llstart;
  llstart = llstart->next; n--;

  delete del;

  return rv;
}

//template<class t>
//inline void Stack<t>::operator<<(Stack<t> &stack, t node) {
//  stack.push(t);
//}

//template<class t>
//inline void Stack<t>::operator<<(t &node, Stack<t> &stack) {
//  t = stack.pop();
//}

template<class t>
t Stack<t>::get_no(int e) {
  int i;
  ll_link<t> *link;

  link = llstart;
  i = n - e - 1;
  while(i > 0) { link = link->next; i--;}

  return link->data;
}

template<class t>
void Stack<t>::push(t node) {
  ll_link<t> *new_link;

  new_link = (ll_link<t>*)malloc(sizeof(ll_link<t>));
  new_link->data = node;
  new_link->next = llstart;
  llstart = new_link;
  n++;
}

