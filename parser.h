#ifndef PARSER_H
#define PARSER_H
#include "lexer.h"
using namespace std;
struct Node {
    string value;
    Node* left;
    Node* right;
};

Node* parse(const vector<Token>& tokens);
#endif