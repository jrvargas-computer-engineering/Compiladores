/* Grupo A - Alunos:
 Juliana Rodrigres de Vargas- 00337553
 Sofia Popsin Gomes - 00313563*/

#include <stdio.h>
#include "asd.h"
#include "tabela.h"
extern int yyparse(void);
extern int yylex_destroy(void);
asd_tree_t *arvore = NULL;

int main (int argc, char **argv) {
   scope_stack_init(); 
   int ret = yyparse();
   asd_print_graphviz(arvore);
   asd_free(arvore);
   scope_stack_free_all();
   yylex_destroy();
   return ret;
 }