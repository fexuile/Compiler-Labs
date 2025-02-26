#include <iostream>
#include <string>
#include <cassert>
#include <cstring>
#include "visit.hpp"
#include "koopa.h"
using namespace std;

void Visit(const koopa_raw_program_t &program)
{
    cout << "  .text" << endl;
    cout << "  .globl main" << endl;
    Visit(program.values);
    Visit(program.funcs);
}

void Visit(const koopa_raw_slice_t &slice)
{
    // cout << "slice" << endl;
    for (size_t i = 0; i < slice.len; ++i)
    {
        auto ptr = slice.buffer[i];
        switch (slice.kind) {
            case KOOPA_RSIK_FUNCTION:
                Visit(reinterpret_cast<koopa_raw_function_t>(ptr));
                break;
            case KOOPA_RSIK_BASIC_BLOCK:
                Visit(reinterpret_cast<koopa_raw_basic_block_t>(ptr));
                break;
            case KOOPA_RSIK_VALUE:
                Visit(reinterpret_cast<koopa_raw_value_t>(ptr));
                break;
            default:
                assert(0);
                break;
        }
    }
}

void Visit(const koopa_raw_function_t &func)
{
    for(int i = 1; i < strlen(func->name); i++) cout << func->name[i];
    cout << ":" << endl;
    Visit(func->bbs);
}

// Basic Block
void Visit(const koopa_raw_basic_block_t &bb)
{
    Visit(bb->insts);
}

// Instrutions
void Visit(const koopa_raw_value_t &value)
{
    const auto &kind = value->kind;
    switch (kind.tag)
    {
    case KOOPA_RVT_RETURN:
        Visit(kind.data.ret);
        break;
    case KOOPA_RVT_INTEGER:
        Visit(kind.data.integer);
        break;
    default:
        assert(false);
        break;
    }
}

// Return Inst
void Visit(const koopa_raw_return_t ret)
{
    Visit(ret.value);
    std::cout << "  ret" << endl;
}

//Interger Inst
void Visit(koopa_raw_integer_t integer)
{
    std::cout << "  li  a0, " << integer.value << endl;
}