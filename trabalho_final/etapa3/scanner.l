/* Grupo A - Alunos:
 Juliana Rodrigres de Vargas- 00337553
 Sofia Popsin Gomes - 00313563*/

%{
    #include <stdio.h>
    #include "parser.tab.h" // Gerado pelo bison -d
%}

%option noyywrap
%option yylineno

/* Regras do flex */ 
/* "Somente tokens identificadores e literais devem possuir 
 um valor léxico a ser empregado na AST"*/


%%
tipo     { return TK_TIPO;}
var      { return TK_VAR; }
senao    { return TK_SENAO; }
decimal  { return TK_DECIMAL; }
se       { return TK_SE; }
inteiro  { return TK_INTEIRO; }
retorna  { return TK_RETORNA; }
enquanto { return TK_ENQUANTO; }
com      { return TK_COM; }


[0-9]*\.[0-9]+  { 
    yylval.valor_lex = malloc(sizeof(lexical_value_t));
    yylval.valor_lex->line = yylineno; 
    yylval.valor_lex->value = strdup(yytext);
    return TK_LI_DECIMAL;
}
[0-9]+  { 
    yylval.valor_lex = malloc(sizeof(lexical_value_t));
    yylval.valor_lex->line = yylineno; 
    yylval.valor_lex->value = strdup(yytext);
    return TK_LI_INTEIRO;
}
[a-z_][a-z0-9_]* { 
    yylval.valor_lex = malloc(sizeof(lexical_value_t));
    yylval.valor_lex->line = yylineno; 
    yylval.valor_lex->value = strdup(yytext);
    return TK_ID;
}

\<= { return TK_OC_LE; }
>=  { return TK_OC_GE; }
==  { return TK_OC_EQ; }
!=  { return TK_OC_NE; }
:=  { return TK_ATRIB; }
->  { return TK_SETA;  }
[!*/%+\-<>[()=,;&|\]] { return yytext[0]; }
[ \t\n]+   /* espaços em branco */
"//"[^\n]* /*comentarios com // */
. { return TK_ER; }
%%

int get_line_number() {
    return yylineno;
}

