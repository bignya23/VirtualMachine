grammar VM;

program         : instruction+ EOF ;        // Program consists of multiple instructions
instruction     : arithmetic
                | stack
                | memory
                | control
                | io
                | HALT ;

arithmetic      : ADD | SUB | MUL | DIV ;   // Arithmetic operations
stack           : PUSH value | POP ;  //DONE  // Stack operations
memory          : LOAD identifier | STORE identifier ; //DONE // Memory operations
control         : JMP label
                | JZ label
                | JNZ label ;               // Control flow
io              : PRINT (STRING | identifier | EMPTY) ; //DONE // Print a string or variable
HALT            : 'HALT' ;                 // Halt program execution

value           : INT ;                    // Integer value for PUSH
identifier      : ID ;                     // Variable name
label           : ID ':' ;                 // Label for jumps

// Tokens
ADD             : 'ADD' ;
SUB             : 'SUB' ;
MUL             : 'MUL' ;
DIV             : 'DIV' ;
PUSH            : 'PUSH' ;
POP             : 'POP' ;
LOAD            : 'LOAD' ;
STORE           : 'STORE' ;
JMP             : 'JMP' ;
JZ              : 'JZ' ;
JNZ             : 'JNZ' ;
PRINT           : 'PRINT' ;
STRING          : '"' (~["])* '"' ;        // Double-quoted string
ID              : [a-zA-Z_][a-zA-Z0-9_]* ;// Identifier for variables/labels
INT             : [0-9]+ ;                 // Integer values

// Ignore whitespace and comments
WS              : [ \t\r\n]+ -> skip ;     // Skip whitespace
COMMENT         : '#' ~[\r\n]* -> skip ;   // Skip single-line comments
