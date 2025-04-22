/* Arquivo EXEMPLO DE Aplicacao */
// MODIFIQUEM-o, CORRIJAM-o!
#include "main.h"

int main() {
    
    pStack P = NULL;
    int ret=0;
    int rlines=0; 
    char buffer[100]; 
    int leitura=0;
    char *ptr;
    ptr = buffer;

    printf("Informe a quantidade de elementos:\n");
    if (!scanf("%d", &rlines)) {
        return 1;
    }
    if (rlines == 0){
        return 1;
    }

    getchar();

    ret = stack(&P,rlines);
    //printf("Criacao da pilha %d\n", ret);
    fflush(stdin);


    printf("Digite %d dados genericos (inteiros, float ou string), um por linha:\n", rlines);
    while (leitura < rlines) {
        if (!fgets(buffer, sizeof(buffer), stdin)) {
            printf("Erro ao ler a entrada.\n");
            return 1;
        }


        if (strlen(buffer) == 0){
            return 1;
        }


        ret = push(&P,ptr);
        //printf("Push na pilha %d\n", ret);
        if (ret == 0){
            leitura++;
        }        

    }    
    
    ret = top(P);    
    
    //printf("Topo na pilha %s\n", ret);

    for (int i=0; i<rlines;i++) {
        ret = pop(&P);
        //printf("Pop na pilha %s\n", ret);
    }
    printf("Pop na pilha completado\n");
    ret = unstack(&P);
    printf("Flush na pilha %d\n", ret);
  
    return 0;
}
