#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tabela.h"

#define STACK_MAX_SIZE 256  
#define TABLE_INITIAL_CAPACITY 16 


/*
implementar pilha com vetor de ponteiros, do tipo da tabela
*/
static table_t* scope_stack[STACK_MAX_SIZE];
static int stack_top = -1;

void scope_stack_init(void) {
    stack_top = -1;
}

void scope_stack_push(table_t* table) {
    if (stack_top >= STACK_MAX_SIZE - 1) {
        fprintf(stderr, "Erro: Estouro da pilha de escopos (limite: %d)\n", STACK_MAX_SIZE);
        exit(EXIT_FAILURE);
    }
    stack_top++;
    scope_stack[stack_top] = table;
}

table_t* scope_stack_pop(void) {
    if (stack_top < 0) {
        return NULL; 
    }
    table_t* table = scope_stack[stack_top];
    stack_top--;
    return table;
}

table_t* scope_stack_peek(void) {
    if (stack_top < 0) {
        return NULL;
    }
    return scope_stack[stack_top];
}

symbol_t* stack_find_global(const char* key) {
    for (int i = stack_top; i >= 0; i--) {
        symbol_t* symbol = table_find(scope_stack[i], key);
        if (symbol != NULL) {
            return symbol; 
        }
    }
    return NULL; 
}

void scope_stack_free_all(void) {
    while (stack_top >= 0) {
        table_t* table = scope_stack_pop();
        table_free(table);
    }
}


table_t* table_create(void) {
    table_t* table = (table_t*) malloc(sizeof(table_t));
    table->count = 0;
    table->allocated_size = TABLE_INITIAL_CAPACITY;
    table->symbols = (symbol_t**) malloc(table->allocated_size * sizeof(symbol_t*));
    return table;
}

void table_free(table_t* table) {
    if (table == NULL) return;
    for (int i = 0; i < table->count; i++) {
        symbol_t* symbol = table->symbols[i];
        if (symbol != NULL) {
            free(symbol->key);
            if (symbol->token_data != NULL) {
                free(symbol->token_data->value); 
                free(symbol->token_data);       
            }
            if (symbol->nature == SYMBOL_FUNCAO) {
                free(symbol->arg_types);
            }            
            free(symbol);
        }
    }
    free(table->symbols);
    free(table);
}

void table_insert(table_t* table, symbol_t* symbol) {
    if (table == NULL || symbol == NULL) return;
    if (table->count >= table->allocated_size) {
        table->allocated_size *= 2;
        table->symbols = (symbol_t**) realloc(table->symbols, table->allocated_size * sizeof(symbol_t*));
    }    
    table->symbols[table->count] = symbol;
    table->count++;
}

symbol_t* table_find(table_t* table, const char* key) {
    if (table == NULL || key == NULL) return NULL;
    
    for (int i = 0; i < table->count; i++) {
        if (strcmp(table->symbols[i]->key, key) == 0) {
            return table->symbols[i];
        }
    }
    return NULL; 
}


static symbol_t* _symbol_alloc(lexical_value_t *token_data, symbol_nature_t nature, semantic_type_t type) {
    symbol_t* symbol = (symbol_t*) malloc(sizeof(symbol_t));
    
    symbol->key = strdup(token_data->value);
    
    symbol->nature = nature;              
    symbol->data_type = type;               
    symbol->token_data = token_data;     
    
    symbol->line = token_data->line;

    symbol->arg_types = NULL;              
    symbol->num_args = 0;                  
    
    return symbol;
}

symbol_t* symbol_create_var(lexical_value_t *token_data, semantic_type_t type) {
    return _symbol_alloc(token_data, SYMBOL_ID, type);
}

symbol_t* symbol_create_literal(lexical_value_t *token_data, semantic_type_t type) {
    return _symbol_alloc(token_data, SYMBOL_LIT, type);
}

symbol_t* symbol_create_func(lexical_value_t *token_data, semantic_type_t return_type, int num_args, semantic_type_t* args) {
    symbol_t* symbol = _symbol_alloc(token_data, SYMBOL_FUNCAO, return_type);    
    symbol->num_args = num_args;
    if (num_args > 0 && args != NULL) {
        int size = num_args * sizeof(semantic_type_t);
        symbol->arg_types = (semantic_type_t*) malloc(size);
        memcpy(symbol->arg_types, args, size);
    }
    return symbol;
}

symbol_t* symbol_create_param(const char* key, semantic_type_t type, int line) {
    symbol_t* symbol = (symbol_t*) malloc(sizeof(symbol_t));
    if (symbol == NULL) {
        fprintf(stderr, "Erro: Falha ao alocar memoria para simbolo de parametro\n");
        exit(EXIT_FAILURE); 
    }
    symbol->key = strdup(key);
    symbol->nature = SYMBOL_ID;
    symbol->data_type = type;                  
    symbol->line = line;                       
    // 4. Preenche os campos que não se aplicam com NULL/0
    symbol->token_data = NULL; // Não temos o token original
    symbol->arg_types = NULL;
    symbol->num_args = 0;
    
    return symbol;
}

int count_params(asd_tree_t* param_node) {
    if (param_node == NULL) {
        return 0; 
    }
    int count = 1;    
    if (param_node->number_of_children > 0) {
        count += count_params(param_node->children[0]);
    }
    return count;
}

static void _extract_recursive(
    table_t* table,             // O novo escopo da função
    asd_tree_t* node,           // O nó do parâmetro atual
    semantic_type_t* type_array, // O vetor para salvar os tipos
    int* index                  // O índice atual no vetor
) {
    if (node == NULL) {
        return;
    }
    const char* name = node->label;
    semantic_type_t type = node->data_type;    
    type_array[*index] = type;
    
    // Verifica se o parâmetro já foi declarado NESTE escopo
    if (table_find(table, name) != NULL) {
        yyerror_semantic("Parametro com nome duplicado.", 0, ERR_DECLARED);
    }
    symbol_t* param_sym = symbol_create_param(name, type, 0 /* node->line */);
    table_insert(table, param_sym);
    
    (*index)++;
    if (node->number_of_children > 0) {
        _extract_recursive(table, node->children[0], type_array, index);
    }
}
semantic_type_t* extract_and_store_params(
    table_t* table,         // O novo escopo (tabela_funcao)
    asd_tree_t* param_node, // A árvore de parâmetros ($4)
    int* out_num_args       // Onde salvar a contagem
) {
    int num_args = count_params(param_node);
    *out_num_args = num_args;
    
    if (num_args == 0) {
        return NULL; 
    }
    semantic_type_t* arg_types = (semantic_type_t*) malloc(num_args * sizeof(semantic_type_t));    
    int index = 0;
    _extract_recursive(table, param_node, arg_types, &index);
    return arg_types; 
}