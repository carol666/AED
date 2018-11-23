#include <stdio.h>
#include <stdlib.h>

typedef struct NODOAB
{
    int ID;
    int nChave;
    struct NODOAB *fe;
    struct NODOAB *fd;
} NodoAB;

int altura(NodoAB *A);
int completa(NodoAB *A);
NodoAB *espelho(NodoAB *A);              //espelhar uma árvore, árvore direita passa a ser a esquerda
int Xrepetidos(NodoAB *A, NodoAB *raiz); //retorna 1 se houver IDs repetidos, 0 se não houver
NodoAB *apagaArvore(NodoAB *A);
NodoAB *apagaDeireita(NodoAB *A);

int main(void)
{
    return 0;
}

int altura(NodoAB *A)
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
        return profundidadeNodo(A->fe, n, cont + 1);

    return profundidadeNodo(A->fd, n, cont + 1);
}

int altura(NodoAB *A)
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

int completa(NodoAB *A)
{
    if (A == NULL)
        return 1;

    if (contarFolhas(A) == pow(2, altura(A) - 1))
    {
        return 1;
    }
    return 0;
}

int contarFolhas(NodoAB *A)
{
    if (A == NULL)
        return 0;

    if (A->fe == A->fd)
        return 1;
    return contarFolhas(A->fd) + contarFolhas(A->fe);
}

NodoAB *espelho(NodoAB *A)
{
    NodoAB *temp;
    if (A == NULL)
        return A;

    temp = espelho(A->fd);
    A->fd = espelho(A->fe);
    A->fe = temp;

    return A;
}

int Xrepetidos(NodoAB *A, NodoAB *raiz) //IMPORTANTE!!!
{
    if (A == NULL)
        return 0;

    if (findNode_NaoChave(raiz, A->nChave) != A)
        return 1;
    return Xrepetidos(A->fd, raiz) || Xrepetidos(A->fe, raiz);
}

NodoAB *apagarArvore(NodoAB *A)
{
    if (A == NULL)
        return A;

    return apagarArvore(remove(A, A));
}

NodoAB *apagarArvoreProf(NodoAB *A)
{
    if (A == NULL)
        return A;

    A->fd = apagaArvore(A->fd);
    A->fe = apagaArvore(A->fe);

    free(A);
    return NULL;
}

NodoAB *apagaDireita(NodoAB *A)
{
    if (A == NULL)
        return NULL;

    A->fd = apagaArvore(A->fd);

    A->fe = apagaDireita(A->fe);

    return A;
}

NodoAB *findNode_NaoChave(NodoAB *A, int x)
{
    NodoAB *dir, *esq;
    if (A == NULL || A->nChave == x)
        return A;

    dir = findNode_NaoChave(A->fd, x);

    return (dir == NULL ? findNode_NaoChave(A->fe, x) : dir);
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
