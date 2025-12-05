/* Grupo A - Alunos:
 Juliana Rodrigres de Vargas- 00337553
 Sofia Popsin Gomes - 00313563*/
 
/* * tabela.h
 * Arquivo de cabeçalho para a Tabela de Símbolos e Pilha de Escopos.
 */
#ifndef TABELA_H
#define TABELA_H
#include "types.h"
#include "asd.h" 
#include "erros.h"
typedef enum {
    UNDEFINED,
    SYMBOL_LIT, 
    SYMBOL_ID,
    SYMBOL_FUNCAO
} symbol_nature_t;

/*
Cada entrada na tabela de símbolos tem uma
chave e um conteúdo. A chave única identifica o sím
bolo, e o conteúdo deve ter os campos:
 • natureza (literal, identificador ou função)
 • tipo do dado dosímbolo (int ou float)
 • argumentos e seus tipos (no caso de funções)
 • dadosdovalor do token pelo yylval (veja E3)
*/
typedef struct symbol_entry {
    char *key;    
    symbol_nature_t nature;
    semantic_type_t data_type;
    semantic_type_t *arg_types; 
    int num_args; 
    lexical_value_t *token_data;      
    int line;            
    int offset;     // Deslocamento em bytes (0, 4, 8...)
    int is_global;  // 1 se for global (rbss), 0 se for local (rfp)
} symbol_t;



/*
--- INTERFACE DA TABELA ---
tabela: struct com quantidade de elementos e lista de elementos
*/
typedef struct symbol_table {
    symbol_t **symbols; 
    int count;          
    int allocated_size; 
} table_t;
table_t* table_create(void);
void table_free(table_t* table);
void table_insert(table_t* table, symbol_t* symbol);
symbol_t* table_find(table_t* table, const char* key);


/* --- INTERFACE DA PILHA DE ESCOPOS --- */
void scope_stack_init(void);
void scope_stack_push(table_t* table);
table_t* scope_stack_pop(void);
table_t* scope_stack_peek(void);
/*
 Para verificar se uma variável foi declarada, 
 verifica-se primeiramente no escopo atual (topo
 da pilha) e enquanto não encontrar, deve-se descer na
 pilha (sem desempilhar) até chegar no escopo global
 (base da pilha, sempre presente).
 */
symbol_t* stack_find_global(const char* key);
void scope_stack_free_all(void);

symbol_t* symbol_create_var(lexical_value_t *token_data, semantic_type_t type);
symbol_t* symbol_create_func(lexical_value_t *token_data, semantic_type_t return_type, int num_args, semantic_type_t* args);
symbol_t* symbol_create_literal(lexical_value_t *token_data, semantic_type_t type);




/* --- INTERFACE PARAMETROS --- */
int count_params(asd_tree_t* param_node);
semantic_type_t* extract_and_store_params(table_t* table, asd_tree_t* param_node, int* out_num_args);
void check_argument_types(symbol_t* func_symbol, asd_tree_t* arg_node);


/*debug */
void print_arg_tree(asd_tree_t* node, int depth); 

/* --- INTERFACE CONTADORES DE OFFSETS --- */
// função para resetar o contador local ao iniciar uma função
void reset_local_offset(void);
#endif 