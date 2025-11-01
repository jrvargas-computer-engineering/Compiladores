// Grupo A - Alunos:
// Juliana Rodrigres de Vargas- 00337553
// Sofia Popsin Gomes - 00313563

%{
#include <stdio.h>
#include <stdlib.h>
#include "asd.h"
#include "tabela.h"
int yylex(void);
void yyerror (char const *mensagem);
void yyerror_semantic(const char *mensagem, int line, int error_code);
extern asd_tree_t *arvore;
%}


/*  =====================================================
    =============== Declaracoes do Bison ================
    =====================================================
*/ 
%code requires { 
    #include "asd.h" 
    #include "tabela.h"    
    asd_tree_t* new_node_from_lexval(lexical_value_t *lexval);
    asd_tree_t* new_node_from_binary_op(const char *label, asd_tree_t *child1, asd_tree_t *child2);
    asd_tree_t* new_node_from_unary_op(const char *label, asd_tree_t *child);
    asd_tree_t* new_node_from_binary_op_arit(const char *label, asd_tree_t *child1, asd_tree_t *child2);
    asd_tree_t* new_node_from_binary_op_rel_log(const char *label, asd_tree_t *child1, asd_tree_t *child2);
}
%define parse.error verbose //Para mensagens de erro detalhadas 

/*
Para
 simplificar esse procedimento, os nós da AST devem
 ser anotados com um tipo de dado definido de acordo
 com as regras de inferência de tipos. Um nó da AST
 deve ter portanto um novo campo que registra o seu
 tipo de dado. 
*/
%union {
  lexical_value_t *valor_lex;
  asd_tree_t *arvore;
  semantic_type_t semantic_type;
}
/*  =====================================================
    =============== Tokens da Linguagem =================
    =====================================================
*/ 
//tokens com "valor de conteudo" carregam informacao
//vao virar folhas posteriormente
%token<valor_lex> TK_ID
%token<valor_lex> TK_LI_INTEIRO
%token<valor_lex> TK_LI_DECIMAL
%type <semantic_type> tipo
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
%type <arvore> escopo_ini escopo_fim escopo_bloco_ini escopo_bloco_fim
%%




/*  =====================================================
    =============== Regras da Gramatica  ================
    =====================================================
*/ 


// Um programa eh composto por uma lista opcional de elementos
// a lista eh terminada pelo operador ponto-e-virgula
programa:
    %empty { 
        $$ = NULL;
        arvore = $$;
    }
    // escopo global
    | escopo_ini lista_elementos escopo_fim ';' {
        $$ = $2;
        arvore = $$;
    }
; 

escopo_ini:
    %empty {
        table_t* tabela_global = table_create(); 
        scope_stack_push(tabela_global);
        $$ = NULL;
    }
;

escopo_fim:
    %empty {
        table_t* tabela_global = scope_stack_pop();
        table_free(tabela_global);
        $$ = NULL; 
    }
 
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

        //definicao funcao eh onde escopo eh destruido
        table_t* tabela_funcao = scope_stack_pop();
        table_free(tabela_funcao);
    }
;

cabecalho_funcao: 
    TK_ID TK_SETA tipo lista_opicional_parametros TK_ATRIB{
        //$$ = new_node_from_lexval($1); 

        $$ = asd_new($1->value); 
        $$->data_type = $3; 

        //$4 NAO DEVE SER adicionada na arvore
        //pensar sobre depois
        //if ($4 != NULL) {
        //    asd_add_child($$, $4);
        //}    

        /* CRIAR ESCOPO DA FUNCAO */
        table_t* tabela_funcao = table_create();


        int num_args = 0;
        semantic_type_t* arg_types = extract_and_store_params(tabela_funcao, $4, &num_args);
        
        //aqui os parametros serao colocados na tabela ($4)
        table_t* escopo_pai = scope_stack_peek();
        
        if (table_find(escopo_pai, $1->value) != NULL) {
            yyerror_semantic("Funcao ja declarada.", $1->line, ERR_DECLARED);
        }
        symbol_t* func_symbol = symbol_create_func($1, $3, num_args, arg_types); 
        table_insert(escopo_pai, func_symbol); 
        

        scope_stack_push(tabela_funcao);
        free(arg_types);
        //asd_free($4);
        //free($1->value);
        //free($1);    

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
        $$ = $1; 
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
        $$ = new_node_from_lexval($1); 
        if ($$) {
            $$->data_type = $3; // <-- CORREÇÃO
        }
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
       
        //pegar o escopo atual
        table_t* escopo_atual = scope_stack_peek();

        //verifica se simbolo esta declarado neste escopo 
        if (table_find(escopo_atual, $2->value) != NULL) {
            yyerror_semantic("Identificador ja declarado.", $2->line, ERR_DECLARED);
        }
        symbol_t* novo_simbolo = symbol_create_var($2, $4);
        table_insert(escopo_atual, novo_simbolo);     
        $$ = NULL;
        
        //o ponteiro $2 agora esta salvo na tabela de simbolos
        //free($2->value);
        //free($2); 
    }
;

tipo:
    TK_DECIMAL {$$ = SEMANTIC_TYPE_FLOAT; }
    | TK_INTEIRO {$$ = SEMANTIC_TYPE_INT; }
; //nao gera no AST , mas agora retorna valor
// para o parser


//POSSIVEL ERRO AQUI
// Regra "geral" que aponta para as regras específicas de tipo
declaracao_variavel_c_ini_opcional:
    TK_VAR TK_ID TK_ATRIB TK_INTEIRO inicializacao_inteiro_opcional{
        
        table_t* escopo_atual = scope_stack_peek();
        //verifica se simbolo esta declarado neste escopo 
        if (table_find(escopo_atual, $2->value) != NULL) {
            yyerror_semantic("Identificador ja declarado.", $2->line, ERR_DECLARED);
        }
        
        symbol_t* novo_simbolo = symbol_create_var($2, SEMANTIC_TYPE_INT);
        table_insert(escopo_atual, novo_simbolo);
        
        if($5 == NULL){
            $$ = NULL;
        }
        else{
            if ($5->data_type != SEMANTIC_TYPE_INT) {
                yyerror_semantic("Inicializacao incompativel. Esperava 'inteiro'.", $2->line, ERR_WRONG_TYPE);
            }
            $$ = asd_new("com"); 
            asd_tree_t* tk_id_no = asd_new($2->value);
            asd_add_child($$, tk_id_no);
            asd_add_child($$, $5);
        }
        //free($2->value);
        //free($2);
    }
    | TK_VAR TK_ID TK_ATRIB TK_DECIMAL inicializacao_decimal_opcional{
       
        table_t* escopo_atual = scope_stack_peek();
        
        //verifica se simbolo esta declarado neste escopo 
        if (table_find(escopo_atual, $2->value) != NULL) {
            yyerror_semantic("Identificador ja declarado.", $2->line, ERR_DECLARED);
        }
       
        symbol_t* novo_simbolo = symbol_create_var($2, SEMANTIC_TYPE_FLOAT);
        table_insert(escopo_atual, novo_simbolo);
        
        if($5 == NULL){
            $$ = NULL; 
        }
        else{
            if ($5->data_type != SEMANTIC_TYPE_FLOAT) {
                yyerror_semantic("Inicializacao incompativel. Esperava 'decimal'.", $2->line, ERR_WRONG_TYPE);
            }
            $$ = asd_new("com"); 
            asd_tree_t* tk_id_no = asd_new($2->value);
            asd_add_child($$, tk_id_no);
            asd_add_child($$, $5);
        }
        //free($2->value);
        //free($2);
    }
;


//POSSIVEL ERRO AQUI
// Regra específica para inicialização de INTEIROS
inicializacao_inteiro_opcional:
    %empty {$$ = NULL;}
    | TK_COM TK_LI_INTEIRO {
        $$ = new_node_from_lexval($2); 
        $$->data_type = SEMANTIC_TYPE_INT;         
    }
;

// Regra específica para inicialização de DECIMAIS
inicializacao_decimal_opcional:
    %empty {$$ = NULL;}
    // Aceita literal decimal
    | TK_COM TK_LI_DECIMAL   { 
        $$ = new_node_from_lexval($2); 
        $$->data_type = SEMANTIC_TYPE_FLOAT; 

    }
    | TK_COM TK_LI_INTEIRO  {// E também aceita literal inteiro (ex: var d := decimal com 5)
        $$ = new_node_from_lexval($2); 
        $$->data_type = SEMANTIC_TYPE_INT; 
    }
;

literal:
    TK_LI_INTEIRO {
        $$ = new_node_from_lexval($1); 
        $$->data_type = SEMANTIC_TYPE_INT; 
    }
    | TK_LI_DECIMAL {
        $$ = new_node_from_lexval($1); 
        $$->data_type = SEMANTIC_TYPE_FLOAT; 
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
    '['escopo_bloco_ini lista_comando_simples_opcionais escopo_bloco_fim']'{
        $$ = $3;
    } // apenas propaga lista de comandos
;

escopo_bloco_ini:
    %empty {
        table_t* tabela_bloco = table_create(); 
        scope_stack_push(tabela_bloco);
        $$ = NULL;   
    }
;

escopo_bloco_fim: 
    %empty {
        table_t* tabela_bloco = scope_stack_pop();
        table_free(tabela_bloco);
        $$ = NULL;
    }
;

lista_comando_simples_opcionais:
    %empty {$$ = NULL;}
    | lista_comando_simples { $$ = $1; }
;

lista_comando_simples:
    comando_simples{
        if($1 == NULL ){$$ = NULL;} else{$$ = $1;} 
    }
    | comando_simples lista_comando_simples  {
       
       if($1 == NULL ){
            $$ = $2;
        } else{
            $$ = $1;
            asd_add_child($1, $2);    
        } 
    }
;

// Consiste no token TK_ID seguido do token TK_ATRIB seguido de uma expressão
comando_atribuicao:
    TK_ID TK_ATRIB expressao {
        symbol_t* simbolo = stack_find_global($1->value);
        
        if (simbolo == NULL) {
            yyerror_semantic("Identificador nao declarado.", $1->line, ERR_UNDECLARED);
        }
        if (simbolo->nature == SYMBOL_FUNCAO) {
            yyerror_semantic("Funcao usada como variavel em atribuicao.", $1->line, ERR_FUNCTION);
        }

        // 4. (Passo 6) Verifique os tipos
        // (Será feito no Passo 6, mas a informação está aqui)
        // if (simbolo->data_type != $3->data_type) { ... }
        if (simbolo->data_type != $3->data_type) {
            yyerror_semantic("Atribuicao de tipo incompativel.", $1->line, ERR_WRONG_TYPE);
        }

        $$ = asd_new(":="); 
        asd_tree_t* tk_id_no = asd_new($1->value);
        tk_id_no->data_type = simbolo->data_type;
        asd_add_child($$, tk_id_no); 
        asd_add_child($$, $3);      
        free($1->value);
        free($1);
    }
; 

// consiste no token TK_ID, seguida de argumentos entre parênteses,
chamada_funcao:
    TK_ID '(' lista_argumentos_opcional ')' {
        symbol_t* simbolo = stack_find_global($1->value);   
        
        if (simbolo == NULL) {
            yyerror_semantic("Funcao nao declarada.", $1->line, ERR_UNDECLARED);
        }     

        if (simbolo->nature == SYMBOL_ID) {
            yyerror_semantic("Variavel usada como funcao.", $1->line, ERR_VARIABLE);
        }

        char label[256];
        sprintf(label, "call %s", $1->value);
        $$ = asd_new(label);
        $$->data_type = simbolo->data_type;

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
        if ($2->data_type != $4) {
             yyerror_semantic("Tipo de retorno incompativel com a declaracao da funcao.", 0, ERR_WRONG_TYPE);
        }
        $$ = new_node_from_unary_op("retorna", $2);  
        $$->data_type = $2->data_type; 
    }
; 

construcoes_fluxo_controle:
    comando_condicional { $$ = $1;}
    | comando_enquanto { $$ = $1; }
;

comando_condicional:
    TK_SE '(' expressao ')' bloco_comandos senao_opcional{
        if ($3->data_type != SEMANTIC_TYPE_INT) {
            yyerror_semantic("Expressao de teste do 'se' deve ser do tipo inteiro.", 0, ERR_WRONG_TYPE);
        }
        $$ = new_node_from_binary_op("se", $3, $5);
        if($6 != NULL) asd_add_child($$, $6); 
        $$->data_type = SEMANTIC_TYPE_INT;
    }
;

senao_opcional:
    %empty {$$ = NULL;}
    | TK_SENAO bloco_comandos { $$ = $2;}
;

comando_enquanto:
    TK_ENQUANTO '(' expressao ')' bloco_comandos {
        if ($3->data_type != SEMANTIC_TYPE_INT) {
            yyerror_semantic("Expressao de teste do 'enquanto' deve ser do tipo inteiro.", 0, ERR_WRONG_TYPE);
        }
        $$ = new_node_from_binary_op("enquanto", $3, $5);
        $$->data_type = SEMANTIC_TYPE_INT; 
    }
;

// ==========  Expressoes (COM PRECEDENCIA E ASSOCIATIVIDADE) ==========
expressao:
    expr_nivel7 { $$ = $1; }
;

// Nível 7: OU Lógico (Menor Precedência)
expr_nivel7:
    expr_nivel7 '|' expr_nivel6 {
        $$ = new_node_from_binary_op_rel_log("|", $1, $3);
    }
    | expr_nivel6  { $$ = $1; }
;

// Nível 6: E Lógico
expr_nivel6:
    expr_nivel6 '&' expr_nivel5  { 
        $$ = new_node_from_binary_op_rel_log("&", $1, $3);
    }
    | expr_nivel5 { $$ = $1; }
;

// Nível 5: Operadores de Igualdade (==, !=)
expr_nivel5:
    expr_nivel5 TK_OC_EQ expr_nivel4 {
        $$ = new_node_from_binary_op_rel_log("==", $1, $3);

    }
    | expr_nivel5 TK_OC_NE expr_nivel4 {
        $$ = new_node_from_binary_op_rel_log("!=", $1, $3);
 
    }
    | expr_nivel4 { $$ = $1; }
;

// Nível 4: Operadores Relacionais (<, >, <=, >=)
expr_nivel4:
    expr_nivel4 '<' expr_nivel3 {
        $$ = new_node_from_binary_op_rel_log("<", $1, $3);

    }
    | expr_nivel4 '>' expr_nivel3{
        $$ = new_node_from_binary_op_rel_log(">", $1, $3);

    }
    | expr_nivel4 TK_OC_LE expr_nivel3{
        $$ = new_node_from_binary_op_rel_log("<=", $1, $3);

    }
    | expr_nivel4 TK_OC_GE expr_nivel3{
        $$ = new_node_from_binary_op_rel_log(">=", $1, $3);

    }
    | expr_nivel3 { $$ = $1; }
;

// Nível 3: Soma e Subtração (Binários)
expr_nivel3:
    expr_nivel3 '+' expr_nivel2{
        $$ = new_node_from_binary_op_arit("+", $1, $3);
    }
    | expr_nivel3 '-' expr_nivel2 {
        $$ = new_node_from_binary_op_arit("-", $1, $3);

    }
    | expr_nivel2 { $$ = $1; }
;

// Nível 2: Multiplicação, Divisão, Resto
expr_nivel2:
    expr_nivel2 '*' expr_nivel1 {
        $$ = new_node_from_binary_op_arit("*", $1, $3);
    }
    | expr_nivel2 '/' expr_nivel1 {
        $$ = new_node_from_binary_op_arit("/", $1, $3);
    }
    | expr_nivel2 '%' expr_nivel1 {
        if ($1->data_type != SEMANTIC_TYPE_INT || $3->data_type != SEMANTIC_TYPE_INT) {
            yyerror_semantic("Operador de resto (%) aplicado a float.", 0, ERR_WRONG_TYPE);
        }
        $$ = new_node_from_binary_op_arit("%", $1, $3);
    }
    | expr_nivel1 { $$ = $1; }
;

// Nível 1: Operadores Unários (+, -, !)
// Operadores unários são prefixados e têm associatividade à direita.
// Por isso, a recursão aqui é à direita.
expr_nivel1:
    '+' expr_nivel1 {
        $$ = new_node_from_unary_op("+", $2);   
        $$->data_type = $2->data_type;
    }
    | '-' expr_nivel1 {
        $$ = new_node_from_unary_op("-", $2); 
        $$->data_type = $2->data_type;
    }
    | '!' expr_nivel1 {
    if ($2->data_type != SEMANTIC_TYPE_INT) {
             yyerror_semantic("Negacao logica (!) aplicada a um float.", 0, ERR_WRONG_TYPE);
        }
        $$ = new_node_from_unary_op("!", $2);
        $$->data_type = SEMANTIC_TYPE_INT; 
    }
    | fator { $$ = $1; }
;

// Nível 0: "Fator" - Elementos de maior precedência
// Inclui literais, identificadores, chamadas de função e expressões entre parênteses.
fator:
    TK_ID {
        symbol_t* simbolo = stack_find_global($1->value);
        if (simbolo == NULL) {
            yyerror_semantic("Identificador nao declarado.", $1->line, ERR_UNDECLARED);
        }
        if (simbolo->nature == SYMBOL_FUNCAO) {
            yyerror_semantic("Funcao usada como variavel.", $1->line, ERR_FUNCTION);
        }
        $$ = new_node_from_lexval($1); 
        $$->data_type = simbolo->data_type;
    }
    | literal { $$ = $1; }
    | chamada_funcao { $$ = $1; }
    | '(' expressao ')' {$$ = $2; } // Permite forçar a precedência
;
%%

// yylineno eh uma variável global que o Flex (scanner.l) mantém com o número da linha atual
extern int yylineno;
 
// Função chamada pelo yyparse ao encontrar um erro sintático.
void yyerror (char const *mensagem) {
    printf("Linha %d: %s\n ", yylineno, mensagem);
}

void yyerror_semantic(const char *mensagem, int line, int error_code) {
    printf("Erro semantico (Linha %d): %s\n", line, mensagem);     
    exit(error_code); 
}

/*  =====================================================
    =================== Funcoes =========================
    =====================================================
*/ 
//new node from token/lex value
//lex values are e.g $1, $2, NULL
asd_tree_t* new_node_from_lexval(lexical_value_t *lexval) {
    if (lexval == NULL) return NULL;
    asd_tree_t *node = asd_new(lexval->value);    
    free(lexval->value);
    free(lexval);
    return node;
}

asd_tree_t* new_node_from_binary_op(const char *label, asd_tree_t *child1, asd_tree_t *child2) {
    asd_tree_t *node = asd_new(label);
    asd_add_child(node, child1);
    asd_add_child(node, child2);
    return node;
}

asd_tree_t* new_node_from_unary_op(const char *label, asd_tree_t *child) {
    asd_tree_t *node = asd_new(label);
    asd_add_child(node, child);
    return node;
}


asd_tree_t* new_node_from_binary_op_arit(const char *label, asd_tree_t *child1, asd_tree_t *child2) {
    if (child1->data_type != child2->data_type) {
        yyerror_semantic("Tipos incompativeis em operacao aritmetica.", 0, ERR_WRONG_TYPE);
    }

    asd_tree_t *node = asd_new(label);
    asd_add_child(node, child1);
    asd_add_child(node, child2);

    node->data_type = child1->data_type; 
    
    return node;
}


asd_tree_t* new_node_from_binary_op_rel_log(const char *label, asd_tree_t *child1, asd_tree_t *child2) {
    if (child1->data_type != child2->data_type) {
        yyerror_semantic("Tipos incompativeis em operacao relacional/logica.", 0, ERR_WRONG_TYPE); 
    }
    asd_tree_t *node = asd_new(label);
    asd_add_child(node, child1); 
    asd_add_child(node, child2); 
    node->data_type = SEMANTIC_TYPE_INT; 
    return node;
}