// Grupo A - Alunos:
// Juliana Rodrigres de Vargas- 00337553
// Sofia Popsin Gomes - 00313563

%{

// ================= codigo em C ========================
#include <stdio.h>
#include <stdlib.h>
#include "asd.h"

int yylex(void);
void yyerror (char const *mensagem);


extern asd_tree_t *arvore;
%}


// ================= declaracoes do bison ========================
%code requires { 
    #include "asd.h" 
    
    // estrutura de valor lexico
    typedef struct lexical_value {
      int line;
      int type; 
      char *value;
    } lexical_value_t;
    
}
%define parse.error verbose // Para mensagens de erro detalhadas 

%union {
  lexical_value_t *valor_lex;
  asd_tree_t *arvore;
}
// ===============================================================

// ================= tokens da linguagem =========================
//tokens com "valor de conteudo" carregam informacao
//vao virar folhas posteriormente
%token<valor_lex> TK_ID
%token<valor_lex> TK_LI_INTEIRO
%token<valor_lex> TK_LI_DECIMAL

//sem valor
%token TK_SENAO TK_SE TK_RETORNA TK_ATRIB TK_ENQUANTO TK_COM TK_SETA
%token TK_TIPO TK_VAR TK_DECIMAL TK_INTEIRO
%token TK_OC_LE TK_OC_GE TK_OC_EQ TK_OC_NE
%token TK_ER

// cabecas de producao que criam ou propagam nós
%type <arvore> programa lista_elementos elemento
%type <arvore> definicao_funcao cabecalho_funcao corpo_funcao
%type <arvore> lista_opicional_parametros lista_parametros parametro
%type <arvore> declaracao_variavel_s_ini declaracao_variavel_c_ini_opcional
%type <arvore> inicializacao_inteiro_opcional inicializacao_decimal_opcional
%type <arvore> literal
%type <arvore> comando_simples bloco_comandos lista_comando_simples_opcionais lista_comando_simples
%type <arvore> comando_atribuicao chamada_funcao comando_retorno
%type <arvore> lista_argumentos_opcional lista_argumentos
%type <arvore> construcoes_fluxo_controle comando_condicional senao_opcional comando_enquanto
%type <arvore> expressao expr_nivel7 expr_nivel6 expr_nivel5 expr_nivel4 expr_nivel3 expr_nivel2 expr_nivel1 fator
// ===============================================================



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

// Um programa eh composto por uma lista opcional de elementos
// a lista eh terminada pelo operador ponto-e-virgula
programa:
    %empty { 
        $$ = NULL;
        arvore = $$;
    }
    | lista_elementos ';' {
        $$ = $1;
        arvore = $$;
    }
; 

 
//Cada elemento dessa lista eh ou uma definicao de funcao 
//ou uma declaracao de variavel 
lista_elementos:
    elemento{
        $$ = $1; //primeiro elemento
    }
    |  elemento ',' lista_elementos { //fix:mudei para poder ter null 
        if($1 != NULL){
            $$ = $1; 
            if($3 != NULL){
                asd_add_child($$, $3);
            }
        }
        else {
           $$ = $3; 
        }
    }
; // Os elementos da lista são separados pelo operador virgula ()

elemento:
    definicao_funcao {
        $$ = $1;
    }
    | declaracao_variavel_s_ini { //fix: mudei para null, para nao por na arvore
        $$ = NULL; 
    }
; 


// ==========  Definicao de funcao  ==========

definicao_funcao: 
    cabecalho_funcao corpo_funcao {
        $$ = $1;
        if($2 != NULL)
            asd_add_child($$, $2); 
    }
;


//anteriormente, a lista_opcional_parametros era perdida
//(nao era adicionada como filha)
//isso gerava memory leak

//cabecalho_funcao: 
//    TK_ID TK_SETA tipo lista_opicional_parametros TK_ATRIB{
//        $$ = asd_new($1->value); 
//        free($1->value);
//        free($1);
//    }
//;
cabecalho_funcao: 
    TK_ID TK_SETA tipo lista_opicional_parametros TK_ATRIB{
        $$ = asd_new($1->value); 

        if ($4 != NULL) {
            asd_add_child($$, $4);
        }
        free($1->value);
        free($1);
    }
;

//A lista de parametros, quando presente, 
//consiste no token opcional TK_COM seguido de uma lista, 
//separada por virgula, de parametros. 
lista_opicional_parametros:
    %empty {$$ = NULL;}
    | TK_COM lista_parametros { 
        $$ = $2;
    }
    | lista_parametros { 
        $$ = $1;
    }
; 

lista_parametros:
    parametro {
        $$ = $1; //fix
        //$$ = asd_new("com");
        //asd_add_child($$, $1);
    }
    | parametro ',' lista_parametros  {
        $$ = $1;
        asd_add_child($$, $3); 
    }
;


//Cada parametro consiste no token TK_ID
//seguido do token TK_ATRIB 
//seguido ou do token TK_INTEIRO ou do token TK_DECIMAL.
parametro:
    TK_ID TK_ATRIB tipo {
        $$ = asd_new($1->value);
        free($1->value);
        free($1); 
    }
; 

// O corpo eh um bloco de comandos 
corpo_funcao:
    bloco_comandos {
        $$ = $1; 
    }
; 

// ==========  Declaracao de variaveis  ==========
declaracao_variavel_s_ini: // Sem inicialização
    TK_VAR TK_ID TK_ATRIB tipo {
        
        //fix: tirei criacao de nodo aqui
        $$ = NULL;
        //$$ = asd_new("variavel");
        //asd_tree_t* tk_id_no = asd_new($2->value);
        //asd_add_child($$, tk_id_no);
        free($2->value);
        free($2); 
    }
;

tipo:
    TK_DECIMAL
    | TK_INTEIRO
; //nao gera no AST


//POSSIVEL ERRO AQUI
// Regra "geral" que aponta para as regras específicas de tipo
declaracao_variavel_c_ini_opcional:
    TK_VAR TK_ID TK_ATRIB TK_INTEIRO inicializacao_inteiro_opcional{
        if($5 == NULL){
            $$ = NULL;
        }
        else{
            $$ = asd_new("com"); 
            asd_tree_t* tk_id_no = asd_new($2->value);
            asd_add_child($$, tk_id_no);
            asd_add_child($$, $5);
        }
            free($2->value);
            free($2);
    }
    | TK_VAR TK_ID TK_ATRIB TK_DECIMAL inicializacao_decimal_opcional{
        if($5 == NULL){
            $$ = NULL; 
        }
        else{
            $$ = asd_new("com"); 
            asd_tree_t* tk_id_no = asd_new($2->value);
            asd_add_child($$, tk_id_no);
            asd_add_child($$, $5);
        }
        free($2->value);
        free($2);
    }
;


//POSSIVEL ERRO AQUI
// Regra específica para inicialização de INTEIROS
inicializacao_inteiro_opcional:
    %empty {$$ = NULL;}
    | TK_COM TK_LI_INTEIRO {
        $$ = asd_new($2->value); 
        free($2->value);
        free($2);        
    }
;

// Regra específica para inicialização de DECIMAIS
inicializacao_decimal_opcional:
    %empty {$$ = NULL;}
    // Aceita literal decimal
    | TK_COM TK_LI_DECIMAL   { 
        $$ = asd_new($2->value);
        free($2->value);
        free($2);
    }
    | TK_COM TK_LI_INTEIRO  {// E também aceita literal inteiro (ex: var d := decimal com 5)
        $$ = asd_new($2->value);
        free($2->value);
        free($2);  
    }
;

literal:
    TK_LI_INTEIRO {
        $$ = asd_new($1->value);
        free($1->value);
        free($1);
    }
    | TK_LI_DECIMAL {
        $$ = asd_new($1->value);
        free($1->value);
        free($1);
    }
;
// ==========  Comandos  ==========

//comandos simples da linguagem podem ser:
//bloco de comandos, declaração de variável, co-
//mando de atribuição, chamada de função, co-
//mando de retorno, e construções de fluxo de con-
//trole.
comando_simples:
    bloco_comandos { $$ = $1; }
    | declaracao_variavel_c_ini_opcional { if($1 == NULL ){$$ = NULL;} else{$$ = $1;} } //mudei aqui
    | comando_atribuicao { $$ = $1; }
    | chamada_funcao { $$ = $1; }
    | comando_retorno { $$ = $1; }
    | construcoes_fluxo_controle { $$ = $1; }
;

//Definido entre colchetes, e
//consiste em uma sequência, possivelmente vazia,
//de comandos simples. Um bloco de comandos
//é considerado como um comando único simples
//e pode ser utilizado em qualquer construção que
//aceite um comando simples.
bloco_comandos:
    '[' lista_comando_simples_opcionais ']'{
        $$ = $2;
    } // apenas propaga lista de comandos
;


lista_comando_simples_opcionais:
    %empty {$$ = NULL;}
    | lista_comando_simples { $$ = $1; }
;

lista_comando_simples:
    comando_simples{
        //$$ = $1;  mudei aqui
        if($1 == NULL ){$$ = NULL;} else{$$ = $1;} 
    }
    | comando_simples lista_comando_simples  {
       
       if($1 == NULL ){
            $$ = $2;
        } else{
            $$ = $1;
            asd_add_child($1, $2);    
        } 

       //$$ = $1;
       //asd_add_child($1, $2); 
    }
;

// Consiste no token TK_ID seguido do token TK_ATRIB seguido de uma expressão
comando_atribuicao:
    TK_ID TK_ATRIB expressao {
        $$ = asd_new(":="); 
        asd_tree_t* tk_id_no = asd_new($1->value);
        asd_add_child($$, tk_id_no); 
        asd_add_child($$, $3);      
        free($1->value);
        free($1);
    }
; 

// consiste no token TK_ID, seguida de argumentos entre parênteses,
chamada_funcao:
    TK_ID '(' lista_argumentos_opcional ')' {
        char label[256];
        sprintf(label, "call %s", $1->value);
        $$ = asd_new(label);
        
        if ($3 != NULL) asd_add_child($$, $3);
        free($1->value);
        free($1);       
    }
; 

// Uma chamada de função pode existir sem argumentos
lista_argumentos_opcional:
    %empty {$$ = NULL;}
    | lista_argumentos
; 

//cada argumento eh separado do outro por vírgula. 
//Um argumento eh uma expressão.
lista_argumentos:
    expressao{
        $$ = $1; 
    }//mexi aqui na ordem da recursao
    | expressao ',' lista_argumentos  {
        $$ = $1;
        asd_add_child($$, $3);
    }
; 


//e terminado ou pelo
//token TK_DECIMAL ou pelo token TK_INTEIRO.
comando_retorno:
    TK_RETORNA expressao TK_ATRIB tipo{
        $$ = asd_new("retorna");
        asd_add_child($$, $2); 
    }
; 

construcoes_fluxo_controle:
    comando_condicional { $$ = $1;}
    | comando_enquanto { $$ = $1; }
;

comando_condicional:
    TK_SE '(' expressao ')' bloco_comandos senao_opcional{
        $$ = asd_new("se");
        asd_add_child($$, $3);
        asd_add_child($$, $5);
        if($6 != NULL) asd_add_child($$, $6); 
    }
;

senao_opcional:
    %empty {$$ = NULL;}
    | TK_SENAO bloco_comandos { $$ = $2;}
;

comando_enquanto:
    TK_ENQUANTO '(' expressao ')' bloco_comandos {
        $$ = asd_new("enquanto");
        asd_add_child($$, $3);
        asd_add_child($$, $5);
    }
;

// ==========  Expressoes (COM PRECEDENCIA E ASSOCIATIVIDADE) ==========
expressao:
    expr_nivel7 { $$ = $1; }
;

// Nível 7: OU Lógico (Menor Precedência)
expr_nivel7:
    expr_nivel7 '|' expr_nivel6 {
        $$ = asd_new("|"); 
        asd_add_child($$, $1); 
        asd_add_child($$, $3); 
    }
    | expr_nivel6  { $$ = $1; }
;

// Nível 6: E Lógico
expr_nivel6:
    expr_nivel6 '&' expr_nivel5  { 
        $$ = asd_new("&"); 
        asd_add_child($$, $1); 
        asd_add_child($$, $3); 
    }
    | expr_nivel5 { $$ = $1; }
;

// Nível 5: Operadores de Igualdade (==, !=)
expr_nivel5:
    expr_nivel5 TK_OC_EQ expr_nivel4 {
        $$ = asd_new("=="); 
        asd_add_child($$, $1); 
        asd_add_child($$, $3); 
    }
    | expr_nivel5 TK_OC_NE expr_nivel4 {
        $$ = asd_new("!="); 
        asd_add_child($$, $1); 
        asd_add_child($$, $3);     
    }
    | expr_nivel4 { $$ = $1; }
;

// Nível 4: Operadores Relacionais (<, >, <=, >=)
expr_nivel4:
    expr_nivel4 '<' expr_nivel3 {
        $$ = asd_new("<"); 
        asd_add_child($$, $1); 
        asd_add_child($$, $3);
    }
    | expr_nivel4 '>' expr_nivel3{
        $$ = asd_new(">"); 
        asd_add_child($$, $1); 
        asd_add_child($$, $3);
    }
    | expr_nivel4 TK_OC_LE expr_nivel3{
        $$ = asd_new("<="); 
        asd_add_child($$, $1); 
        asd_add_child($$, $3);
    }
    | expr_nivel4 TK_OC_GE expr_nivel3{
        $$ = asd_new(">="); 
        asd_add_child($$, $1); 
        asd_add_child($$, $3);
    }
    | expr_nivel3 { $$ = $1; }
;

// Nível 3: Soma e Subtração (Binários)
expr_nivel3:
    expr_nivel3 '+' expr_nivel2{
        $$ = asd_new("+"); 
        asd_add_child($$, $1); 
        asd_add_child($$, $3);
    }
    | expr_nivel3 '-' expr_nivel2 {
        $$ = asd_new("-"); 
        asd_add_child($$, $1); 
        asd_add_child($$, $3);
    }
    | expr_nivel2 { $$ = $1; }
;

// Nível 2: Multiplicação, Divisão, Resto
expr_nivel2:
    expr_nivel2 '*' expr_nivel1 {
        $$ = asd_new("*"); 
        asd_add_child($$, $1); 
        asd_add_child($$, $3);
    }
    | expr_nivel2 '/' expr_nivel1 {
        $$ = asd_new("/"); 
        asd_add_child($$, $1); 
        asd_add_child($$, $3); 
    }
    | expr_nivel2 '%' expr_nivel1 {
        $$ = asd_new("%"); 
        asd_add_child($$, $1); 
        asd_add_child($$, $3);
    }
    | expr_nivel1 { $$ = $1; }
;

// Nível 1: Operadores Unários (+, -, !)
// Operadores unários são prefixados e têm associatividade à direita.
// Por isso, a recursão aqui é à direita.
expr_nivel1:
    '+' expr_nivel1 {
        $$ = asd_new("+"); 
        asd_add_child($$, $2);       
    }
    | '-' expr_nivel1 {
        $$ = asd_new("-"); 
        asd_add_child($$, $2);
    }
    | '!' expr_nivel1 {
        $$ = asd_new("!"); 
        asd_add_child($$, $2);
    }
    | fator { $$ = $1; }
;

// Nível 0: "Fator" - Elementos de maior precedência
// Inclui literais, identificadores, chamadas de função e expressões entre parênteses.
fator:
    TK_ID {
        $$ = asd_new($1->value);
        free($1->value);
        free($1);
    }
    | literal { $$ = $1; }
    | chamada_funcao { $$ = $1; }
    | '(' expressao ')' {$$ = $2; } // Permite forçar a precedência
;
%%

// yylineno eh uma variável global que o Flex (scanner.l) mantém com o número da linha atual
extern int yylineno;
 
// Função chamada pelo yyparse ao encontrar um erro sintático.
void yyerror (char const *mensagem)
{
    // Imprime uma mensagem de erro para a saida informando a linha onde o erro ocorreu e a mensagem do parser.
    printf("Linha %d: %s\n ", yylineno, mensagem);
}