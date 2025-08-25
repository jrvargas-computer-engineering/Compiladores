
%{
    #include "tokens.h"
}%

%option noyywrap
%option yylineno

%%
tipo    { return TK_TIPO; }
var     { return TK_VAR; }
senao   { return TK_SENAO; }
decimal { return TK_DECIMAL; } 
se      { return TK_SE; } 
inteiro { return TK_INTEIRO; } 
retorna { return TK_RETORNA; }
enquanto{ return TK_ENQUANTO; }
com     { return TK_COM; }
[!*/%+-<>[]()=,;&|]  {return yytext[0]}
<= TK_OC_LE
>= TK_OC_GE 
== TK_OC_EQ 
!= TK_OC_NE 
:= TK_ATRIB 
-> TK_SETA 
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
