#pragma once
#include <vector>

// The syntax tree node types
enum NodeType  {
  // Statements
  STMT_LIST,        // list of statements [left-part, right-part] (left-part may be another list)
  EMPTY_STMT,       // empty statement []
  EXPR_STMT,        // single expression as statement [expression]
  PRINT_STMT,       // print statement [expression]
  INPUT_STMT,       // input statement [variable]
  IFTHEN_STMT,      // if statement [cond, if-part]
  IFTHENELSE_STMT,  // if statement with else [cond, if-part, else-part]
  ERROR_STMT,       // error statement
  FUNC_STMT,        // function statement

  // Expressions
  EQUAL_EXPR,       // equality expression [op1, op2]
  ASSIGN_EXPR,      // assignment expression [variable, op2]
  CONCAT_EXPR,      // concatenation expression [op1, op2]
  IDENT_EXPR,       // identifier (link to symbol table)
  STR_EXPR,         // string constant (link to symbol table)

  COERCE_TO_STR     // Coerce to string (from boolean)
};

enum DataType {
  T_VOID,
  T_STRING,
  T_BOOL,
  T_ARGS
};

const int MXCHILD = 3;   // max. number of children a tree node can have

class SymDesc;

// The syntax tree node class
class TreeNode  {
  public:
    TreeNode (NodeType _type)   {type = _type;}
    TreeNode (NodeType _type, TreeNode *child1) {type = _type; child.push_back(child1);}
    TreeNode (NodeType _type, TreeNode *child1, TreeNode *child2) {type = _type; child.push_back(child1); child.push_back(child2);}
    TreeNode (NodeType _type, TreeNode *child1, TreeNode *child2, TreeNode *child3) {
      type = _type;
      child.push_back(child1); child.push_back(child2); child.push_back(child3);
    }
    void show ()  {show(0);}    // Show the tree contents
    void check();
    void append(TreeNode *_node) { child.push_back(_node); }
    int coerce_to_string(int childno);

    NodeType type;              // what type of node is it?
    SymDesc  *symbol;           // pointer to symbol, if applicable
    std::vector<TreeNode*>child; // pointers to childen
    //TreeNode *child[MXCHILD];   // pointers to children
    DataType rettype;          // the 'return' type of this node
  private:
    void show(int level);
};

typedef TreeNode *SyntTree;

class ArgList {
  public:
    void append(TreeNode *_node) { nodes.push_back(_node); }
  private:
    std::vector<TreeNode*> nodes;
};
