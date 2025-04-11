# Compiler Project

Name - Khushbu Jain<br>
Roll Number - 23115047<br>
Branch - CSE 4th Semester<br>
Github Link - https://github.com/khushbujain41709/Compiler.git

This is a simple custom compiler built in C++ for parsing expressions and generating simulated assembly code.<br>
I am using the Taylor series expansion of the exponential function e^x to compute its value using assembly. The equation implemented is : <br>
e(x) = 1 + x + x^2/2 + x^3/6 + x^4/24<br>
This approximation includes the first five terms of the Taylor series.<br>
The Taylor series is a powerful mathematical tool used to approximate functions as an infinite sum of their derivatives at a single point (usually around x = 0, called a Maclaurin series).

The KHUS operation(Custom Insruction) implements the following logic :<br>
It takes three variables (x, y, z) as input<br>
Computes y³ (y cubed) by multiplying yyy<br>
Then performs either :<br>
If z is positive: returns x + y³<br>
If z is negative: returns x - y³

## Features

- **Lexical Analysis**: Tokenizes input expressions
- **Parsing**: Builds Abstract Syntax Trees (AST)
- **Semantic Analysis**: Checks for division by zero
- **Intermediate Code Generation**: Produces Three-Address Code (3AC)
- **Assembly Generation**: Outputs x86 assembly (NASM syntax)

## Prerequisites

- GCC/G++ (MinGW on Windows)
- NASM (Netwide Assembler)
- GNU Linker (ld) or MinGW linker

## Installation

1. Install NASM on Windows:
   ```bash
   winget install nasm

## Usage
Run these commands in command prompt where in the same directory where all files are located.
```bash
g++ main.cpp lexer.cpp parser.cpp semantic.cpp icg.cpp codegen.cpp -o compiler
./compiler
nasm -f win32 output.asm -o output.obj 
gcc output.obj -o output.exe -nostdlib -e _start
type output.asm
objdump -d -M intel output.exe
objdump -d -M intel output.obj
```
## Build and Execution Commands

| Command | Description |
|---------|-------------|
| `g++ main.cpp lexer.cpp parser.cpp semantic.cpp icg.cpp codegen.cpp -o compiler` | Compiles all C++ source files into a `compiler` executable that processes mathematical expressions |
| `./compiler` | Runs the compiler to transform `input.txt` into x86 assembly (`output.asm`) |
| `nasm -f win32 output.asm -o output.obj` | Assembles the code into a Windows 32-bit object file (`output.obj`) |
| `gcc output.obj -o output.exe -nostdlib -e _start` | Links the object file into a minimal Windows executable |
| `type output.asm` | Displays the generated assembly code |
| `objdump -d -M intel output.exe` | Shows disassembled machine code of the final executable (Intel syntax) |
| `objdump -d -M intel output.obj` | Disassembles the intermediate object file for debugging |

## Output
Assembly instructions will be written to `output.asm`<br>
Whole output is written in `mainOutput.txt`
