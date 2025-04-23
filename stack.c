#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack_pub.h"
#include "stack_pri.h"

// construtor e destrutor mantidos iguais
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

// push mantém a detecção original de int / float / string
int push(pStack p, void *element) {
    if (!p || !element || p->capacidade >= p->tamanho)
        return FAIL;

    char *elem = (char *)element;
    char *testeInt = NULL, *testeFloat = NULL;
    long ehnumero;
    float ehfloat;
    No *novo = NULL;

    ehnumero = strtol(elem, &testeInt, 10);
    if (testeInt == elem || (*testeInt != '\0' && *testeInt != '\n')) {
        ehfloat = strtof(elem, &testeFloat);
        if (testeFloat == elem || (*testeFloat != '\0' && *testeFloat != '\n')) {
            // string
            if (p->type == 99) p->type = 2;
            else if (p->type != 2) {
                printf("Elemento nao permitido. Informe outro elemento:\n");
                return FAIL;
            }
            novo = malloc(sizeof(No));
            if (!novo) return FAIL;
            novo->dado.stringValue = strdup(elem);
            if (!novo->dado.stringValue) { free(novo); return FAIL; }
        } else {
            // float
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
        // inteiro
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

// pop: sempre devolve string (usuario faz printf("%s"))
int pop(pStack p, void *element) {
    if (!p || !element || p->capacidade == 0)
        return FAIL;
    No *rem = p->topo;
    char *out_str;
    char buffer[64];

    // converte para string
    if (p->type == 0) {
        snprintf(buffer, sizeof(buffer), "%d", rem->dado.intValue);
        out_str = strdup(buffer);
    } else if (p->type == 1) {
        snprintf(buffer, sizeof(buffer), "%f", rem->dado.floatValue);
        out_str = strdup(buffer);
    } else {
        out_str = strdup(rem->dado.stringValue);
    }

    // libera nó
    p->topo = rem->anterior;
    if (p->type == 2) free(rem->dado.stringValue);
    free(rem);
    p->capacidade--;
    if (p->capacidade == 0)
        p->type = 99;

    // devolve string ao usuário
    *(char **)element = out_str;
    return SUCCESS;
}

// same as before
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

// top: idem a pop, mas sem remover do topo
int top(pStack p, void *out) {
    if (!p || !out || p->capacidade == 0 || !p->topo)
        return FAIL;

    No *aux = p->topo;
    char *out_str;
    char buffer[64];

    if (p->type == 0) {
        snprintf(buffer, sizeof(buffer), "%d", aux->dado.intValue);
        out_str = strdup(buffer);
    } else if (p->type == 1) {
        snprintf(buffer, sizeof(buffer), "%f", aux->dado.floatValue);
        out_str = strdup(buffer);
    } else {
        out_str = strdup(aux->dado.stringValue);
    }

    *(char **)out = out_str;
    return SUCCESS;
}
