#ifndef CODEGEN_H
#define CODEGEN_H
#include <vector>
#include <string>
#include <ostream>
using namespace std;
void generateAssembly(const vector<string>& tac, ostream& out);
#endif