%option noyywrap
%option nounput
%option noinput

%{
#include <cstdlib>
#include <string>
#include "sysy.tab.hpp"
using namespace std;
%}

WhiteSpace    [ \t\n\r]*
LineComment   "//".*
BlockComment \/\*[^*]*\*+([^/*][^*]*\*+)*\/
Indentifier [a-zA-Z_][a-zA-Z0-9_]*
Decimal [1-9][0-9]*
Octal 0[0-7]*
Hexadecimal   0[xX][0-9a-fA-F]+

%%

{WhiteSpace} {}
{LineComment} {}
{BlockComment} {}
"int" {return INT; }
"return" {return RETURN; }
{Indentifier} {yylval.str_val = new string(yytext); return IDENT; }
{Decimal} {yylval.int_val = strtol(yytext, NULL, 0); return INT_CONST; }
{Octal} {yylval.int_val = strtol(yytext, NULL, 0); return INT_CONST; }
{Hexadecimal} {yylval.int_val = strtol(yytext, NULL, 0); return INT_CONST; }
. {return yytext[0]; }

%%