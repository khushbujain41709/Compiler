#ifndef LEXER_H
#define LEXER_H
// This is part of a header guard, a common pattern in C++ header files to prevent multiple inclusions of the same file.
// A header guard ensures that the contents of a header file are included only once, even if it's included multiple times (directly or indirectly) in other files.
#include <string>
#include <vector>
using namespace std;
enum TokenType { NUMBER, VARIABLE, OPERATOR, CUSTOM, LPAREN, RPAREN, ASSIGN, FUNC, END };

struct Token {
    TokenType type;
    string value;
};

vector<Token> tokenize(const string& code);
#endif