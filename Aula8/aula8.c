#include <stdio.h>
#include <stdlib.h>

typedef struct NODOAB
{
    int ID;
    int nChave;
    struct NODOAB *fe;
    struct NODOAB *fd;
} NodoAB;

int igualEstrutura(NodoAB *A, NodoAB *B);
int igualConteudo(NodoAB *A, NodoAB *B);
float mediaID(NodoAB *A);
int medianaID(NodoAB *A, NodoAB *raiz);
int contem(NodoAB *A, NodoAB *B);
float somaID(NodoAB *A);
int Nesimo(NodoAB *A, int a); //retorna o ID do elemento na posição A
int contarIDMenor(NodoAB *A, int ID);
NodoAB *findNode(NodoAB *A, int ID);
int contarNodos(NodoAB *A);

int main(int argc, char const *argv[])
{
    /* code */
    return 0;
}

int igualEstrutura(NodoAB *A, NodoAB *B)
{
    if (A == NULL && B == NULL)
    {
        return 1;
    }
    if (A == NULL || B == NULL)
    {
        return 0;
    }

    return (igualEstrutura(A->fd, B->fd) && igualEstrutura(A->fe, B->fe));
}

int igualConteudo(NodoAB *A, NodoAB *B)
{
    return contem(A, B) && contem(B, A);
}

float mediaID(NodoAB *A)
{
    if (A == NULL)
        return 0;
    return somaID(A) / contarNodos(A);
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

int Nesimo(NodoAB *A, int a)
{
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

int contem(NodoAB *A, NodoAB *B)
{
    if (B == NULL)
        return 1;

    if (findNode(A, B->ID) == NULL)
        return 0;

    return contem(A, B->fd) && contem(A, B->fe);
}

int modaX(NodoAB *A)
{
}

int contarNodos(NodoAB *A)
{
    if (A == NULL)
        return 0;

    return 1 + contarNodos(A->fd) + contarNodos(A->fe);
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

float somaID(NodoAB *A)
{
    if (A == NULL)
        return 0;

    return A->ID + soma(A->fd) + soma(A->fe);
}

int Xrepetidos(NodoAB *A, NodoAB *raiz) //IMPORTANTE!!!
{
    if (A == NULL)
        return 0;

    if (findNode_NaoChave(raiz, A->nChave) != A)
        return 1;
    return Xrepetidos(A->fd, raiz) || Xrepetidos(A->fe, raiz);
}

int max3int(int a, int b, int c)
{
    return (a > b ? (a > c ? a : c) : (b > c ? b : c));
}
