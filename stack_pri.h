// stack_pri.h (atualizado para definir sizedata)
#ifndef STACK_PRI_H
#define STACK_PRI_H

#include <stdlib.h>

typedef struct no {
    union {
        int intValue;
        float floatValue;
        char *stringValue;
    } dado;
    struct no *anterior;
} No;

typedef struct PE {
    No *topo;
    int tamanho;
    int capacidade;
    int type;      // 0: int, 1: float, 2: string, 99: undefined
    int sizedata;  // tamanho em bytes de cada elemento
} PE;

#endif