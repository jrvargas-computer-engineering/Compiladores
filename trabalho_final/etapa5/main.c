/* Grupo A - Alunos:
 Juliana Rodrigres de Vargas- 00337553
 Sofia Popsin Gomes - 00313563*/

#include <stdio.h>
#include "asd.h"
#include "tabela.h"
#include "iloc.h"

extern int yyparse(void);
extern int yylex_destroy(void);
asd_tree_t *arvore = NULL;

int main (int argc, char **argv) {
  scope_stack_init(); 
  int ret = yyparse();

  // asd_print_graphviz(arvore);
  // asd_free(arvore);
  // scope_stack_free_all();     
  
  if (ret == 0 && arvore != NULL) {
    // Cast para o tipo correto da árvore
    asd_tree_t *root = (asd_tree_t*) arvore;
    
    // 1. Imprime o código gerado para stdout (Saída Padrão)
    asd_print_code(root->code_head);
    
    // 2. Exporta a árvore para debug em stderr ou arquivo
    // Não imprima graphviz na stdout, senão mistura com o código ILOC!
    // asd_print_graphviz(arvore);  
    // Importante: Liberar ANTES de destruir a árvore
    asd_free_iloc(root->code_head);
    asd_free(root);
  }

  yylex_destroy();
  return ret;
}