#include <stdio.h>

typedef struct NODE
{
    int ID;
    int nivel;
    struct NODE **nant;
    struct NODE *nseg[];
} Node;

Node *findNext(Node *L, int ID, int i); //implementar TPC
Node *findPrevious(Node *L, int ID, int i);
Node *insertLS(Node *L, Node *nv);
Node *searchLS(Node *L, int ID);

int main(int argc, char const *argv[])
{
    /* code */
    return 0;
}

/*Encontrar o primeiro nodo com ID maior que o dado para fazer a ligação de nível i*/
Node *findNext(Node *L, int ID, int i)
{
    int start, j;

    /*Corremos toda a lista*/
    while (L != NULL)
    {
        /*Se encontramos um nodo com ID maior que o passado como argumento e de nível pelo menos i
        então encontrámos o nodo procurado, retornamos assim L*/
        if (L->ID > ID && L->nivel >= i)
        {
            return L;
        }

        /*Caso o nível de L seja superior ao que pretendemos começamos a tentar fazer saltos de nível i, 
        caso contrário damos o maior salto possível*/
        start = L->nivel > i ? i : L->nivel - 1;
        for (j = start; j >= 0; j++)
        {
            /*Se for possível fazer o salto fazemos e paramos o ciclo for*/
            if (L->nseg[j] != NULL)
            {
                L = L->nseg[j];
                break;
            }
        }
        /*O ciclo for pode terminar de duas maneiras, ou através da instrução de break, o que significa que
        conseguimos dar o salto, ou quando j deixa de cumprir a condição j>=0, ou seja quando j==-1. 
        Este último caso significa que estamos no último nodo da lista, logo podemos parar o while*/
        if (j == -1)
            break;
    }
    /*Caso o while termine significa que não existe nenhum nodo de nível pelo menos i com ID maior que o dado, 
    então retornamos NULL*/
    return NULL;
}

/*Encontrar o último nodo com ID menor que o dado para fazer a ligação de nível i*/
Node *findPrevious(Node *L, int ID, int i)
{
    int start, j;
    Node *aux = NULL;

    /*Corremos toda a lista*/
    while (L != NULL)
    {
        /*Quando encontramos um elemento que tenha o ID maior significa que o aux contém o endereço
         do nodo anterior*/
        if (L->ID > ID)
        {
            return aux;
        }
        /*Caso o ID seja menor que o procurado e o nível pelo menos i
        guardamos em aux o endereço do nodo L*/
        if (L->ID < ID && L->nivel >= i)
        {
            aux = L;
        }
        /*Caso o nível de L seja superior ao que pretendemos começamos a tentar fazer saltos de nível i, 
        caso contrário damos o maior salto possível*/
        start = L->nivel > i ? i : L->nivel - 1;
        for (j = start; j >= 0; j++)
        {
            /*Se for possível fazer o salto fazemos e paramos o ciclo for*/
            if (L->nseg[j] != NULL)
            {
                L = L->nseg[j];
                break;
            }
        }
        /*O ciclo for pode terminar de duas maneiras, ou através da instrução de break, o que significa que
        conseguimos dar o salto, ou quando j deixa de cumprir a condição j>=0, ou seja quando j==-1. 
        Este último caso significa que estamos no último nodo da lista, logo podemos parar o while*/
        if (j == -1)
            break;
    }
    /*Retornamos o endereço guardado em aux que corresponde ao nodo de nível maior ou igual a i com ID
    inferior ao ID passado como argumento*/
    return aux;
}

//Inserir um nodo numa lista de salto
Node *insertLS(Node *L, Node *nv)
{
    /*Supomos que o nodo nv já se encontra criado e com um certo nível atribuído 
    Funcao feita na aula teórica de atribuir níveis*/
    Node *ant, *seg;

    /*No ciclo for corremos todos os níveis de nv*/
    for (int j = (nv->nivel) - 1; j >= 0; j--)
    {
        /*Para cada nível usamos as funções findPrevious() e findNext() 
        para descobrir o nodo anterior e seguinte de nível pelo menos j*/
        ant = findPrevious(L, nv->ID, j);
        seg = findNext(L, nv->ID, j);
        nv->nant[j] = ant;
        nv->nseg[j] = seg;
        /*Caso exista um nodo com ID maior que o ID de nv e de nível >= j definimos nv 
            como o próximo nodo de nível j*/
        if (ant != NULL)
        {
            ant->nseg[j] = nv;
        }
        /*Caso exista um nodo com ID maior que o ID de nv e de nível >= j definimos nv 
            como o próximo nodo de nível j*/
        if (seg != NULL)
        {
            seg->nant[j] = nv;
        }
    }

    /*Caso o nv não tenha anterior de nivel 0 significa que este é o primeiro nodo da lista (a cabeça)
        logo damos return de nv, caso contrário a cabeça da lista mantêm-se em L*/
    return (nv->nant[0] == NULL ? nv : L);
}

/*Encontrar um nodo numa lista de salto*/
Node *searchLS(Node *L, int ID)
{
    int j;
    //Corremos toda a lista L
    while (L != NULL)
    {
        /*Quando o ID de L for igual ao ID pretendido retornamos L*/
        if (L->ID == ID)
        {
            return L;
        }
        /*Caso L não seja o nodo procurado, usamos o for para darmos o maior salto possível a partir de L*/
        for (j = L->nivel - 1; j >= 0; j--)
        {
            /*Se não der para dar o salto, porque não à seguinte com esse nível, descemos o nível 
            e voltamos a tentar*/
            if (L->nseg[j] == NULL)
            {
                continue;
            }

            /*Se o salto dado for grande demais, ou seja o nodo seguinte já tem um ID maior que o que 
            procuramos, continuamos a tentar com um salto de nível mais baixo*/
            if (L->nseg[j]->ID > ID)
            {
                continue;
            }
            /*Se o salto for possível e não for grande demais damos esse salto e saímos do ciclo*/
            L = L->nseg[j];
            break;
        }

        /*O ciclo for pode terminar de 2 formas: ou termina porque conseguimos dar um salto e encontra a
        instrução de break, ou a condição do ciclo (j >= 0) deixa de ser satisfeita. Neste última caso, 
        significa que o elemento que procuramos não se encontra na lista logo retornamos NULL*/
        if (j == -1)
        {
            return NULL;
        }
    }
    return NULL;
}