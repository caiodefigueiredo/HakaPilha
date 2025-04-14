#include "stack_pri.h"
#include "stack_pub.h"



// "Construtor": aloca memória e inicializa as variáveis
int stack(ppStack pp, int size){
    *pp = (pStack)malloc(sizeof(struct PE));
    (*pp)->topo = NULL;
    (*pp)->tamanho = size;
    (*pp)->capacidade = 0;
    return SUCCESSO;
}

int push(ppStack pp, int element){
    No *novo=NULL;
    if ((*pp)->capacidade >= (*pp)->tamanho){
        return FRACASSO;
    }
    
    novo = malloc(sizeof(novo));
    if(novo){
        
        novo->dado = element;
        novo->anterior=(*pp)->topo;
        (*pp)->capacidade+= 1;
        (*pp)->topo = novo;
    }
    else{
        return FRACASSO;
    }
    return SUCCESSO;
}

// **** "Operações de acesso" ****
// Retorna uma cópia do dado do topo
int top(pStack p){
    No *leitura=NULL;
    leitura = p->topo;
    if (!leitura){
        return FRACASSO;
    }
    else{
        return leitura->dado;
    }

}

// Desempilha um elemento
int pop(ppStack pp){
    No *remover=NULL;
    int valor=0;
    
    if ((*pp)->capacidade == 0){
        return FRACASSO;
    }
    
    if((*pp)->topo){
        remover = (*pp)->topo;
        valor= remover->dado;
        (*pp)->topo = remover->anterior;
        (*pp)->capacidade-= 1;        
        free(remover);
    }
    else{
        return FRACASSO;
    }
    return valor;
}

// "Destrutor": libera memória da estrutura
int unstack(ppStack pp){
    No *remover=NULL;
    printf("teste1\n");
    printf("teste2 %d\n",(*pp)->capacidade);
    if ((*pp)->capacidade == 0){
        printf("teste3\n");
        free(*pp);
        printf("teste4\n");
        return SUCCESSO;
    }
    printf("teste5\n");
    if((*pp)->capacidade > 0){
        printf("teste6\n");
        for (int i = (*pp)->capacidade; i>0;i--){
            remover = (*pp)->topo;
            (*pp)->topo = remover->anterior;
            (*pp)->capacidade-= 1;        
            free(remover);
        }
    }
    printf("teste7\n");
    free(*pp);
    printf("teste8\n");
    return SUCCESSO;
}

// Remove todos os dados da pilha mantendo o descritor alocado.
int cleanStack(ppStack pp){
    No *remover=NULL;
    
    if ((*pp)->capacidade = 0){
        return SUCCESSO;
    }
    
    if((*pp)->capacidade > 0){
        for (int i = (*pp)->capacidade; i>0;i--){
            remover = (*pp)->topo;
            (*pp)->topo = remover->anterior;
            (*pp)->capacidade-= 1;        
            free(remover);
        }
    }
    return SUCCESSO;

}

