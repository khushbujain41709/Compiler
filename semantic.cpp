#include "semantic.h"
#include <iostream>
#include <unordered_set>
using namespace std;
void collectDeclaredVariables(Node* node, unordered_set<string>& declared) {
    if (!node) return;

    if (node->value == ";") {
        collectDeclaredVariables(node->left, declared);
        collectDeclaredVariables(node->right, declared);
        return;
    }

    // If it's a function assignment like e(x) = ..., declare x
    if (node->value == "=" && node->left && node->left->right) { // node->left = e and node->left->right = x
        declared.insert(node->left->right->value);  // x in e(x)
    }
    // If it's a KHUS operation, declare all its variables
    else if (node->value == "KHUS") {
        if (node->left) declared.insert(node->left->value);  // x
        if (node->right && node->right->value == ",") {
            if (node->right->left) declared.insert(node->right->left->value);  // y
            if (node->right->right) declared.insert(node->right->right->value);  // z
        }
    }

    collectDeclaredVariables(node->left, declared);
    collectDeclaredVariables(node->right, declared);
}

void checkSemanticErrors(Node* node, const unordered_set<string>& declared) {
    if (!node) return;

    // Check for division by zero
    if (node->value == "/" && node->right && node->right->value == "0") {
        cerr << "Semantic Error: Division by zero." << endl;
        exit(1);
    }

    // Check for variable usage without declaration 
    // If the node is a leaf and its value starts with a letter → it's likely a variable.
    if (!node->left && !node->right && isalpha(node->value[0])) { 
        if (declared.find(node->value) == declared.end()){ // Is the variable in the declared set?
            cerr << "Semantic Error: Undeclared variable used -> " << node->value << endl;
            exit(1);
        }
    }

    // ... in checkSemanticErrors function
    if (node->value == "KHUS") {
        if (!node->left || !node->right || node->right->value != "," || !node->right->left || !node->right->right) {
            throw runtime_error("Invalid KHUS operation structure");
        }
    }

    checkSemanticErrors(node->left, declared);
    checkSemanticErrors(node->right, declared);
}

void semanticCheck(Node* root) {
    unordered_set<string> declared;
    collectDeclaredVariables(root, declared);
    checkSemanticErrors(root, declared);
}
