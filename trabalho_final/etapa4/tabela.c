#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tabela.h"
#include "diretivas.h"
#define STACK_MAX_SIZE 256  
#define TABLE_INITIAL_CAPACITY 16 

/*  =====================================================
    ====================== Debug ========================
    =====================================================
*/
void print_arg_tree(asd_tree_t* node, int depth) {
    if (!node) return;
    for (int i = 0; i < depth; i++) printf("  ");
    printf("arg: %s (%d filhos)\n", node->label, node->number_of_children);
    for (int i = 0; i < node->number_of_children; i++) {
        print_arg_tree(node->children[i], depth + 1);
    }
}


/*  =====================================================
    =============== Tabela de Escopos ===================
    =====================================================
    O escopo pode ser global, local da função 
    e local de um bloco, sendo que este pode ser recursivamente
    aninhado. Uma forma de se implementar estas 
    regras de escopo é através de uma pilha de tabelas
    de símbolos. Para verificar se uma variável foi declarada, 
    verifica-se primeiramente no escopo atual (topo
    da pilha) e enquanto não encontrar, deve-se descer na
    pilha (sem desempilhar) até chegar no escopo global
    (base da pilha, sempre presente). 
*/ 

static table_t* scope_stack[STACK_MAX_SIZE];
static int stack_top = -1;

void scope_stack_init(void) {
    stack_top = -1;
}

void scope_stack_push(table_t* table) {
    if (stack_top >= STACK_MAX_SIZE - 1) {
        fprintf(stderr, "[ERROR] Estouro da pilha de escopos (limite: %d)\n", STACK_MAX_SIZE);
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



/*  =====================================================
    ===================== Símbolos ======================
    =====================================================
    Todos os identificadores devem ter sido declarados no
    momento do seu uso, seja como variável, seja como
    função. Todas as entradas na tabela de símbolos de
    vem ter um tipo associado conforme a declaração,
    verificando-se se não houve dupla declaração ou se o
    símbolo não foi declarado. 
*/
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
    printf("[DEBUG][symbol_create_func] Criando função '%s' com %d parâmetros:\n", 
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
        fprintf(stderr, "[ERROR] Falha ao alocar memoria para simbolo de parametro\n"); 
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


/*  =====================================================
    ============== Contagem de Parâmetros ===============
    =====================================================
    A lista de argumentos fornecidos em uma chamada de
    função deve ser verificada contra a lista de parâmetros
    formais na declaração da mesma função. Cada chamada 
    de função deve prover um argumento para cada
    parâmetro, e ter o seu tipo compatıvel. Tais verificações
    devem ser realizadas levando-se em conta as informações 
    registradas na tabela de sımbolos, registradas no
    momento da declaração/definição da função.
    */

static int is_operator_label(const char* label) {
    if (label == NULL) return 0;
    const char* ops[] = {"+", "-", "*", "/", "%", ">", "<", ">=", "<=", "==", "!=", "&&", "||"};
    for (int i = 0; i < (int)(sizeof(ops)/sizeof(ops[0])); i++) {
        if (strcmp(label, ops[i]) == 0)
            return 1;
    }
    return 0;
}

int count_params(asd_tree_t* param_node) {
    #ifdef DEBUG_ON
    printf("\n[DEBUG] Iniciando contagem de argumentos...\n"); 
    print_arg_tree(param_node, 0);
    #endif

    if (param_node == NULL){
        return 0;
    }


    if (param_node->label && strncmp(param_node->label, "call", 4) == 0) {
        return 1 + count_params(param_node->children[1]);
    }
    if (param_node->number_of_children == 1) {
        return 1 + count_params(param_node->children[0]);
    }
    if (param_node->number_of_children > 1) {
        int count = 0;
        //GAMBIARRA AQUI, PARA RESOLVER CASOS (NUMERO + NUMERO)
        if (param_node->label && is_operator_label(param_node->label)){
            count--; 
        }
        for (int i = 0; i < param_node->number_of_children; i++) {
            asd_tree_t* child = param_node->children[i];
            if (child == NULL) continue;
            if (child->label && strncmp(child->label, "call", 4) == 0) {
                count++;
                continue;
            }

            if (child->number_of_children > 0) {
                count += count_params(child);
            }
            else if (child->data_type == SEMANTIC_TYPE_INT || child->data_type == SEMANTIC_TYPE_FLOAT) {
                count++;
            }
        }
        return count;
    }
    if (param_node->number_of_children == 0) {
        if (param_node->data_type == SEMANTIC_TYPE_INT ||
            param_node->data_type == SEMANTIC_TYPE_FLOAT) {
            return 1;
        }
    }
    return 0;
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
    type_array[*index] = type;

    if (table_find(table, name) != NULL) {
        yyerror_semantic("Uso duplicado. Parametro com nome duplicado.", 0, ERR_DECLARED); 
    }
    symbol_t* param_sym = symbol_create_param(name, type, node->line);
    table_insert(table, param_sym);


    #ifdef DEBUG_ON
    printf("[DEBUG][_extract_recursive] Param %s (type=%d) -> index=%d\n",
           name ? name : "<anon>", type, *index);
    #endif
    (*index)++;
    #ifdef DEBUG_ON
    printf("[DEBUG][_extract_recursive] Novo index=%d (filhos=%d)\n", 
           *index, node->number_of_children);
    #endif

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
    printf("[DEBUG][extract_and_store_params] num_args=%d\n", num_args); 
    for (int i = 0; i < num_args; i++) {
        printf("[DEBUG][extract_and_store_params] arg_types[%d] = %d\n", i, arg_types[i]); 
    }
    #endif
    return arg_types; 
}



static void _check_types_recursive(symbol_t* func, asd_tree_t* arg, int* index) {    
    #ifdef DEBUG_ON
    printf("[ARG CHECK] nó='%s', tipo=%d, filhos=%d, index=%d\n", 
       arg->label ? arg->label : "<sem-label>",
       arg->data_type, arg->number_of_children, *index);
    #endif
    if (!arg) return;
    if (arg->data_type == SEMANTIC_TYPE_INT || arg->data_type == SEMANTIC_TYPE_FLOAT) {
        if (*index >= func->num_args) {
            yyerror_semantic("Argumentos em excesso na chamada da funcao.", arg->line, ERR_EXCESS_ARGS); 
        }
        if (func->arg_types[*index] != arg->data_type) {
            yyerror_semantic("Tipo incorreto. Argumento de tipo incompativel.", arg->line, ERR_WRONG_TYPE_ARGS); 
        }
        (*index)++;
        return;  
    }
    for (int i = 0; i < arg->number_of_children; i++) {
        _check_types_recursive(func, arg->children[i], index);
    }
}


void check_argument_types(symbol_t* func_symbol, asd_tree_t* arg_node) {
    #ifdef DEBUG_ON
    printf("[DEBUG][check_argument_types] Funcao '%s' com %d args esperados.\n", 
       func_symbol->key, func_symbol->num_args); 
    #endif
    if (func_symbol->num_args == 0 && arg_node == NULL)
        return;

    if (arg_node != NULL) {
        int index = 0;
        _check_types_recursive(func_symbol, arg_node, &index);
    }
}


