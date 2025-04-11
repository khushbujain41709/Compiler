#include <iostream>
#include <fstream>
#include <vector>
#include "lexer.h"
#include "parser.h"
#include "semantic.h"
#include "icg.h"
#include "codegen.h"
using namespace std;

int main() {
    // 1. Read input file
    ifstream infile("C://Users//khushbu//OneDrive//Desktop//Compiler//compiler//input.txt");
    if (!infile){
        cerr << "Error: Cannot open input.txt\n";
        return 1;
    }

    string code((istreambuf_iterator<char>(infile)), istreambuf_iterator<char>());
    infile.close();
    cout << "Input file read successfully.\n";

    // 2. Lexical analysis
    vector<Token> tokens = tokenize(code);
    if (tokens.empty()) {
        cerr << "Error: No tokens generated\n";
        return 1;
    }
    cout<<"Tokens (" << tokens.size()<<") :\n";
    for(const auto& t : tokens){
        cout<<"Type : "<<t.type<<", Value : "<<t.value<<"\n";
    }
    cout << "Lexical analysis completed. Tokens : " << tokens.size() << "\n";

    // 3. Parsing
    Node* ast = parse(tokens);
    if (!ast) {
        cerr << "Error: Parser failed\n";
        return 1;
    }
    cout << "Parsing successful.\n";

    // 4. Semantic analysis
    try{
        semanticCheck(ast);
        cout << "Semantic analysis passed.\n";
    }
    catch (const exception& e){
        cerr << "Semantic Error : " << e.what() << "\n";
        return 1;
    }

    // 5. Intermediate code generation
    vector<string> tac = generate3AC(ast);
    if (tac.empty()){
        cerr << "Error: No intermediate code generated\n";
        return 1;
    }
    for(const auto& line : tac){
        cout<<line<<"\n";
    }
    cout << "3-address code (TAC) generation completed.\n";

    // 6. Generate assembly output
    string outputPath = "C://Users//khushbu//OneDrive//Desktop//Compiler//compiler//output.asm";
    ofstream asmfile(outputPath);
    if (!asmfile) {
        cerr << "Error: Cannot create output.asm\n";
        return 1;
    }

    generateAssembly(tac, asmfile);
    asmfile.close();
    cout << "Assembly code written to output.asm\n";

    // 7. Verify output
    ifstream check(outputPath);
    if (!check) {
        cerr << "Error: Output file not found\n";
        return 1;
    }
    check.close();

    cout << "Successfully created output.txt\n";
    return 0;
}
