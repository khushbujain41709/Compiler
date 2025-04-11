#include "parser.h"
#include <stack>
#include <map>
#include <stdexcept>
using namespace std;
int precedence(const string& op) {
    if (op == "^") return 3;
    if (op == "*" || op == "/") return 2;
    if (op == "+" || op == "-") return 1;
    return 0;
}

Node* parseExpression(const vector<Token>& tokens, size_t start, size_t end);

Node* parse(const vector<Token>& tokens) {
    // Find if there's a KHUS expression
    size_t khus_pos = tokens.size();
    for (size_t i = 0; i < tokens.size(); i++) {
        if (tokens[i].type == CUSTOM && tokens[i].value == "KHUS") {
            khus_pos = i;
            break;
        }
    }

    // Parse the function definition (first part)
    vector<Token> funcTokens(tokens.begin(), tokens.begin() + khus_pos);
    Node* funcTree = parseExpression(funcTokens, 0, funcTokens.size());

    // If there's a KHUS expression, parse it separately
    if (khus_pos < tokens.size()) {
        vector<Token> khusTokens(tokens.begin() + khus_pos, tokens.end());
        Node* khusTree = parseExpression(khusTokens, 0, khusTokens.size());
        return new Node{";", funcTree, khusTree};  // Separate with semicolon
        // root node is ; then uske left tree mei funcTree hai aur right tree mei khusTree hai
    }

    return funcTree;
}

Node* parseExpression(const vector<Token>& tokens, size_t start, size_t end) {
    stack<Node*> operands;
    stack<string> operators;

    // Handle function definition
    if (end - start > 5 &&
        tokens[start].type == FUNC &&
        tokens[start+1].type == LPAREN &&
        tokens[start+2].type == VARIABLE &&
        tokens[start+3].type == RPAREN &&
        tokens[start+4].type == ASSIGN) {
        // e(x) = 
        
        Node* funcNode = new Node{tokens[start].value, nullptr, 
                                 new Node{tokens[start+2].value, nullptr, nullptr}};
        Node* exprTree = parseExpression(tokens, start+5, end);
        return new Node{"=", funcNode, exprTree};
        // root node is = then uske left tree mei funcTree hai aur right tree mei exprTree hai
    }

    for (size_t i = start; i < end; ++i){
        const Token& tok = tokens[i];
        if (tok.type == NUMBER || tok.type == VARIABLE) {
            operands.push(new Node{tok.value, nullptr, nullptr});
            // agar number ya variable hai toh operands stack mei daalna hai
        }
        else if (tok.type == OPERATOR) {
            while (!operators.empty() && precedence(operators.top()) >= precedence(tok.value)){
                // if top is * and tok is + 
                Node* right = operands.top(); operands.pop(); // 5
                Node* left = operands.top(); operands.pop(); // x
                operands.push(new Node{operators.top(), left, right});  // * , x , 5
                operators.pop(); // pop *
            }
            operators.push(tok.value);
        }
        else if (tok.type == CUSTOM && tok.value == "KHUS") {
            // KHUS x y z
            if (i + 3 >= end || 
                tokens[i+1].type != VARIABLE ||
                tokens[i+2].type != VARIABLE ||
                tokens[i+3].type != VARIABLE) {
                throw runtime_error("Invalid KHUS syntax");
            }
            
            Node* x = new Node{tokens[i+1].value, nullptr, nullptr};
            Node* y = new Node{tokens[i+2].value, nullptr, nullptr};
            Node* z = new Node{tokens[i+3].value, nullptr, nullptr};
            
            // Create KHUS operation node
            Node* commaNode = new Node{",", y, z};
            operands.push(new Node{"KHUS", x, commaNode});
            i += 3;  // Skip x, y, z
        }
        else if (tok.type == LPAREN) {
            // Handle parentheses by finding matching RPAREN
            int paren_count = 1;
            size_t j = i + 1;
            while (j < end && paren_count > 0) {
                if (tokens[j].type == LPAREN) paren_count++;
                else if (tokens[j].type == RPAREN) paren_count--;
                j++;
            }
            if (paren_count != 0) throw runtime_error("Mismatched parentheses");
            
            // It parses the subexpression between ( and ) which lies between indices i+1 and j-1
            Node* subExpr = parseExpression(tokens, i+1, j-1);
            operands.push(subExpr);
            i = j - 1;
        }
    }

    while (!operators.empty()) {
        Node* right = operands.top(); operands.pop();
        Node* left = operands.top(); operands.pop();
        operands.push(new Node{operators.top(), left, right});
        operators.pop();
    }
    /*

    e(x) = x + 5; KHUS a b c
       ;
     /  \
    =    KHUS
   / \   /|\
  e   +  a b c
     / \
    x   5

    */

    return operands.empty() ? nullptr : operands.top();
}