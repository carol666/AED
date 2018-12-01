#include <stdio.h>
#include <stdlib.h>

typedef struct NODOAB
{
    int ID;
    int indice;
    int nChave;
    struct NODOAB *fe;
    struct NODOAB *fd;
} NodoAB;

typedef struct NODO
{
    int ID;
    struct NODO *nseg;
    struct NODO *nant;
} Nodo;

int totalNaoIndexados(Nodo *L, NodoAB *A);
int SubArvore(NodoAB *A, NodoAB *B);
NodoAB *EquilibraMuitoDesiquilibrada(NodoAB *A);

main(int argc, char const *argv[])
{
    /* code */
    return 0;
}

int totalNaoIndexados(Nodo *L, NodoAB *A)
{
    int cont = 0;

    if (A == NULL)
        return countNodes(L);

    while (L != NULL)
    {
        if (findNode(A, L) == NULL)
        {
            cont++;
        }
        L = L->nseg;
    }

    return cont;
}

int totalNaoIndexadosProf(Nodo *L, NodoAB *A)
{
    if (L == NULL)
        return 0;

    return ((findNodeAB(A, L->ID) == NULL) + totalNaoIndexadosProf(L->nseg, A));
}

NodoAB *findNode(NodoAB *A, Nodo *indice)
{
    if (A == NULL || A->indice == indice)
    {
        return A;
    }

    if (indice->ID > A->indice->ID)
    {
        return findNode(A->fd, indice);
    }
    else
    {
        return findNode(A->fe, indice);
    }
}

NodoAB *findNodeAB(NodoAB *A, int ID)
{
    if (A == NULL || A->indice->ID == ID)
    {
        return A;
    }

    if (ID > A->indice->ID)
    {
        return findNode(A->fd, ID);
    }
    else
    {
        return findNode(A->fe, ID);
    }
}

int countNodes(Nodo *L)
{
    int count = 0; //iniciamos o num de nodos o 0, caso a lista esteja vazia retorna este numero

    while (L != NULL) //enquanto a lista nao tiver terminado
    {
        count++;     //incrimentar o numero de nodos
        L = L->nseg; //avançar na lista
    }

    return count; //retornar o numero de nodos
}

int SubArvore(NodoAB *A, NodoAB *B)
{
    NodoAB *aux;
    if (B == NULL)
        return 1;

    aux = findNodeAB(A, B->ID);

    if (aux == NULL)
        return 0;

    return igual(aux, B);
}

int igual(NodoAB *A, NodoAB *B)
{
    if (B == NULL)
        return 1;

    if (A == NULL)
        return 0;

    if (A->ID != B->ID)
        return 0;

    return igual(A->fe, B->fe) && igual(A->fd, B->fd);
}

NodoAB *EquilibraMuitoDesiquilibrada(NodoAB *A)
{
    NodoAB *final = findnode(A, meadianaID(A, A));

    A = remove(A, final);

    while (A != NULL)
    {
        aux = remove(&A, A);
        final = inserir(final, aux);
    }

    final->fe = EquilibraMuitoDesiquilibrada(final->fe);
    final->fd = EquilibraMuitoDesiquilibrada(final->fd);

    return final;
}

int medianaID(NodoAB *A, NodoAB *raiz)
{
    int menores = contarIDMenor(raiz, A->ID);
    int nodos = contarNodos(raiz);
    if (A == NULL)
        return -1;

    if (menores == nodos / 2)
        return A->ID;

    if (menores > nodos / 2)
        return meadianaID(A->fe, raiz);

    return medianaID(A->fd, raiz);
}

int contarIDMenor(NodoAB *A, int ID)
{
    if (A == NULL)
        return 0;

    if (A->ID >= ID)
        return contarIDMenor(A->fe, ID);

    if (A->ID < ID)
        return 1 + contarIDMenor(A->fe, ID) + contarIDMenor(A->fd, ID);
}

int contarNodos(NodoAB *A)
{
    if (A == NULL)
        return 0;

    return 1 + contarNodos(A->fd) + contarNodos(A->fe);
}

NodoAB *remove(NodoAB *A, NodoAB *del)
{
    NodoAB *aux, *aux2, *aux3, *pai = findPai(A, del);

    if (del->fe == del->fd)
    {
        if (pai != NULL)
        {
            if (pai->fd == del)
                pai->fd = NULL;
            else
                pai->fe = NULL;

            free(del);
            return (A);
        }
        return NULL;
    }

    if (del->fd == NULL || del->fe == NULL)
    {
        if (del->fd != NULL)
            aux = del->fd;
        else
            aux = del->fe;

        if (pai == NULL)
        {
            free(del);
            return aux;
        }

        if (pai->fe == del)
            pai->fe = aux;
        else
            pai->fd = aux;

        free(del);
        return (A);
    }
    aux = del->fd;
    aux2 = del->fe;

    if (pai == NULL)
    {
        free(del);
        return (insere(aux, aux2));
    }

    aux3 = insere(aux, aux2);
    if (pai->fe == del)
    {
        pai->fe = aux3;
    }
    else
    {
        pai->fd = aux3;
    }
}
