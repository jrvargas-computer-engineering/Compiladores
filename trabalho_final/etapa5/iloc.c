/* Grupo A - Alunos:
 Juliana Rodrigres de Vargas- 00337553
 Sofia Popsin Gomes - 00313563*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "iloc.h"

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
    return asd_concat_lists(list, instruction);
}

/*
 * Função auxiliar para liberar memória
 */
void asd_free_iloc(iloc_node_t *head) {
    iloc_node_t *current = head;
    while (current != NULL) {
        iloc_node_t *next = current->next;
        
        if (current->label) free(current->label);
        if (current->opcode) free(current->opcode);
        if (current->arg1) free(current->arg1);
        if (current->arg2) free(current->arg2);
        if (current->arg3) free(current->arg3);
        free(current);
        
        current = next;
    }
}