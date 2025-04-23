#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack_pub.h"    // declara SUCCESS, FAIL e protótipos
#include "stack_pri.h" // define No, PE

int main() {
    pStack P = NULL;
    int ret, rlines;
    char buffer[100];

    // Quantidade de elementos
    printf("Informe a quantidade de elementos:\n");
    if (scanf("%d", &rlines) != 1 || rlines <= 0) {
        fprintf(stderr, "Quantidade inválida.\n");
        return 1;
    }
    getchar(); // consome '\n'

    printf("Digite %d dados genéricos (inteiros, float ou string), um por linha:\n", rlines);

    ret = stack(&P, rlines, sizeof(char *));
    if (ret != SUCCESS) {
        fprintf(stderr, "Erro ao criar pilha.\n");
        return 1;
    }

    int leitura = 0;
    while (leitura < rlines) {
        if (!fgets(buffer, sizeof(buffer), stdin)) {
            fprintf(stderr, "Erro ao ler a entrada.\n");
            unstack(&P);
            return 1;
        }
        buffer[strcspn(buffer, "\n")] = '\0';

        ret = push(P, buffer);
        if (ret == SUCCESS) {
            leitura++;
        }
        // se ret == FAIL, a própria função push já imprime a mensagem
    }

    // Exibe topo
    printf("Elemento do topo:\n");
    if (P->type == 0) {
        int out;
        if (top(P, &out) == SUCCESS) printf("%d\n", out);
    } else if (P->type == 1) {
        float out;
        if (top(P, &out) == SUCCESS) printf("%.2f\n", out);
    } else {
        char *out;
        if (top(P, &out) == SUCCESS) {
            printf("%s\n", out);
            free(out);
        }
    }

    // Desempilha todos
    for (int i = 0; i < rlines; i++) {
        if (P->type == 0) {
            int out;
            if (pop(P, &out) == SUCCESS)
                printf("Elemento retirado: %d\n", out);
        } else if (P->type == 1) {
            float out;
            if (pop(P, &out) == SUCCESS)
                printf("Elemento retirado: %.2f\n", out);
        } else {
            char *out;
            if (pop(P, &out) == SUCCESS) {
                printf("Elemento retirado: %s\n", out);
                free(out);
            }
        }
    }
    printf("Pop na pilha completado\n");

    // Destrutor
    ret = unstack(&P);
    printf("Flush na pilha %d\n", ret);

    return 0;
}
