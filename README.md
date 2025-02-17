# Virtual Assembly VM

## Overview

Virtual Assembly VM is a custom virtual machine that replicates assembly-like functionality without using registers. Instead, it relies on a stack and memory-based approach. The VM introduces labels for control flow, making it easier to work with structured execution.

## Features

- **Arithmetic Operations**: Supports addition, subtraction, multiplication, and division.
- **Stack Operations**: Push and pop values to/from the stack.
- **Memory Operations**: Load and store values.
- **Control Flow**: Jump and conditional jump instructions with label-based addressing.
- **Input/Output**: Print variables, strings, or read user input.
- **Halt Execution**: Explicitly stop program execution.

## Grammar

The VM's grammar is defined as follows:

### Program Structure

```
program         : instruction+ EOF ;
instruction     : arithmetic
                | stack
                | memory
                | control
                | io
                | HALT ;
```

### Instructions

- **Arithmetic**
  ```
  (INCREASE | DECREASE) identifier
  (ADD | SUB | MUL | DIV) (identifier + identifier | identifier + value | value + value)
  ```
- **Stack**
  ```
  PUSH value
  POP
  ```
- **Memory**
  ```
  LOAD identifier
  STORE identifier
  ```
- **Control Flow**
  ```
  JMP label
  JZ label
  JNZ label
  ```
- **Input/Output**
  ```
  PRINT (STRING | identifier | EMPTY)
  INPUT identifier
  ```
- **Halting Execution**
  ```
  HALT
  ```

### Tokens

```
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
INPUT           : 'INPUT' ;
INCREASE        : 'INC' ;
DECREASE        : 'DEC' ;
HALT            : 'HALT' ;
EXPRESSION      : 'EXPRESSION' ;
STRING          : '"' (~[""'])* '"' ;
ID              : [a-zA-Z_][a-zA-Z0-9_]* ;
INT             : [0-9]+ ;
WS              : [ \t\r\n]+ -> skip ;
COMMENT         : '#' ~[\r\n]* -> skip ;
```

## Example Code

```assembly
print "welcome"
push 20
store y
push 10
store x
inc x
jmp printx
print

printx:
    print x
    load x
    store result
    print result
```

## Installation

1. Clone the repository:
   ```sh
   git clone https://github.com/bignya23/virtualmachine.git
   cd virtualmachine
   ```
2. Build the project using CMake:
   ```sh
   mkdir build && cd build
   cmake ..
   make
   ```
3. Run the VM with an example program:
   ```sh
   ./vm.exe/test.masm
   ```

## Future Enhancements

- Implement more complex expressions.
- Add support for function calls and loops.
- Introduce debugging tools.

## Contributing

Contributions are welcome! Feel free to fork the repository, open issues, and submit pull requests.

## License

This project is licensed under the MIT License.

