#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack_pub.h"
#include "stack_pri.h"

int stack(ppStack pp, int size, int sizedata) {
    if (!pp || size <= 0 || sizedata <= 0)
        return FAIL;
    *pp = (pStack)malloc(sizeof(PE));
    if (!*pp)
        return FAIL;
    (*pp)->topo = NULL;
    (*pp)->tamanho = size;
    (*pp)->capacidade = 0;
    (*pp)->type = 99;
    (*pp)->sizedata = sizedata;
    return SUCCESS;
}

int unstack(ppStack pp) {
    if (!pp || !*pp)
        return FAIL;
    No *atual = (*pp)->topo;
    while (atual) {
        No *prox = atual->anterior;
        if ((*pp)->type == 2 && atual->dado.stringValue)
            free(atual->dado.stringValue);
        free(atual);
        atual = prox;
    }
    free(*pp);
    *pp = NULL;
    return SUCCESS;
}

int push(pStack p, void *element) {
    if (!p || !element || p->capacidade >= p->tamanho)
        return FAIL;

    char *elem = (char *)element;
    char *testeInt = NULL;
    char *testeFloat = NULL;
    long ehnumero;
    float ehfloat;
    No *novo = NULL;

    ehnumero = strtol(elem, &testeInt, 10);
    if (testeInt == elem || (*testeInt != '\0' && *testeInt != '\n')) {
        ehfloat = strtof(elem, &testeFloat);
        if (testeFloat == elem || (*testeFloat != '\0' && *testeFloat != '\n')) {
            if (p->type == 99) p->type = 2;
            else if (p->type != 2) {
                printf("Elemento nao permitido. Informe outro elemento:\n");
                return FAIL;
            }
            novo = malloc(sizeof(No));
            if (!novo) return FAIL;
            novo->dado.stringValue = malloc(strlen(elem) + 1);
            if (!novo->dado.stringValue) {
                free(novo);
                return FAIL;
            }
            strcpy(novo->dado.stringValue, elem);
        } else {
            if (p->type == 99) p->type = 1;
            else if (p->type != 1) {
                printf("Elemento nao permitido. Informe outro elemento:\n");
                return FAIL;
            }
            novo = malloc(sizeof(No));
            if (!novo) return FAIL;
            novo->dado.floatValue = ehfloat;
        }
    } else {
        if (p->type == 99) p->type = 0;
        else if (p->type != 0) {
            printf("Elemento nao permitido. Informe outro elemento:\n");
            return FAIL;
        }
        novo = malloc(sizeof(No));
        if (!novo) return FAIL;
        novo->dado.intValue = (int)ehnumero;
    }

    novo->anterior = p->topo;
    p->topo = novo;
    p->capacidade++;
    return SUCCESS;
}

int pop(pStack p, void *element) {
    if (!p || !element || p->capacidade == 0)
        return FAIL;
    No *rem = p->topo;
    if (p->type == 0) {
        *(int *)element = rem->dado.intValue;
    } else if (p->type == 1) {
        *(float *)element = rem->dado.floatValue;
    } else {
        *(char **)element = strdup(rem->dado.stringValue);
        free(rem->dado.stringValue);
    }
    p->topo = rem->anterior;
    free(rem);
    p->capacidade--;
    if (p->capacidade == 0)
        p->type = 99;
    return SUCCESS;
}

int cleanStack(pStack p) {
    if (!p)
        return FAIL;
    while (p->capacidade > 0) {
        No *rem = p->topo;
        p->topo = rem->anterior;
        if (p->type == 2 && rem->dado.stringValue)
            free(rem->dado.stringValue);
        free(rem);
        p->capacidade--;
    }
    p->type = 99;
    return SUCCESS;
}

int top(pStack p, void *out) {
    if (!p || !out || p->capacidade == 0 || !p->topo)
        return FAIL;
    No *aux = p->topo;
    if (p->type == 0) {
        *(int *)out = aux->dado.intValue;
    } else if (p->type == 1) {
        *(float *)out = aux->dado.floatValue;
    } else {
        *(char **)out = strdup(aux->dado.stringValue);
    }
    return SUCCESS;
}