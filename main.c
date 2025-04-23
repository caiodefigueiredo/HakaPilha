#include "main.h"

int main() {
    pStack P = NULL;
    int ret, rlines;
    char buffer[100];

        rlines = 0;
    while (1) {
        printf("Informe a quantidade de elementos:\n");
        char line[100];
        if (!fgets(line, sizeof(line), stdin)) {
            fprintf(stderr, "Erro ao ler a entrada.\n");
            return 1;
        }
        // remove '\n'
        line[strcspn(line, "\n")] = '\0';

        char *endptr;
        long val = strtol(line, &endptr, 10);
        // pular espaços/tabs após o número
        while (*endptr == ' ' || *endptr == '\t') endptr++;

        if (endptr[0] == '\0' && val > 0) {
            rlines = (int)val;
            break;  // linha válida: apenas dígitos + '\0'
        } else {
            fprintf(stderr, "Quantidade inválida. Informe um inteiro positivo.\n");
        }
    }


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
        } // se ret == FAIL, a própria função push já imprime a mensagem
    }

    // Exibe topo
    printf("Elemento do topo:\n");
    char *temp_out = NULL;
    if (top(P, &temp_out) == SUCCESS) {
        printf("%s\n", temp_out);
        free(temp_out);
    }

    // Desempilha todos
    for (int i = 0; i < rlines; i++) {
        char *out = NULL;
        if (pop(P, &out) == SUCCESS) {
            printf("Elemento retirado: %s\n", out);
            free(out);
        }
    }
    printf("Pop na pilha completado\n");

    ret = unstack(&P);
    printf("Flush na pilha %d\n", ret);

    return 0;
}
