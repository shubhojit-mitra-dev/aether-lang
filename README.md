# Aether

Aether is a **personal learning project** focused on **applied compiler design**, built incrementally in **C**.

The goal of this project is to understand how a compiler is constructed from first principles by **actually building one**, step by step, rather than relying on abstractions or frameworks.

At the moment, the project is intentionally **minimal** and exploratory.

---

## Current State

* Single source file: `main.c`
* Basic lexer implementation
* Reads a `.ae` source file
* Tokenizes simple constructs (keywords, numbers, symbols)
* Prints tokens for inspection and debugging

There is **no parser, AST, or code generation yet**.

---

## Example

Input (`test.ae`):

```c
exit(100);
```

Current lexer output:

```
EXIT
OPEN_PAREN
NUMBER(100)
CLOSE_PAREN
SEMICOLON
```

This output is meant purely for learning and verification while developing the lexer.

---

## Learning Roadmap

1. Lexical analysis
2. Parsing and AST construction
3. Arithmetic expressions
4. Assembly code generation
5. Variables and scopes
6. Stack management
7. Control flow (`if`, `while`)
8. Console output
9. Compiling simple programs

---

## Motivation

This project exists to:

* Learn how real compilers work internally
* Practice systems programming in C
* Build intuition around lexing, parsing, and code generation
* Gain hands-on experience before moving to more advanced compiler work

There are **no ambitions yet** beyond learning and experimentation.

---

## Status

🚧 **Work in progress**

The code is expected to be rewritten, refactored, and broken frequently as understanding improves.


