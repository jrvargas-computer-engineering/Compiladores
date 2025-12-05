/* Grupo A - Alunos:
 Juliana Rodrigres de Vargas- 00337553
 Sofia Popsin Gomes - 00313563*/

#include <stdio.h>
#include "asd.h"
#include "tabela.h"
#include "iloc.h"
#include "asm_gen.h"

extern int yyparse(void);
extern int yylex_destroy(void);

// Referências globais definidas no parser.y
asd_tree_t *arvore = NULL;
extern table_t* tabela_global_obj; // <--- 2. Declare a tabela externa

int main (int argc, char **argv) {
  scope_stack_init(); 
  int ret = yyparse();

  // asd_print_graphviz(arvore);
  // asd_free(arvore);
  // scope_stack_free_all();     
  
  if (ret == 0 && arvore != NULL) {
    // Cast para o tipo correto da árvore
    asd_tree_t *root = (asd_tree_t*) arvore;
    
    // --- ALTERAÇÃO PARA ETAPA 6 ---
    
    // 3. NÃO IMPRIMA MAIS O ILOC NA SAÍDA PADRÃO!
    // O montador (gcc/as) não entenderá instruções ILOC.
    // asd_print_code(root->code_head);
    
    // 4. Chame o Gerador de Assembly
    generateAssembly(tabela_global_obj, root->code_head);

    // Exporta a árvore para debug em stderr ou arquivo
    // Não imprima graphviz na stdout, senão mistura com o código ILOC!
    // asd_print_graphviz(arvore);  

    // // 5. Limpeza de Memória
    // asd_free_iloc(root->code_head);
    // asd_free(root);

    // // Agora liberamos a tabela global (que não foi liberada no parser)
    // if (tabela_global_obj != NULL) {
    //     table_free(tabela_global_obj);
    // }
  }

  yylex_destroy();
  return ret;
}