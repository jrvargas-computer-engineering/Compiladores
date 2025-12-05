#ifndef ASM_GEN_H
#define ASM_GEN_H

#include "tabela.h"
#include "iloc.h"

// Função principal que orquestra a geração
void generateAssembly(table_t *tabela_global, iloc_node_t *codigo_iloc);

#endif