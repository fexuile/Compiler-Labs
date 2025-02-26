#include "ast.hpp"
#include "koopa.h"
#include <iostream>
#include <string>
#include <cstring>
using namespace std;
string mode;
extern char *str;

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
    else if(mode == "-koopa") {
        if(name != "main") {
            std::cerr << "Error: only main function is supported\n";
            exit(1);
        }
        std::cout << "fun @" << name << "(): ";
        type->dump();
        std::cout << " {\n";
        code->dump();
        std::cout << "}\n";
    }
    else {
        str = strcat(str, ("fun @" + name + "(): ").c_str());
        type->dump();
        str = strcat(str, " {\n");
        code->dump();
        str = strcat(str, "}\n");
    }
}

void FuncTypeAST::dump() const {
    if(mode == "-ast") {
        std::cout << "FuncTypeAST { " << type << " }";
    }
    else if(mode == "-koopa") {
        if(type == "int") std::cout << "i32";
    }
    else {
        if(type == "int") str = strcat(str, "i32");
    }
}

void BlockAST::dump() const {
    if(mode == "-ast") {
        std::cout << "BlockAST { ";
        stmt->dump();
        std::cout << " }";
    }
    else if(mode == "-koopa") {
        cout << "%entry:\n";
        stmt->dump();
    }
    else {
        str = strcat(str, "%entry:\n");
        stmt->dump();
    }
}

void StmtAST::dump() const {
    if(mode == "-ast") {
        std::cout << "StmtAST { " << number << " }";
    }
    else if(mode == "-koopa") {
        std::cout << "  ret " << number << "\n";
    }
    else {
        str = strcat(str, ("  ret " + to_string(number) + "\n").c_str());
    }
}