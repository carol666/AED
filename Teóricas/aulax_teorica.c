#include <stdio.h>
#include <stdlib.h>

typedef struct NODOAB
{
    int ID;
    struct NODOAB *fe;
    struct NODOAB *fd;
} NodoAB;

NodoAB *findPai(NodoAB *A, NodoAB *n)
{
    if (A == NULL || n == NULL)
        return (NULL);

    if (A->fe == n || A->fd == n)
        return A;

    if (A->ID > n->ID)
        return (findPai(A->fe, n));

    return (findPai(A->fd, n));
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

int profundidadeNodo(NodoAB *A, NodoAB *n, int cont)
{
    if (A == NULL || n == NULL)
    {
        return -1;
    }

    if (A == n)
    {
        return cont;
    }

    if (A->ID > n->ID)
        return profundidadeNodo(A->fe, n, cont++);

    return profundidadeNodo(A->fd, n, cont++);
}