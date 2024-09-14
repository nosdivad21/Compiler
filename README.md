# Compiler
This is a compiler built for my compiler class that takes code and breaks it down to assembly. 
It is capable of compiling functions, recursive functions, ifs, whiles, nested ifs and while, and all arithmetic operations. 
Scanner.cpp reads the code and breaks it down into tokens, SymbolTable.cpp populates the the symbol table needed for PDA operations.
PDA.cpp does all push down automata operations, running through the tokens and using the precedence table to compile to assembly.
Assembly to machine code was out of the scope of this class so the machine code was run on a linux vm for testing purposes.
