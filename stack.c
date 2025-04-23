// stack.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack_pub.h"
#include "stack_pri.h"

int stack(ppStack pp, int size, int sizedata) {
    if (!pp || size <= 0 || sizedata <= 0)
        return FAIL;
    *pp = malloc(sizeof(PE));
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
    No *curr = (*pp)->topo;
    while (curr) {
        No *next = curr->anterior;
        if ((*pp)->type == 2 && curr->dado.stringValue)
            free(curr->dado.stringValue);
        free(curr);
        curr = next;
    }
    free(*pp);
    *pp = NULL;
    return SUCCESS;
}

int push(pStack p, void *element) {
    if (!p || !element || p->capacidade >= p->tamanho)
        return FAIL;

    // Determina tipo na primeira inserção
    if (p->type == 99) {
        if (p->sizedata == sizeof(int)) p->type = 0;
        else if (p->sizedata == sizeof(float)) p->type = 1;
        else if (p->sizedata == sizeof(char *)) p->type = 2;
        else return FAIL;
    }

    No *node = malloc(sizeof(No));
    if (!node) return FAIL;

    if (p->type == 0) {
        // copia int
        node->dado.intValue = *(int *)element;
    } else if (p->type == 1) {
        // copia float
        node->dado.floatValue = *(float *)element;
    } else {
        // copia string pointer (aloca nova cópia)
        char *str = *(char **)element;
        size_t len = strlen(str);
        node->dado.stringValue = malloc((sizeof(char*) * len));
        if (!node->dado.stringValue) { free(node); return FAIL; }
        strcpy(node->dado.stringValue, str);
    }

    node->anterior = p->topo;
    p->topo = node;
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
        *(char **)element = rem->dado.stringValue;
    }

    p->topo = rem->anterior;
    free(rem);
    p->capacidade--;
    if (p->capacidade == 0)
        p->type = 99;
    return SUCCESS;
}

int cleanStack(pStack p) {
    if (!p) return FAIL;
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
        *(char **)out = aux->dado.stringValue;
    }
    return SUCCESS;
}
