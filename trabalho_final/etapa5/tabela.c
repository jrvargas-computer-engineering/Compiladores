#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tabela.h"
#include "diretivas.h"
#define STACK_MAX_SIZE 256  
#define TABLE_INITIAL_CAPACITY 16
#define BYTE_SIZE 4 // Inteiros e floats ocupam 4 bytes 

static int global_byte_count = 0; // Contador para rbss
static int local_byte_count = 0;  // Contador para rfp

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
    
    // Realocação se necessário
    if (table->count >= table->allocated_size) {
        table->allocated_size *= 2;
        table->symbols = (symbol_t**) realloc(table->symbols, table->allocated_size * sizeof(symbol_t*));
    }    
    
    // --- LÓGICA DE ENDEREÇAMENTO (ETAPA 5) ---
    // Apenas Variáveis e Parâmetros precisam de endereço em memória. 
    if (symbol->nature == SYMBOL_ID) { // Se for identificador (variável ou param)
        
        // Verifica se a tabela atual é a Global (base da pilha de escopos)
        // scope_stack[0] é sempre o escopo global
        if (table == scope_stack[0]) {
            symbol->is_global = 1;
            symbol->offset = global_byte_count;
            global_byte_count += BYTE_SIZE;
        } else {
            symbol->is_global = 0;
            symbol->offset = local_byte_count;
            local_byte_count += BYTE_SIZE;
        }
        
        #ifdef DEBUG_ON
        printf("[DEBUG] Var '%s' alocada. Global? %d. Offset: %d\n", 
               symbol->key, symbol->is_global, symbol->offset);
        #endif
    } else {
        // Literais e Funções não ocupam espaço no frame de dados/pilha dessa forma
        symbol->offset = -1;
        symbol->is_global = -1;
    }

    // Inserção original
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
int count_params(asd_tree_t* list_node) {
    if (list_node == NULL) {
        return 0; 
    }
    return list_node->number_of_children;
}




/* Em tabela.c */
semantic_type_t* extract_and_store_params(
    table_t* table,
    asd_tree_t* param_list_node,
    int* out_num_args
) {
    int num_args = count_params(param_list_node);
    *out_num_args = num_args;
    
    if (num_args == 0) {
        return NULL; 
    }

    semantic_type_t* arg_types = (semantic_type_t*) malloc(num_args * sizeof(semantic_type_t));    
    
    for (int i = 0; i < num_args; i++) {
        asd_tree_t* node = param_list_node->children[i];

        const char* name = node->label;
        semantic_type_t type = node->data_type;    
        
        arg_types[i] = type;
        
        if (table_find(table, name) != NULL) {
            yyerror_semantic("Parametro com nome duplicado.", node->line, ERR_DECLARED);
        }
        
        symbol_t* param_sym = symbol_create_param(name, type, node->line);
        table_insert(table, param_sym);
    }
    
    return arg_types; 
}



void check_argument_types(symbol_t* func_symbol, asd_tree_t* arg_list_node) {
    if (func_symbol->num_args == 0 && arg_list_node == NULL) {
        return;
    }

    for (int i = 0; i < func_symbol->num_args; i++) {        
        asd_tree_t* arg_node = arg_list_node->children[i];
        semantic_type_t expected_type = func_symbol->arg_types[i];
        semantic_type_t provided_type = arg_node->data_type;

        if (expected_type != provided_type) {
            yyerror_semantic("Argumento de tipo incompativel.", arg_node->line, ERR_WRONG_TYPE_ARGS);
        }
    }
}


/*  =====================================================
    ============== Contadores de Offsets =================
    =====================================================
    Modificar a inserção na Tabela de Símbolos para
    calcular os endereços (offsets) das variáveis.
    Manter um contador de bytes para variáveis Globais
    (base rbss) e um contador para variáveis Locais
    (base rfp).
*/
// Função para ser chamada no parser quando começar uma nova função
void reset_local_offset(void) {
    local_byte_count = 0;
}