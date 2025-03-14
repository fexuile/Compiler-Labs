#include "ast.hpp"
#include "koopa.h"
#include <iostream>
using namespace std;
string mode;
int ID = 0;

void CompUnitAST::dump() const{
    if(mode == "-ast") {
        std::cout << "CompUnitAST { ";
        funcdef->dump();
        std::cout << " }\n";
    }
    else {
        funcdef->dump();
    }
}

void FuncDefAST::dump() const {
    if(mode == "-ast") {
        std::cout << "FuncDefAST { ";
        type->dump();
        std::cout << ", " << name << ", ";
        code->dump();
        cout << " }";
    }
    else {
        if (name != "main"){
            std::cerr << "error: function name != main\n";
            exit(1);
        }
        std::cout << "fun @" << name << "(): ";
        type->dump();
        std::cout << " {\n";
        code->dump();
        std::cout << "}\n";
    }
}

void FuncTypeAST::dump() const {
    if(mode == "-ast") {
        std::cout << "FuncTypeAST { " << type << " }";
    }
    else {
        if(type == "int") std::cout << "i32";
    }
}

void BlockAST::dump() const {
    if(mode == "-ast") {
        std::cout << "BlockAST { ";
        stmt->dump(); 
        std::cout << " }";
    }
    else {
        cout << "\%" << ID++ << ":\n";
        stmt->dump();
    }
}

void StmtAST::dump() const {
    if(mode == "-ast") {
        std::cout << "StmtAST { " << number << " }";
    }
    else {
        std::cout << "  ret " << number << "\n";
    }
}