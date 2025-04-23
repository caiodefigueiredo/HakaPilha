// stack_pri.h
#ifndef STACK_PRI_H
#define STACK_PRI_H

#include "stack_pub.h"

// Estrutura de nó para tipos int, float ou string
typedef struct no {
    union {
        int intValue;
        float floatValue;
        char *stringValue;
    } dado;
    struct no *anterior;
} No;

// Descritor da pilha genérica homogênea
// type: 0=int, 1=float, 2=string, 99=undefined
typedef struct PE {
    No *topo;
    int tamanho;
    int capacidade;
    int type;
    int sizedata;
} PE;

#endif  // STACK_PRI_H