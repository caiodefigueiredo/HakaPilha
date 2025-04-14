#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>

#define SUCCESSO 0
#define FRACASSO 1

typedef struct PE *pStack, **ppStack;

// "Construtor": aloca memória e inicializa as variáveis
int stack(ppStack pp, int size);
// "Destrutor": libera memória da estrutura
int unstack(ppStack pp);

// **** "Operações de manipulação" ****
// Empilha um elemento 
int push(ppStack pp, int element);
// Desempilha um elemento
int pop(ppStack pp);
// Remove todos os dados da pilha mantendo o descritor alocado.
int cleanStack(ppStack pp);

// **** "Operações de acesso" ****
// Retorna uma cópia do dado do topo
int top(pStack p);

#endif