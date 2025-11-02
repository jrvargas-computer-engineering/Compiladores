#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tabela.h"

#define STACK_MAX_SIZE 256  
#define TABLE_INITIAL_CAPACITY 16 
//#define DEBUG_ON

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


//TODO conferir realloc
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
   
    #ifdef DEBUG_ON
    printf("[symbol_create_func] Criando função '%s' com %d parâmetros:\n",
           symbol->key, symbol->num_args);
    for (int i = 0; i < symbol->num_args; i++) {
        printf("  tipo arg[%d] = %d\n", i, symbol->arg_types[i]);
    }
    #endif

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
    symbol->token_data = NULL; 
    symbol->arg_types = NULL;
    symbol->num_args = 0;
    
    return symbol;
}


int count_params(asd_tree_t* param_node) {
    if (param_node == NULL)
        return 0;

    // Só conta se o nó tem tipo válido
    int count = 0;
    if (param_node->data_type == SEMANTIC_TYPE_INT ||
        param_node->data_type == SEMANTIC_TYPE_FLOAT) {
        count = 1;
    }

    // O próximo argumento está sempre no primeiro filho, se existir
    if (param_node->number_of_children == 1) {
        count += count_params(param_node->children[0]);
    }

    return count;
}


static void _extract_recursive(
    table_t* table,
    asd_tree_t* node,
    semantic_type_t* type_array,
    int* index
) {
    if (node == NULL) {
        return;
    }

    const char* name = node->label;
    semantic_type_t type = node->data_type;

    /* guarda o tipo atual na posição index */
    type_array[*index] = type;

    /* checa duplicado e insere símbolo de parâmetro no novo escopo */
    if (table_find(table, name) != NULL) {
        yyerror_semantic("Parametro com nome duplicado.", 0, ERR_DECLARED);
    }
    symbol_t* param_sym = symbol_create_param(name, type, node->line);
    table_insert(table, param_sym);


    #ifdef DEBUG_ON
    printf("[_extract_recursive] Param %s (type=%d) -> index=%d\n",
           name ? name : "<anon>", type, *index);
    #endif
    (*index)++;
    #ifdef DEBUG_ON
    printf("[_extract_recursive] Novo index=%d (filhos=%d)\n",
           *index, node->number_of_children);
    #endif

    /* percorre TODOS os filhos (ordem esquerda -> direita) */
    for (int i = 0; i < node->number_of_children; i++) {
        _extract_recursive(table, node->children[i], type_array, index);
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
   
   
    #ifdef DEBUG_ON
    printf("[extract_and_store_params] num_args=%d\n", num_args);
    for (int i = 0; i < num_args; i++) {
        printf("[extract_and_store_params] arg_types[%d] = %d\n", i, arg_types[i]);
    }
    #endif

    return arg_types; 
}
static void _check_types_recursive(symbol_t* func, asd_tree_t* arg, int* index) {
    if (arg == NULL)
        return;

    // Verifica se este nó representa um argumento real
    if (arg->data_type == SEMANTIC_TYPE_INT ||
        arg->data_type == SEMANTIC_TYPE_FLOAT) {

        if (*index >= func->num_args) {
            yyerror_semantic("Argumentos em excesso na chamada da funcao.", arg->line, ERR_EXCESS_ARGS);
        }

        semantic_type_t expected = func->arg_types[*index];
        semantic_type_t provided = arg->data_type;
        if (expected != provided) {
            yyerror_semantic("Argumento de tipo incompativel.", arg->line, ERR_WRONG_TYPE_ARGS);
        }

        (*index)++;
    }

    // O próximo argumento está sempre no primeiro filho, se houver
    if (arg->number_of_children == 1) {
        _check_types_recursive(func, arg->children[0], index);
    }
}

void check_argument_types(symbol_t* func_symbol, asd_tree_t* arg_node) {
    
    #ifdef DEBUG_ON
    printf("[check_argument_types] Função '%s' com %d args esperados.\n",
       func_symbol->key, func_symbol->num_args);
    #endif

    if (func_symbol->num_args == 0 && arg_node == NULL)
        return;

    if (arg_node != NULL) {
        int index = 0;
        _check_types_recursive(func_symbol, arg_node, &index);
    }
}

void print_arg_tree(asd_tree_t* node, int depth) {
    if (!node) return;
    for (int i = 0; i < depth; i++) printf("  ");
    printf("arg: %s (%d filhos)\n", node->label, node->number_of_children);
    for (int i = 0; i < node->number_of_children; i++) {
        print_arg_tree(node->children[i], depth + 1);
    }
}
