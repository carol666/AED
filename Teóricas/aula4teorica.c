#include <stdio.h>
#include <stdlib.h>

typedef struct NODE{
	int ID;
	struct NODE *nant;
	struct NODE *nseg;
}Node;

Node* removeFirst(Node *L){ // Utiliza-se quando se quer retirar e eliminar elemento
    Node *aux = L;
    if(L==NULL){
        return L;
    }
    L = L->nseg;
    free(aux);
    return nseg;
}

Node* removeFirst2(Node **L){   // Quando se quer retirar e colocar noutro sítio
    Node *aux = (*L);
    if( (*L) != NULL){}
        (*L)=(*L)->nseg;
        aux->nseg = NULL;
    }
    return (aux);
}

int contaFila(Node *L){             // Contar Elementos de uma fila
    int i=0;
    Node *aux = NULL;
    while(L != NULL){
        aux = push(aux, pop(&L));   // push em filas -> insertFirst  ; pop -> removeFirst
        i++;
    }
    return i;
}

int contaPilha(Node *L){            // Contar Elementos de uma fila
    int i=0;
    Node *aux = NULL;
    while (L != NULL){              // Colocar elementos "noutra sala"
        aux = push(aux,pop(&L));    // push em pilhas -> insertLast  ; pop -> removeFirst
        i++;
    }
    while (aux != NULL){            // Voltar a colocá-los na "sala" original, como na última eles estavam na ordem inversa agora estão 
        L = push(L,pop(&aux));      // corretamente ordenados
    }
    return i;
}