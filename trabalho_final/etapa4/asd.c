/* Grupo A - Alunos:
 Juliana Rodrigres de Vargas- 00337553
 Sofia Popsin Gomes - 00313563*/
 
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "asd.h"
#include "diretivas.h"

asd_tree_t *asd_new(const char *label)
{
  asd_tree_t *ret = NULL;
  ret = calloc(1, sizeof(asd_tree_t));
  if (ret != NULL){
    ret->label = strdup(label);
    ret->number_of_children = 0;
    ret->children = NULL;
    ret->value = 0;
    ret->data_type = SEMANTIC_TYPE_UNDEFINED; 
    
    #ifdef DEBUG_ON
    printf("[DEBUG] Criando nó: %s (%p)\n", label, (void*)ret);
    #endif

  }
  return ret;
}

void asd_free(asd_tree_t *tree)
{
  if (tree != NULL){
    //printf("[DEBUG] Liberando nó: %s (%p)\n", tree->label, (void*)tree);

    int i;
    for (i = 0; i < tree->number_of_children; i++){
      asd_free(tree->children[i]);
    }
    free(tree->children);
    free(tree->label);
    free(tree);
  }else{
    #ifdef DEBUG_ON
    printf("ASDFREE Erro: %s recebeu parâmetro tree = %p.\n", __FUNCTION__, tree);
    #endif
    free(NULL);
  }
}

void asd_add_child(asd_tree_t *tree, asd_tree_t *child)
{
  if (tree != NULL && child != NULL){
    tree->number_of_children++;
    tree->children = realloc(tree->children, tree->number_of_children * sizeof(asd_tree_t*));
    tree->children[tree->number_of_children-1] = child;
  }else{
    #ifdef DEBUG_ON
    printf("ASD_ADD_CHILD Erro: %s recebeu parâmetro tree = %p / %p.\n", __FUNCTION__, tree, child);
    #endif
  }
}

static void _asd_print (FILE *foutput, asd_tree_t *tree, int profundidade)
{
  int i;
  if (tree != NULL){
    fprintf(foutput, "%d%*s: Nó '%s' tem %d filhos:\n", profundidade, profundidade*2, "", tree->label, tree->number_of_children);
    for (i = 0; i < tree->number_of_children; i++){
      _asd_print(foutput, tree->children[i], profundidade+1);
    }
  }else{
    #ifdef DEBUG_ON
    printf("_ASD_PRINT Erro: %s recebeu parâmetro tree = %p.\n", __FUNCTION__, tree);
    #endif
  }
}

void asd_print(asd_tree_t *tree)
{
  FILE *foutput = stderr;
  if (tree != NULL){
    _asd_print(foutput, tree, 0);
  }else{
    #ifdef DEBUG_ON
    printf("ASD_PRINT Erro: %s recebeu parâmetro tree = %p.\n", __FUNCTION__, tree);
    #endif
  }
}

static void _asd_print_graphviz (FILE *foutput, asd_tree_t *tree)
{
  int i;
  if (tree != NULL){
    //alterei aqui
    fprintf(foutput, "  %ld [ label=\"%s\" ];\n", (long)tree, tree->label);
    for (i = 0; i < tree->number_of_children; i++){
      fprintf(foutput, "  %ld -> %ld;\n", (long)tree, (long)tree->children[i]);
      _asd_print_graphviz(foutput, tree->children[i]);
    }
  }else{
    #ifdef DEBUG_ON
    printf("_ASD_PRINT_GRAPHVIZ Erro: %s recebeu parâmetro tree = %p.\n", __FUNCTION__, tree);
    #endif
  }
}

void asd_print_graphviz(asd_tree_t *tree)
{

  FILE *foutput = stdout;  
  if (tree != NULL){
    fprintf(foutput, "digraph grafo {\n");
    _asd_print_graphviz(foutput, tree);
    fprintf(foutput, "}\n");
  }else{
    #ifdef DEBUG_ON
    printf("ASD_PRINT_GRAPHVIZ Erro: %s recebeu parâmetro tree = %p.\n", __FUNCTION__, tree);
    #endif
  }
}
