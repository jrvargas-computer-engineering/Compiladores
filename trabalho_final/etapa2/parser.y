%{
#include <stdio.h>
int yylex(void);
void yyerror (char const *mensagem);
%}

%define parse.error verbose // Para mensagens de erro detalhadas 

// Lista de todos os tokens da linguagem
%token TK_TIPO
%token TK_VAR
%token TK_SENAO
%token TK_DECIMAL
%token TK_SE
%token TK_INTEIRO
%token TK_ATRIB
%token TK_RETORNA
%token TK_SETA
%token TK_ENQUANTO
%token TK_COM
%token TK_OC_LE
%token TK_OC_GE
%token TK_OC_EQ
%token TK_OC_NE
%token TK_ID
%token TK_LI_INTEIRO
%token TK_LI_DECIMAL
%token TK_ER


// ====================  Regras da gramatica  ====================  
%%
/*
programa: lista ';';
programa: %empty;
lista: elemento;
lista: lista ',' elemento;
elemento: TK_INTEIRO ',' TK_DECIMAL;
*/

// ==========  Estrutura do programa ==========
programa:
    %empty
    | lista_elementos_opcional
; // Um programa eh composto por uma lista opcional de elementos

lista_elementos_opcional:
    lista_elementos ';'
; // a lista eh terminada pelo operador ponto-e-virgula

lista_elementos:
    elemento
    | lista_elementos ',' elemento
; // Os elementos da lista são separados pelo operador virgula (left recursion)

elemento:
    definicao_funcao
    | declaracao_variavel
; /* 
Cada elemento dessa lista eh ou uma definicao de funcao 
ou uma declaracao de variavel 
*/

// ==========  Definicao de funcao  ==========
definicao_funcao:
    cabecalho_funcao corpo_funcao
; // Uma definicao de funcao eh composta por um cabecalho e um corpo

cabecalho_funcao:
    TK_ID TK_SETA tipo lista_opicional_parametros TK_ATRIB
; /* 
O cabecalho consiste no token TK_ID 
seguido do token TK_SETA 
seguido ou do token TK_DECIMAL ou do token TK_INTEIRO, 
seguido por uma lista opcional de parametros 
seguido do token TK_ATRIB. 
*/

lista_opicional_parametros:
    %empty
    | token_opcional_TK_COM lista_parametros
; /* 
A lista de parametros, quando presente, 
consiste no token opcional TK_COM seguido de uma lista, 
separada por virgula, de parametros. 
*/
token_opcional_TK_COM:
    %empty
    | TK_COM
;

lista_parametros:
    parametro
    | lista_parametros ',' parametro
;

parametro:
    TK_ID TK_ATRIB tipo
; /* 
Cada parametro consiste no token TK_ID
seguido do token TK_ATRIB 
seguido ou do token TK_INTEIRO ou do token TK_DECIMAL.
*/

corpo_funcao:
    bloco_comandos 
; // O corpo eh um bloco de comandos 

// ==========  Declaracao de variaveis  ==========
/* declaracao_variavel: // Sem inicialização
    TK_VAR TK_ID TK_ATRIB tipo
;

variavel_declaracao_local: // Com inicialização opcional
    TK_VAR TK_ID TK_ATRIB tipo inicializacao_opt
;

tipo:
    TK_DECIMAL
    | TK_INTEIRO
;

inicializacao_opt:
    %empty
    | TK_COM literal
;

literal:
    TK_LI_INTEIRO
    | TK_LI_DECIMAL
;

// ==========  Comandos  ==========
bloco_comandos:
    TK_ABRE_COLCHETE comando_simples_list_opt TK_FECHA_COLCHETE
;

comando_simples_list_opt:
    %empty
    | comando_simples_list
;

comando_simples_list:
    comando_simples
    | comando_simples_list comando_simples
;

comando_simples:
    variavel_declaracao_local ';'
    | comando_atribuicao ';'
    | chamada_funcao ';'
    | comando_retorno ';'
    | comando_condicional
    | comando_iterativo
    | bloco_comandos // Um bloco também é um comando simples [cite: 45]
;
*/
%%

// yylineno é uma variável global que o Flex (scanner.l) mantém com o número da linha atual
extern int yylineno;
 
// Função chamada pelo yyparse ao encontrar um erro sintático.
void yyerror (char const *mensagem)
{
    // Imprime uma mensagem de erro para a saida informando a linha onde o erro ocorreu e a mensagem do parser.
    printf("[ERRO SINTÁTICO] Linha %d: %s\n ", yylineno, mensagem);
}