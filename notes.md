== Symbol table ==
* Binary tree/hash table instead of a linear table.
* Note that a more advanced compiler would probably let the
  lexer store and retrieve identifiers. This is because in a
  complex language there are many different meanings identifiers
  can have: variables, functions, types, etc. The lexer could
  retrieve the identifier description and directly return the
  appropriate token to the parser. Since our identifiers are
  always variables, I just let the parser handle them.

