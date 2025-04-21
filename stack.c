#include "stack_pri.h"
#include "stack_pub.h"



// "Construtor": aloca memória e inicializa as variáveis
int stack(ppStack pp, int size){
    *pp = (pStack)malloc(sizeof(struct PE));
    (*pp)->topo = NULL;
    (*pp)->tamanho = size;
    (*pp)->capacidade = 0;
    (*pp)->type = 99;
    return SUCCESSO;
}

int push(ppStack pp, char *element){
    char *testeInt=NULL;
    char *testeFloat=NULL;
    long ehnumero;
    float ehfloat;
    No *novo=NULL;

    if ((*pp)->capacidade >= (*pp)->tamanho){
        return FRACASSO;
    }        
    novo = malloc(sizeof(novo));
    if(novo){      
        ehnumero = strtol(element, &testeInt, 10);
        if (*testeInt == '\0' || *testeInt == '\n'){
            if ((*pp)->type==99){
                (*pp)->type=0;
            }
            else{
                if ((*pp)->type==1 || (*pp)->type==2){
                    printf("\nElemento nao permitido. Informe outro elemento:\n");
                    return FRACASSO;
                }
            }            
            //printf("\ninteiro\n");
            novo->dado.intValue = (int)ehnumero;
        }
        else {
            ehfloat = strtof(element, &testeFloat);
            if (*testeFloat == '\0' || *testeFloat == '\n'){
                if ((*pp)->type==99){
                    (*pp)->type=1;
                }
                else{
                    if ((*pp)->type==0 || (*pp)->type==2){
                        printf("\nElemento nao permitido. Informe outro elemento:\n");
                        return FRACASSO;
                    }
                }
                //printf("\nfloat\n");
                novo->dado.floatValue = ehfloat;
            }
            else{
                if ((*pp)->type==99 || (*pp)->type==2) {
                    if ((*pp)->type==99){
                        (*pp)->type=2;
                    }
                    novo->dado.stringValue = malloc(strlen(element) + 1);
                    if (!novo->dado.stringValue) {
                        printf("Erro de alocacao.\n");
                        return FRACASSO;
                    }
                    //printf("\nchar\n");
                    strcpy(novo->dado.stringValue,element);
                    novo->dado.stringValue[strcspn(novo->dado.stringValue, "\n")] = '\0';
                }
                else{
                    printf("\nElemento nao permitido. Informe outro elemento:\n");
                    return FRACASSO;
                }                
            }
        }

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
        switch (p->type) {
            case 0:
                printf("Elemento do topo: %d\n", leitura->dado.intValue);
                break;
            case 1:
                printf("Elemento do topo: %.2f\n", leitura->dado.floatValue);
                break;
            case 2:
                printf("Elemento do topo: %s\n", leitura->dado.stringValue); 
                break;
            default: 
                printf("Sem elemento na pilha\n"); 
        }   
        return SUCCESSO;
    }

}

// Desempilha um elemento
int pop(ppStack pp){
    No *remover=NULL;
    char valor[100];
    
    if ((*pp)->capacidade == 0){
        return FRACASSO;
    }
    
    if((*pp)->topo){
        remover = (*pp)->topo;
        switch ((*pp)->type) {
            case 0:
                printf("Elemento retirado: %d\n", remover->dado.intValue);
                break;
            case 1:
                printf("Elemento retirado f: %.2f\n", remover->dado.floatValue);
                break;
            case 2:
                printf("Elemento retirado: %s\n", remover->dado.stringValue); 
                break;
            default: 
                printf("Sem elemento na pilha\n"); 
        }   
        //valor = remover->dado;
        (*pp)->topo = remover->anterior;
        (*pp)->capacidade-= 1;        
        free(remover);
        if ((*pp)->capacidade == 0){
            (*pp)->type = 99;
            (*pp)->capacidade = 0;
            (*pp)->topo = NULL;
        }
    }
    else{
        return FRACASSO;
    }
    return SUCCESSO;
}

// "Destrutor": libera memória da estrutura
int unstack(ppStack pp){
    No *remover=NULL;
    //printf("teste1\n");
    //printf("teste2 %d\n",(*pp)->capacidade);
    if ((*pp)->capacidade == 0){
        (*pp)->type = 99;
        (*pp)->capacidade = 0;
        (*pp)->topo = NULL;

        //printf("teste3\n");
        free(*pp);
        (*pp) = NULL;
        //printf("teste4\n");
        return SUCCESSO;
    }
    //printf("teste5\n");
    if((*pp)->capacidade > 0){
        //printf("teste6\n");
        for (int i = (*pp)->capacidade; i>0;i--){            
            remover = (*pp)->topo;
            switch ((*pp)->type) {
                case 0:
                    printf("Elemento limpado: %d\n", remover->dado.intValue);
                    break;
                case 1:
                    printf("Elemento limpado: %.2f\n", remover->dado.floatValue);
                    break;
                case 2:
                    printf("Elemento limpado: %s\n", remover->dado.stringValue); 
                    break;
                default: 
                    printf("Sem elemento na pilha\n"); 
            }               
            (*pp)->topo = remover->anterior;
            (*pp)->capacidade-= 1;        
            free(remover);
        }
        

    }

    (*pp)->type = 99;
    (*pp)->capacidade = 0;
    (*pp)->topo = NULL;
    //printf("teste7\n");
    free(*pp);
    (*pp) = NULL;
    //printf("teste8\n");
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
            switch ((*pp)->type) {
                case 0:
                    printf("Elemento limpado: %d\n", remover->dado.intValue);
                    break;
                case 1:
                    printf("Elemento limpado: %.2f\n", remover->dado.floatValue);
                    break;
                case 2:
                    printf("Elemento limpado: %s\n", remover->dado.stringValue); 
                    break;
                default: 
                    printf("Sem elemento na pilha\n"); 
            }               
            (*pp)->topo = remover->anterior;
            (*pp)->capacidade-= 1;        
            free(remover);            
        }
        (*pp)->type = 99;
        (*pp)->capacidade = 0;
        (*pp)->topo = NULL;
    }
    return SUCCESSO;

}

