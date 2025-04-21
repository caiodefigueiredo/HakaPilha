#ifndef STACK_PRI_H
#define STACK_PRI_H


typedef struct no {
    //Dado *info;
    union {
        int intValue;
        float floatValue;
        char *stringValue;
    } dado;
    struct no *anterior;
} No;

typedef struct PE 
{
    No *topo;
    int tamanho;
    int capacidade;
    int type; // 0 para int, 1 para float, 2 para string, 99 para não definido
} PE;


#endif