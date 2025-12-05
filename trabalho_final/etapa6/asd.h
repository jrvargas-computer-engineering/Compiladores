/* Grupo A - Alunos:
 Juliana Rodrigres de Vargas- 00337553
 Sofia Popsin Gomes - 00313563*/
 
#ifndef _ARVORE_H_
#define _ARVORE_H_

#include "iloc.h"

//add e4
typedef enum {
    SEMANTIC_TYPE_INT,            
    SEMANTIC_TYPE_FLOAT          
} semantic_type_t;

typedef struct asd_tree {
  char *label;
  double value; 
  int number_of_children;
  struct asd_tree **children;
  semantic_type_t data_type; //add e4
  int line;

  // Ponteiro para o início e fim do código ILOC gerado por este nó
  iloc_node_t *code_head; 
  iloc_node_t *code_tail; 

  // Nome do registrador temporário onde o resultado deste nó está armazenado
  // Ex: se este nó calcula "2+3", temp pode ser "r5"
  char *temp;

} asd_tree_t;

/*
 * Função asd_new, cria um nó sem filhos com o label informado.
 */
asd_tree_t *asd_new(const char *label);

/*
 * Função asd_tree, libera recursivamente o nó e seus filhos.
 */
void asd_free(asd_tree_t *tree);

/*
 * Função asd_add_child, adiciona child como filho de tree.
 */
void asd_add_child(asd_tree_t *tree, asd_tree_t *child);

/*
 * Função asd_print, imprime recursivamente a árvore.
 */
void asd_print(asd_tree_t *tree);

/*
 * Função asd_print_graphviz, idem, em formato DOT
 */
void asd_print_graphviz (asd_tree_t *tree);

void asd_print_code(iloc_node_t *head);

#endif //_ARVORE_H_
