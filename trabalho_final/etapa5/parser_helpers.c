#include "parser_helpers.h"
/*  =====================================================
    =================== Funcoes =========================
    =====================================================
*/ 

//add e4
semantic_type_t last_type(asd_tree_t* bloco) {
    /*
    Validacao retirada em resultado ao comentario
    *O tipo de dado pode ser int ou float, não tem como ser SEMANTIC_TYPE_UNDEFINED*
    if (!bloco) return NULL;
    */
    
    asd_tree_t* current = bloco;
    while (current->number_of_children > 0) {
        current = current->children[current->number_of_children - 1];
    }
    return current->data_type;
}

//new node from token/lex value
//lex values are e.g $1, $2, NULL
asd_tree_t* new_node_from_lexval(lexical_value_t *lexval) {
    if (lexval == NULL) return NULL;
    asd_tree_t *node = asd_new(lexval->value);    
    //adicionado E4
    node->line = lexval->line;
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
        yyerror_semantic("Tipos incompativeis em operacao aritmetica.", child1->line, ERR_WRONG_TYPE);
        //add e4
        return NULL;

    }

    asd_tree_t *node = asd_new(label);
    asd_add_child(node, child1);
    asd_add_child(node, child2);

    node->line = child1->line;  
    node->data_type = child1->data_type; 
    return node;
}


asd_tree_t* new_node_from_binary_op_rel_log(const char *label, asd_tree_t *child1, asd_tree_t *child2) {
    if (child1->data_type != child2->data_type) {
        yyerror_semantic("Tipos incompativeis em operacao relacional/logica.", child1->line, ERR_WRONG_TYPE); 
        //add e4
        return NULL;
    }
    asd_tree_t *node = asd_new(label);
    asd_add_child(node, child1); 
    asd_add_child(node, child2); 
    node->line = child1->line;  
    node->data_type = SEMANTIC_TYPE_INT; 
    return node;
}