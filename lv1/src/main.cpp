#include <cstdio>
#include <string>
#include <cassert>
#include <iostream>
#include <memory>
#include "include/ast.hpp"
using namespace std;

extern FILE *yyin;
extern FILE *yyout;
extern string mode;
extern int yyparse(unique_ptr<BaseAST> &ast);

int main(int argc, char *argv[]) {
    assert(argc == 5);
    mode = argv[1];
    auto input = argv[2];
    auto output = argv[4];

    yyin = fopen(input, "r");
    assert(yyin);

    unique_ptr<BaseAST> ast;
    auto ret = yyparse(ast);
    assert(ret == 0);
    
    freopen(output, "w", stdout);
    ast->dump();
    fclose(stdout);

    return 0;
}