/* Grupo A - Alunos:
 Juliana Rodrigres de Vargas- 00337553
 Sofia Popsin Gomes - 00313563*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "iloc.h"

// Variáveis estáticas para contagem (invisíveis fora deste arquivo)
static int temp_count = 0;
static int label_count = 0;

/*
 * Função create_instruction: Cria um novo nó de instrução ILOC.
 * Inicializa os ponteiros next e prev como NULL.
 */
iloc_node_t* asd_new_iloc(char *label, char *opcode, char *arg1, char *arg2, char *arg3) {
    iloc_node_t *new_node = (iloc_node_t*) malloc(sizeof(iloc_node_t));
    
    if (new_node == NULL) {
        fprintf(stderr, "[Erro] Falha ao alocar memória para instrução ILOC.\n");
        exit(1);
    }

    // strdup aloca memória e copia a string. Se o argumento for NULL, mantemos NULL.
    new_node->label = label ? strdup(label) : NULL;
    new_node->opcode = opcode ? strdup(opcode) : NULL;
    new_node->arg1 = arg1 ? strdup(arg1) : NULL;
    new_node->arg2 = arg2 ? strdup(arg2) : NULL;
    new_node->arg3 = arg3 ? strdup(arg3) : NULL;
    
    new_node->next = NULL;
    new_node->prev = NULL;

    return new_node;
}

/*
 * Função concat_lists: Une duas listas encadeadas.
 * Retorna o ponteiro para o início da lista unida.
 */
iloc_node_t* asd_concat_lists(iloc_node_t *list1, iloc_node_t *list2) {
    // Casos base: se uma das listas for vazia, retorna a outra
    if (list1 == NULL) return list2;
    if (list2 == NULL) return list1;

    // Encontrar o final da list1
    iloc_node_t *current = list1;
    while (current->next != NULL) {
        current = current->next;
    }

    // Conectar o final da list1 ao início da list2
    current->next = list2;
    list2->prev = current;

    // Retorna o início da lista combinada (que ainda é o início da list1)
    return list1;
}

/*
 * Função append_instruction: Adiciona uma única instrução ao final de uma lista.
 * Na prática, é um caso especial de concatenação.
 */
iloc_node_t* asd_append_instruction(iloc_node_t *list, iloc_node_t *instruction) {
    if (instruction != NULL) {
        // Segurança: Garante que a instrução a ser adicionada é o fim da lista
        instruction->next = NULL; 
    }
    return asd_concat_lists(list, instruction);
}

/*
 * Função auxiliar para liberar memória
 */
void asd_free_iloc(iloc_node_t *head) {
    iloc_node_t *current = head;
    while (current != NULL) {
        iloc_node_t *next = current->next;
        
        // Libera as strings se existirem
        if (current->label) free(current->label);
        if (current->opcode) free(current->opcode);
        if (current->arg1) free(current->arg1);
        if (current->arg2) free(current->arg2);
        if (current->arg3) free(current->arg3);
        
        // Libera o próprio nó
        free(current);
        
        current = next;
    }
}

/*
 * Gera um nome de registrador temporário único.
 * Ex: "r0", "r1", "r2"...
 */
char* make_temp(void) {
    // Buffer estático ou local grande o suficiente para o nome
    // r + int (max 10 digitos) + \0 sobra espaço em 64 bytes
    char buffer[64];
    
    // Formata a string "r" seguido do número atual
    // O operador ++ pós-fixado usa o valor atual e depois incrementa
    snprintf(buffer, 64, "r%d", temp_count++);
    
    // Retorna uma CÓPIA da string (alocada dinamicamente).
    // É crucial usar strdup para que o ponteiro retornado não aponte 
    // para uma variável local que deixará de existir.
    return strdup(buffer);
}

/*
 * Gera um nome de rótulo único.
 * Ex: "L0", "L1", "L2"...
 */
char* make_label(void) {
    char buffer[64];
    
    // Formata a string "L" seguido do número atual
    snprintf(buffer, 64, "L%d", label_count++);
    
    return strdup(buffer);
}

void asd_print_code(iloc_node_t *head) {
    iloc_node_t *current = head;
    while (current != NULL) {
        // 1. Imprime Label se houver
        if (current->label) {
            printf("%s: ", current->label);
        }

        // 2. Formatação baseada no Opcode
        if (current->opcode) {
            printf("%s ", current->opcode);
            
            // Grupo de Controle de Fluxo (usam ->)
            if (strcmp(current->opcode, "jumpI") == 0) {
                // jumpI -> L1
                printf("-> %s", current->arg1);
            }
            else if (strcmp(current->opcode, "jump") == 0) {
                // jump -> r1
                printf("-> %s", current->arg1);
            }
            else if (strcmp(current->opcode, "cbr") == 0) {
                // cbr r1 -> L2, L3
                printf("%s -> %s, %s", current->arg1, current->arg2, current->arg3);
            }
            else if (strncmp(current->opcode, "cmp_", 4) == 0) {
                // cmp_EQ r1, r2 -> r3
                printf("%s, %s -> %s", current->arg1, current->arg2, current->arg3);
            }
            // Grupo Store (storeAI r1 => r2, c3)
            else if (strncmp(current->opcode, "store", 5) == 0 || 
                     strncmp(current->opcode, "cstore", 6) == 0) {
                if (current->arg3)
                    printf("%s => %s, %s", current->arg1, current->arg2, current->arg3);
                else
                    printf("%s => %s", current->arg1, current->arg2); // store r1 => r2
            }
            // Grupo Load (loadAI r1, c2 => r3) e Aritmética
            else {
                if (current->arg1 && current->arg2 && current->arg3) {
                    // add r1, r2 => r3  OU  loadAI r1, c2 => r3
                    printf("%s, %s => %s", current->arg1, current->arg2, current->arg3);
                }
                else if (current->arg1 && current->arg3) { // Ex: loadI c1 => r2 (arg2 null)
                     printf("%s => %s", current->arg1, current->arg3);
                }
                else if (current->arg1 && current->arg2) { // Ex: i2i r1 => r2
                     printf("%s => %s", current->arg1, current->arg2);
                }
            }
        }
        printf("\n");
        current = current->next;
    }
}