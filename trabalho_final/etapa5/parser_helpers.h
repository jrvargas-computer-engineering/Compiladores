/* Grupo A - Alunos:
 Juliana Rodrigres de Vargas- 00337553
 Sofia Popsin Gomes - 00313563*/
 
#include <stdlib.h>
#include <stdio.h>
#include "asd.h" 
#include "tabela.h"   
#include "iloc.h"

semantic_type_t last_type(asd_tree_t* bloco);
asd_tree_t* new_node_from_lexval(lexical_value_t *lexval);
asd_tree_t* new_node_from_binary_op(const char *label, asd_tree_t *child1, asd_tree_t *child2);
asd_tree_t* new_node_from_unary_op(const char *label, asd_tree_t *child);
asd_tree_t* new_node_from_binary_op_arit(const char *label, asd_tree_t *child1, asd_tree_t *child2);
asd_tree_t* new_node_from_binary_op_rel_log(const char *label, asd_tree_t *child1, asd_tree_t *child2);