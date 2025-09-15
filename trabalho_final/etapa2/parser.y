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
    | declaracao_variavel_s_ini
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
declaracao_variavel_s_ini: // Sem inicialização
    TK_VAR TK_ID TK_ATRIB tipo
;

tipo:
    TK_DECIMAL
    | TK_INTEIRO
;

declaracao_variavel_c_ini_opcional: // Com inicialização opcional
    TK_VAR TK_ID TK_ATRIB tipo inicializacao_opcional
;

inicializacao_opcional:
    %empty
    | TK_COM literal
;

literal:
    TK_LI_INTEIRO
    | TK_LI_DECIMAL
;

// ==========  Comandos  ==========
comando_simples:
    bloco_comandos
    | declaracao_variavel_c_ini_opcional
    | comando_atribuicao 
    | chamada_funcao 
    | comando_retorno
    | construcoes_fluxo_controle
;/*
comandos simples da linguagem podem ser:
bloco de comandos, declaração de variável, co-
mando de atribuição, chamada de função, co-
mando de retorno, e construções de fluxo de con-
trole.
*/

bloco_comandos:
    '[' lista_comando_simples_opicionais ']'
;/* Definido entre colchetes, e
consiste em uma sequência, possivelmente vazia,
de comandos simples. Um bloco de comandos
é considerado como um comando único simples
e pode ser utilizado em qualquer construção que
aceite um comando simples.
*/

lista_comando_simples_opicionais:
    %empty
    | lista_comando_simples
;

lista_comando_simples:
    comando_simples
    | lista_comando_simples comando_simples
;

comando_atribuicao:
    TK_ID TK_ATRIB expressao
; // Consiste no token TK_ID seguido do token TK_ATRIB seguido de uma expressão

chamada_funcao:
    TK_ID '(' lista_argumentos_opcional ')' 
; // consiste no token TK_ID, seguida de argumentos entre parênteses,

lista_argumentos_opcional:
    %empty
    | lista_argumentos
; // Uma chamada de função pode existir sem argumentos

lista_argumentos:
    expressao
    | lista_argumentos ',' expressao
; /*  cada argumento eh separado do outro por vírgula. 
Um argumento eh uma expressão.
*/

comando_retorno:
    TK_RETORNA expressao TK_ATRIB tipo
; /* e terminado ou pelo
token TK_DECIMAL ou pelo token TK_INTEIRO.
*/ 

construcoes_fluxo_controle:
    comando_condicional
    | comando_enquanto
;

comando_condicional:
    TK_SE '(' expressao ')' bloco_comandos senao_opcional
;

senao_opcional:
    %empty
    | TK_SENAO bloco_comandos
;

comando_enquanto:
    TK_ENQUANTO '(' expressao ')' bloco_comandos
;

// ==========  Expressoes (COM PRECEDENCIA E ASSOCIATIVIDADE) ==========
expressao:
    expr_nivel7
;

// Nível 7: OU Lógico (Menor Precedência)
expr_nivel7:
    expr_nivel7 '|' expr_nivel6
    | expr_nivel6
;

// Nível 6: E Lógico
expr_nivel6:
    expr_nivel6 '&' expr_nivel5
    | expr_nivel5
;

// Nível 5: Operadores de Igualdade (==, !=)
expr_nivel5:
    expr_nivel5 TK_OC_EQ expr_nivel4
    | expr_nivel5 TK_OC_NE expr_nivel4
    | expr_nivel4
;

// Nível 4: Operadores Relacionais (<, >, <=, >=)
expr_nivel4:
    expr_nivel4 '<' expr_nivel3
    | expr_nivel4 '>' expr_nivel3
    | expr_nivel4 TK_OC_LE expr_nivel3
    | expr_nivel4 TK_OC_GE expr_nivel3
    | expr_nivel3
;

// Nível 3: Soma e Subtração (Binários)
expr_nivel3:
    expr_nivel3 '+' expr_nivel2
    | expr_nivel3 '-' expr_nivel2
    | expr_nivel2
;

// Nível 2: Multiplicação, Divisão, Resto
expr_nivel2:
    expr_nivel2 '*' expr_nivel1
    | expr_nivel2 '/' expr_nivel1
    | expr_nivel2 '%' expr_nivel1
    | expr_nivel1
;

// Nível 1: Operadores Unários (+, -, !)
// Operadores unários são prefixados e têm associatividade à direita.
// Por isso, a recursão aqui é à direita.
expr_nivel1:
    '+' expr_nivel1
    | '-' expr_nivel1
    | '!' expr_nivel1
    | fator
;

// Nível 0: "Fator" - Elementos de maior precedência
// Inclui literais, identificadores, chamadas de função e expressões entre parênteses.
fator:
    TK_ID
    | literal
    | chamada_funcao
    | '(' expressao ')' // Permite forçar a precedência
;
%%

// yylineno eh uma variável global que o Flex (scanner.l) mantém com o número da linha atual
extern int yylineno;
 
// Função chamada pelo yyparse ao encontrar um erro sintático.
void yyerror (char const *mensagem)
{
    // Imprime uma mensagem de erro para a saida informando a linha onde o erro ocorreu e a mensagem do parser.
    printf("[ERRO SINTÁTICO] Linha %d: %s\n ", yylineno, mensagem);
}