/* Grupo A - Alunos:
 Juliana Rodrigres de Vargas- 00337553
 Sofia Popsin Gomes - 00313563*/

#include <stdio.h>
 #include "asd.h"
 extern int yyparse(void);
 extern int yylex_destroy(void);
 asd_tree_t *arvore = NULL;
 int main (int argc, char **argv)
 {
 int ret = yyparse();
 asd_print_graphviz(arvore);
 asd_free(arvore);
 yylex_destroy();
 return ret;
 }