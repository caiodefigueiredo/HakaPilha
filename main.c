/* Arquivo EXEMPLO DE Aplicacao */
// MODIFIQUEM-o, CORRIJAM-o!
#include "main.h"

int main() {
    
    pStack P = NULL;
    int ret=0;
    int valor=0;
    int *arg;
    int rlines=0;  

    if (!scanf("%d", &rlines)) {
        return 1;
    }
    if (rlines == 0){
        return 1;
    }

    arg = (int*) malloc(sizeof(int)*(rlines));


    if (!arg){
        printf("Erro de alocação.\n");
    }


    ret = stack(&P,rlines);
    printf("Criacao da pilha %d\n", ret);

    for (int i=0; i<rlines;i++){
        scanf("%d", &arg[i]);
        ret = push(&P,arg[i]);
        printf("Push na pilha %d\n", ret);
        printf("Push na pilha valor %d\n", arg[i]);
    }
    
    ret = top(P);

    printf("Topo na pilha %d\n", ret);

    for (int i=0; i<rlines;i++) {
        ret = pop(&P);
        printf("Pop na pilha %d\n", ret);
    }
    printf("Pop na pilha completado\n");
    ret = unstack(&P);
    printf("Flush na pilha %d\n", ret);
  
    return 0;
}
