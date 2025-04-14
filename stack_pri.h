#ifndef STACK_PRI_H
#define STACK_PRI_H

/*typedef struct dado 
{
    int type; // 0 para int, 1 para float, 2 para string
    union {
        int intValue;
        float floatValue;
        char *stringValue;
    } data;

} Dado;*/

typedef struct no {
    //Dado *info;
    int dado;
    struct no *anterior;
} No;

typedef struct PE 
{
    No *topo;
    int tamanho;
    int capacidade;
} PE;


#endif