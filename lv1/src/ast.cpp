#include "include/ast.hpp"
#include <iostream>
using namespace std;
string mode;

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
        cout << "%entry:\n";
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