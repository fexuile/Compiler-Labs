#pragma once
#include <cstdio>
#include <string>
#include <cassert>
#include <iostream>
#include <memory>
using namespace std;

class BaseAST { 
public:
    virtual ~BaseAST() = default;
    virtual void dump() const = 0;
};

class CompUnitAST : public BaseAST {
public:
    unique_ptr<BaseAST> funcdef;
    void dump() const;
};

class FuncDefAST : public BaseAST {
public:
    unique_ptr<BaseAST> type;
    string name;
    unique_ptr<BaseAST> code;
    void dump() const;
};

class FuncTypeAST : public BaseAST {
public:
    string type;
    void dump() const;
};

class BlockAST : public BaseAST {
public:
    unique_ptr<BaseAST> stmt;
    void dump() const;
};

class StmtAST : public BaseAST {
public:
    int number;
    void dump() const;
};

class ExpAST : public BaseAST {
public:
    unique_ptr<BaseAST> UnaryExp;
    void dump() const;
};

class PrimaryExpAST : public BaseAST {
public:
union {
    int number;
    unique_ptr<BaseAST> exp;
}content;
    void dump() const;
};

class UnaryExpAST : public BaseAST {
public:
    unique_ptr<BaseAST> UnaryOp;
    unique_ptr<BaseAST> UnaryExp;
    unique_ptr<BaseAST> PrimaryExp;
    void dump() const;
};

class UnaryOpAST : public BaseAST {
public:
enum class UnaryOpType {
    PLUS,
    MINUS,
    NOT
};  
    UnaryOpType type;
    void dump() const;
};