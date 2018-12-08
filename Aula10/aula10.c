#include <stdio.h>

typedef struct NODO
{
    int ID;
    struct NODO *nseg;
} Nodo;

int grauEntrada(Nodo **G, int tv, int v);
int grauSaida(Nodo **G, int tv, int v);
int totalVerticesAtingiveis(Nodo **G, int tv, int v, int N);
int countNodes(Nodo *L);

main(int argc, char const *argv[])
{

    return 0;
}

int grauEntrada(Nodo **G, int tv, int v)
{
    Nodo *aux;
    int count = 0;
    if (G == NULL)
        return count;

    for (int i = 0; i < tv; i++)
    {
        aux = G[i];
        if (i == v)
            continue;
        while (aux != NULL)
        {
            if (aux->ID == v)
                count++;

            aux = aux->nseg;
        }
    }
    return count;
}

int grauSaida(Nodo **G, int tv, int v)
{
    if (G == NULL)
        return 0;
    return countNodes(G[v]);
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

int totalVerticesAtingiveis(Nodo **G, int tv, int v, int N)
{
    int count = 0;
    int *flag = (int)malloc(tv * sizeof(int)); //0-ainda nao cheguei  1-ja cheguei 2-ja explorei
    Nodo *aux;

    for (int i = 0; i < tv; i++)
    {
        flag[i] = -1;
    }

    if (G == NULL)
        return 0;

    flag[v] = 0;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < tv; j++)
        {
            if (flag[j] == i)
            {
                aux = G[j];
                while (aux != NULL)
                {
                    if (flag[aux->ID] == 0)
                        flag[aux->ID] = i + 1;

                    aux = aux->nseg;
                }
            }
        }
    }
    for (int i = 0; i < tv; i++)
    {
        if (flag[i] != -1)
            count++;
    }
    return count;
}
