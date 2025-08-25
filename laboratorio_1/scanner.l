
%{
    #include "tokens.h"
}%

%option noyywrap
%option yylineno

%%
tipo { return TK_TIPO; }
[,=\]] {return yytext[0]}
. return TK_ER;
%%


int get_line_number() {
    return yylineno;
}


/*
int main (int argc, char **argv) {
int token = 0;
while ((token = yylex())){
// faça algo com o token
// consulte o lexema com yytext
}
return 0;
}
*/
