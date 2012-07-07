// Union to pass information between lexer and caller
typedef union {
   char *str;
} YYSTYPE;

extern YYSTYPE yylval;

// Lexer constants
enum {
   UNUSED = 257,  // start above 256 (we can also return actual chars)
   ERROR_TOKEN, // returned if illegal character found
   IF,
   ELSE,
   PRINT,
   INPUT,
   ASSIGN,     // assign
   EQUAL,      // test if equal
   CONCAT,     // string-concatenate
   END_STMT,   // end of statement
   OPEN_PAR,   // opening parenthesis
   CLOSE_PAR,  // closing parenthesis
   BEGIN_CS,   // begin compound statement
   END_CS,     // end   compound statement
   ID,         // identifier
   STRING      // string constant
};
