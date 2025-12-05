#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "asm_gen.h"

// Início da área de temporários na pilha (para não colidir com variáveis locais)
#define TEMP_BASE_OFFSET 256 

/* * Auxiliar: Identifica se é temporário (r0, r1...) 
 */
int is_temp(char *reg) {
    return (reg[0] == 'r' && isdigit(reg[1]));
}

/* * Auxiliar: Calcula o endereço de pilha para um temporário ou variável
 * Retorna uma string no formato "-N(%rbp)" ou o nome da global "var(%rip)"
 */
void get_asm_addr(char *iloc_op, char *buffer) {
    if (iloc_op == NULL) return;

    // Caso 1: Registrador Temporário (r0, r1...) -> Pilha (Área de Temps)
    if (is_temp(iloc_op)) {
        int reg_num = atoi(iloc_op + 1); // Pula o 'r' e pega o número
        // Mapeia r0 -> -260(%rbp), r1 -> -264(%rbp)...
        int offset = TEMP_BASE_OFFSET + (reg_num + 1) * 4;
        sprintf(buffer, "-%d(%%rbp)", offset);
    } 
    // Caso 2: Registrador de Base Global (rbss) -> Variável Global
    else if (strcmp(iloc_op, "rbss") == 0) {
        // Isso geralmente é tratado direto na instrução loadAI/storeAI
        // mas deixamos aqui por segurança.
        strcpy(buffer, "%rip"); 
    }
    // Caso 3: Registrador de Base Local (rfp) -> Pilha (Área de Locais)
    else if (strcmp(iloc_op, "rfp") == 0) {
        strcpy(buffer, "%rbp");
    }
    // Caso 4: Literais (números)
    else if (isdigit(iloc_op[0]) || iloc_op[0] == '-') {
        sprintf(buffer, "$%s", iloc_op);
    }
    // Caso 5: Labels ou Globais Diretos
    else {
        sprintf(buffer, "%s", iloc_op);
    }
}

/**
 * Traduz uma única instrução ILOC para Assembly
 */
void translateInstruction(iloc_node_t *node) {
    if (!node) return;

    // Se tiver rótulo, imprime (ex: "L1:")
    if (node->label) {
        printf("%s:\n", node->label);
    }

    if (!node->opcode) return;

    char op1[64], op2[64], op3[64];
    // Prepara os operandos (se existirem)
    if (node->arg1) get_asm_addr(node->arg1, op1);
    if (node->arg2) get_asm_addr(node->arg2, op2);
    if (node->arg3) get_asm_addr(node->arg3, op3);

    // --- TRADUÇÃO DAS OPERAÇÕES ---

    // 1. Carregar Literal: loadI 10 => r1
    // Assembly: movl $10, -addr_r1(%rbp)
    if (strcmp(node->opcode, "loadI") == 0) {
        printf("\tmovl\t%s, %s\n", op1, op3);
    }
    
    // 2. Aritmética: add r1, r2 => r3
    // Como não podemos somar mem+mem, usamos %eax como ponte
    // movl r1, %eax
    // addl r2, %eax
    // movl %eax, r3
    else if (strcmp(node->opcode, "add") == 0) {
        printf("\tmovl\t%s, %%eax\n", op1);
        printf("\taddl\t%s, %%eax\n", op2);
        printf("\tmovl\t%%eax, %s\n", op3);
    }
    else if (strcmp(node->opcode, "sub") == 0) {
        printf("\tmovl\t%s, %%eax\n", op1);
        printf("\tsubl\t%s, %%eax\n", op2);
        printf("\tmovl\t%%eax, %s\n", op3);
    }
    else if (strcmp(node->opcode, "mult") == 0) {
        printf("\tmovl\t%s, %%eax\n", op1);
        printf("\timull\t%s, %%eax\n", op2);
        printf("\tmovl\t%%eax, %s\n", op3);
    }

    // 3. Acesso à Memória (Variáveis)
    
    // storeAI r1 => rfp, 0  (Gravar em local)
    // storeAI r1 => rbss, 0 (Gravar em global)
    else if (strcmp(node->opcode, "storeAI") == 0) {
        printf("\tmovl\t%s, %%eax\n", op1); // Pega o valor do registrador
        
        if (strcmp(node->arg2, "rfp") == 0) {
            // Local: rfp + offset (negativo na pilha)
            // Lógica: offset 0 vira -4(%rbp), 4 vira -8(%rbp)...
            int offset = atoi(node->arg3);
            printf("\tmovl\t%%eax, -%d(%%rbp)\n", offset + 4);
        } 
        else if (strcmp(node->arg2, "rbss") == 0) {
            // Global: apenas o nome da variável + (%rip)
            // Mas espera... o ILOC usa offset numérico para global? 
            // Seu parser na etapa 5 calculava offsets, mas para globals assembly usa RÓTULOS.
            // Para simplificar, seu 'storeAI' deveria ter o NOME da variável se possível.
            // Se você só tem offset numérico para global, precisará mapear de volta (difícil)
            // OU: Assumir que o 'arg3' seja o RÓTULO para globais se você alterou isso.
            
            // SE O ARG3 FOR NUMÉRICO (offset) E É GLOBAL, ISSO É UM PROBLEMA NO ASSEMBLY.
            // Assumindo que você ajustou para passar o LABEL ou que só testaremos locais por enquanto.
        }
    }
    
    // loadAI rfp, 0 => r1 (Ler de local)
    else if (strcmp(node->opcode, "loadAI") == 0) {
        if (strcmp(node->arg1, "rfp") == 0) {
            int offset = atoi(node->arg2);
            printf("\tmovl\t-%d(%%rbp), %%eax\n", offset + 4);
            printf("\tmovl\t%%eax, %s\n", op3);
        }
    }

    // 4. Retorno
    // return r1 -> movl r1, %eax; pop; ret
    // Seu ILOC usa "retorna" como unário ou você gera store num registrador específico?
    // Se o seu parser gera um 'jump' para o fim, trate aqui.
    // Se gera uma instrução específica 'retorna r1':
    else if (strcmp(node->opcode, "retorna") == 0) {
         printf("\tmovl\t%s, %%eax\n", op1); // Valor de retorno em EAX
         // Pula para o epílogo (ou faz aqui mesmo se for simples)
         printf("\tpopq\t%%rbp\n");
         printf("\tret\n");
    }

    // 5. Controle de Fluxo (Simples)
    else if (strcmp(node->opcode, "jumpI") == 0) {
        printf("\tjmp\t%s\n", node->arg1);
    }
    else if (strcmp(node->opcode, "nop") == 0) {
        // Nada
    }
}

/* Loop principal de geração de código */
void generateCodeSegment(iloc_node_t *head) {
    iloc_node_t *current = head;
    while (current != NULL) {
        translateInstruction(current);
        current = current->next;
    }
}

/**
 * Gera o Segmento de Dados (.data)
 * Percorre a tabela de símbolos e declara variáveis globais.
 */
void generateDataSegment(table_t *tabela_global) {
    if (tabela_global == NULL) return;

    printf("\t.data\n");

    // Itera sobre todos os símbolos da tabela global
    for (int i = 0; i < tabela_global->count; i++) {
        symbol_t *symbol = tabela_global->symbols[i];

        // Filtramos apenas o que é Variável (SYMBOL_ID) e Global
        // Ignoramos funções e literais aqui
        if (symbol->nature == SYMBOL_ID && symbol->is_global) {
            
            // 1. Diretiva .globl (torna visível para o linker)
            printf("\t.globl\t%s\n", symbol->key);
            
            // 2. Alinhamento (4 bytes para int/float)
            printf("\t.align\t4\n");
            
            // 3. Define tipo e tamanho
            printf("\t.type\t%s, @object\n", symbol->key);
            printf("\t.size\t%s, 4\n", symbol->key);
            
            // 4. Rótulo e valor inicial (default 0)
            printf("%s:\n", symbol->key);
            printf("\t.long\t0\n"); 
        }
    }
}

void generateAssembly(table_t *tabela_global, iloc_node_t *codigo_iloc) {
    // 1. Cabeçalho
    printf("\t.file\t\"entrada.cv\"\n");
    
    // 2. Gera Segmento de Dados (CHAMADA NOVA)
    generateDataSegment(tabela_global);

    // 3. Segmento de Código
    printf("\t.text\n");
    printf("\t.globl\tmain\n");
    printf("\t.type\tmain, @function\n");
    printf("main:\n");

    // Prólogo
    printf("\tpushq\t%%rbp\n");
    printf("\tmovq\t%%rsp, %%rbp\n");
    
    generateCodeSegment(codigo_iloc);
    // Epílogo
    printf("\tmovl\t$0, %%eax\n");
    printf("\tpopq\t%%rbp\n");
    printf("\tret\n");
}