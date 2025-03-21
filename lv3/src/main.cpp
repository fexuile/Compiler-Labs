#include <cstdio>
#include <string>
#include <cassert>
#include <iostream>
#include <memory>
#include <cstring>
#include "include/ast.hpp"
#include "include/visit.hpp"
#include "koopa.h"
using namespace std;

extern FILE *yyin;
extern FILE *yyout;
extern string mode;
extern int yyparse(unique_ptr<BaseAST> &ast);

char *str;

void do_riscv() {
    // 解析字符串 str, 得到 Koopa IR 程序
    koopa_program_t program;
    koopa_error_code_t ret = koopa_parse_from_string(str, &program);
    assert(ret == KOOPA_EC_SUCCESS);  // 确保解析时没有出错
    // 创建一个 raw program builder, 用来构建 raw program
    koopa_raw_program_builder_t builder = koopa_new_raw_program_builder();
    // 将 Koopa IR 程序转换为 raw program
    koopa_raw_program_t raw = koopa_build_raw_program(builder, program);
    // 释放 Koopa IR 程序占用的内存
    koopa_delete_program(program);

    // 处理raw
    Visit(raw);

    // 处理完成, 释放 raw program builder 占用的内存
    // 注意, raw program 中所有的指针指向的内存均为 raw program builder 的内存
    // 所以不要在 raw program 处理完毕之前释放 builder
    koopa_delete_raw_program_builder(builder);

    free(str);
}

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

    str = new char[5000];
    freopen(output, "w", stdout);
    ast->dump();

    if(mode == "-riscv") do_riscv();
    fclose(stdout);
    
    return 0;
}