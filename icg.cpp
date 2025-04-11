#include "icg.h"
#include <sstream>
#include <string>
#include <vector>
#include <functional>
using namespace std;

vector<string> generate3AC(Node* root) {
    vector<string> code;
    int tempCount = 1;

    function<string(Node*)> visit = [&](Node* node) -> string {
        if (!node) return "";

        if (node->value == ";"){
            visit(node->left);
            return visit(node->right);
        }
        
        // Handle leaf nodes
        if (!node->left && !node->right) {
            return node->value;
        }

        // Handle function definition e(x) = ...
        if (node->value == "=" && node->left->value == "e"){
            string expr = visit(node->right);
            return expr;
        }

        // Handle KHUS operation
        if (node->value == "KHUS") {
            string x = visit(node->left);
            string y = visit(node->right->left);
            string z = visit(node->right->right);
            
            // Compute y^3
            string t1 = "t" + to_string(tempCount++);
            string t2 = "t" + to_string(tempCount++);
            code.push_back(t1 + " = " + y + " * " + y);
            code.push_back(t2 + " = " + t1 + " * " + y);
            
            // Compute both possibilities
            string t3 = "t" + to_string(tempCount++);
            string t4 = "t" + to_string(tempCount++);
            code.push_back(t3 + " = " + x + " + " + t2);
            code.push_back(t4 + " = " + x + " - " + t2);
            
            // Select result
            string t6 = "t" + to_string(tempCount++);
            return t6;
        }

        // Handle binary operations
        string left = visit(node->left);
        string right = visit(node->right);
        string temp = "t" + to_string(tempCount++);
        code.push_back(temp + " = " + left + " " + node->value + " " + right);
        return temp;
    };

    if (root) {
        visit(root);
    }    
    return code;
}