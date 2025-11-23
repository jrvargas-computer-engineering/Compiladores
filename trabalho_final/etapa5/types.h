/* Grupo A - Alunos:
 Juliana Rodrigres de Vargas- 00337553
 Sofia Popsin Gomes - 00313563*/

#ifndef TYPES_H
#define TYPES_H

#include "asd.h"

typedef struct lexical_value {
    int line;
    int type; 
    char *value;
} lexical_value_t;

#endif 