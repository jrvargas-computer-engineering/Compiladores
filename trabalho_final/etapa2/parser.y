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

%%
// As regras da gramática
programa: lista ';';
programa: %empty;
lista: elemento;
lista: lista ',' elemento;
elemento: TK_INTEIRO ',' TK_DECIMAL;

// Estrutura do programa

element_list_opt:
    /* vazio */
    | element_list
;

element_list:
    element
    | element_list TK_VIRGULA element
;

element:
    funcao_definicao
    | variavel_declaracao_global
;

// Declaracao de variaveis
variavel_declaracao_global: // Sem inicialização
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
    /* vazio */
    | TK_COM literal
;

literal:
    TK_LI_INTEIRO
    | TK_LI_DECIMAL
;

// Definicao de funcao

funcao_definicao:
    cabecalho_funcao corpo_funcao
;

cabecalho_funcao:
    TK_ID TK_SETA tipo param_list_opt TK_ATRIB
;

param_list_opt:
    /* vazio */
    | TK_COM param_list
;

param_list:
    parametro
    | param_list TK_VIRGULA parametro
;

parametro:
    TK_ID TK_ATRIB tipo
;

corpo_funcao:
    bloco_comandos // O corpo é um bloco de comandos
;

// Comandos
bloco_comandos:
    TK_ABRE_COLCHETE comando_simples_list_opt TK_FECHA_COLCHETE
;

comando_simples_list_opt:
    /* vazio */
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

%%

// yylineno é uma variável global que o Flex (scanner.l) mantém com o número da linha atual
extern int yylineno;
 
/**
 * Função chamada pelo yyparse ao encontrar um erro sintático.
 */
void yyerror (char const *mensagem)
{
    // Imprime uma mensagem de erro para a saida informando a linha onde o erro ocorreu e a mensagem do parser.
    printf("[ERRO SINTÁTICO] Linha %d: %s\n ", yylineno, mensagem);
}