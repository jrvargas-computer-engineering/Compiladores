#ifndef _ILOC_H_
#define _ILOC_H_

// Enum para facilitar a identificação do tipo de argumento

typedef struct iloc_node {
    char *label;    // Rótulo opcional (ex: "L1"). Pode ser NULL se não tiver.
    char *opcode;   // A instrução em si (ex: "add", "loadAI", "storeAI")
    
    // Argumentos da instrução (operando da esquerda, direita e destino)
    // Ex: add r1, r2 => r3  --> arg1="r1", arg2="r2", arg3="r3"
    // Ex: jumpI -> L1       --> arg1="L1", arg2=NULL, arg3=NULL
    char *arg1;     
    char *arg2;
    char *arg3;

    // Ponteiros para manter a lista duplamente encadeada
    struct iloc_node *next;
    struct iloc_node *prev;
    
} iloc_node_t;

// Função auxiliar para criar uma nova instrução (construtor)
iloc_node_t* new_iloc(char *label, char *opcode, char *arg1, char *arg2, char *arg3);

// Função para liberar a memória de uma lista de instruções
void free_iloc_list(iloc_node_t *head);

#endif // _ILOC_H_