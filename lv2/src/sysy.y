%code requires {
#include <memory>
#include <string>
#include "include/ast.hpp"
}

%{
#include <iostream>
#include <string>
#include <memory>
#include "include/ast.hpp"
int yylex();
void yyerror(std::unique_ptr<BaseAST>&ast, const char *s);

using namespace std;
extern int yylineno;
extern char *yytext;
%}

%parse-param {std::unique_ptr<BaseAST>&ast}
%union{
    std::string *str_val;
    int int_val;
    BaseAST *ast_val;
}

%token INT RETURN
%token <int_val> INT_CONST
%token <str_val> IDENT

%type <ast_val> FuncDef FuncType Block Stmt

%%

CompUnit : FuncDef{
    auto comp_unit = make_unique<CompUnitAST>();
    comp_unit->funcdef = std::unique_ptr<BaseAST>($1);
    ast = move(comp_unit);
};

FuncDef : FuncType IDENT '(' ')' Block {
    auto ast = new FuncDefAST();
    ast->type = std::unique_ptr<BaseAST>($1);
    ast->name = *std::unique_ptr<std::string>($2);
    ast->code = std::unique_ptr<BaseAST>($5);
    $$ = ast;
};

FuncType : INT {
    auto ast = new FuncTypeAST();
    ast->type = "int";
    $$ = ast;
};

Block : '{' Stmt '}'{
    auto ast = new BlockAST();
    ast->stmt = std::unique_ptr<BaseAST>($2);
    $$ = ast;
};

Stmt : RETURN INT_CONST ';'{ 
    auto ast = new StmtAST();
    ast->number = ($2);
    $$ = ast;
}

%%

void yyerror(std::unique_ptr<BaseAST>&ast, const char *s) {
    cerr << "error at line " << yylineno << ": " << s << " at token " << yytext <<endl;
}