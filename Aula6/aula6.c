#include <stdio.h>

typedef struct NODOAB
{
    int ID;
    int nChave;
    struct NODOAB *fe;
    struct NODOAB *fd;
} NodoAB;

NodoAB *findNode(NodoAB *A, int ID);
int completa(NodoAB *A);
int alturaArvore(NodoAB *A);
int cheia(NodoAB *A);
int contarNodos(NodoAB *A);
int maxID(NodoAB *A);
int equilibrada(NodoAB *A);
NodoAB *findNode_NaoChave(NodoAB *A, int x); //O x não é o id, a árvore está ordenada por IDs
int max_NaoChave(NodoAB *A);                 //Vamos avaliar o max de um parametro que não o ID

int main(void)
{
}

NodoAB *findNode(NodoAB *A, int ID)
{
    if (A == NULL || A->ID == ID)
    {
        return A;
    }

    if (ID > A->ID)
    {
        return findNode(A->fd, ID);
    }
    else
    {
        return findNode(A->fe, ID);
    }
}

int cheia(NodoAB *A)
{
    if (A == NULL)
    {
        return 1;
    }

    if (A->fd == NULL && A->fe == NULL)
        return 1;
    else if (A->fd == NULL || A->fe == NULL)
        return 0;
    else
        return cheia(A->fe) * cheia(A->fd);
}

int maxID(NodoAB *A)
{
    if (A == NULL)
    {
        return -1; //nao há máximo
    }

    if (A->fd != NULL)
    {
        return maxID(A->fd);
    }

    return A->ID;
}

int contarNodos(NodoAB *A)
{
    if (A == NULL)
        return 0;

    return 1 + contarNodos(A->fd) + contarNodos(A->fe);
}
int equilibrada(NodoAB *A)
{
    int dif;
    if (A == NULL)
        return 1;

    dif = contarNodos(A->fd) - contarNodos(A->fe);
    if (dif > 1 || dif < -1)
        return 0;

    return equilibrada(A->fd) * equilibrada(A->fe);
}

NodoAB *findNode_NaoChave(NodoAB *A, int x)
{
    NodoAB *dir, *esq;
    if (A == NULL || A->nChave == x)
        return A;

    dir = findNode_NaoChave(A->fd, x);

    return (dir == NULL ? findNode_NaoChave(A->fe, x) : dir);
}

int max_NaoChave(NodoAB *A)
{
    if (A == NULL)
    {
        return -1;
    }

    return max3int(A->nChave, max_NaoChave(A->fd), max_NaoChave(A->fe));
}

int max3int(int a, int b, int c)
{
    return (a > b ? (a > c ? a : c) : (b > c ? b : c));
}

int completa(NodoAB *A) //ACABAR
{
    if (A == NULL || !equilibrada(A))
        return 0;

    if (cheia(A))
        return 1;

    return 0;
}

int alturaArvore(NodoAB *A)
{
    int dir, esq;
    if (A == NULL)
    {
        return 0;
    }

    dir = alturaArvore(A->fd);
    esq = alturaArvore(A->fe);
    return 1 + (dir > esq ? dir : esq);
}
