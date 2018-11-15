#include <stdio.h>
#include <stdlib.h>

typedef struct NODE
{
    int id;
    struct NODE *nant;
    struct NODE *nseg;
} Node;

int listaOrdenada(Node *L);
Node *insertLast(Node *L, Node *nv);
int totalElementosDiferentes(Node *L);
Node *inverteLista(Node *L);
void printLista(Node *L);
Node *insertFirst(Node *L, Node *nv);

int main(void)
{
    Node *P, *Q, *R, *L = NULL;

    P = malloc(sizeof(Node));
    Q = malloc(sizeof(Node));
    R = malloc(sizeof(Node));

    P->id = 1;
    P->nseg = NULL;
    P->nant = NULL;
    Q->id = 2;
    Q->nseg = NULL;
    Q->nant = NULL;
    R->id = 3;
    R->nseg = NULL;
    R->nant = NULL;

    L = insertLast(L, P);
    L = insertLast(L, Q);
    L = insertLast(L, R);
    printLista(L);
    listaOrdenada(L) ? printf("Esta ordenada!\n") : printf("Nao esta ordenada!\n");
    printf("Elementos Diferentes: %d\n", totalElementosDiferentes(L));
    L = inverteLista(L);
    printLista(L);
    return 0;
}

//Verificar se a lista se encontra ordenada, retorna 1 em casa positivo e 0 em caso negativo
int listaOrdenada(Node *L)
{
    //Se a lista estiver vazia então está ordenada, retornamos 1
    if (L == NULL)
    {
        return 1;
    }

    //Continuar enquanto houver próximo elemento na lista
    while (L->nseg != NULL)
    {
        if (L->nseg->id < L->id) //Se o ID do nodo seguinte for menor do que o de L
        {
            return 0; //Então a lista não está ordenada, retornamos L e a função termina
        }
        L = L->nseg; //Avançar para o próximo nodo
    }
    return 1; //Caso o while termina significa que nunca entrou no if, logo a lista esta ordenada
}

//Inserir um nodo no fim da lista
Node *insertLast(Node *L, Node *nv)
{
    Node *Aux = L; //Guardamos a cabeça da lista em Aux

    //Caso a lista esteja vazia retornamos o endereço do nodo a inserir
    if (L == NULL)
    {
        return nv;
    }

    while (L->nseg != NULL) //Continuar enquanto houver um próximo nodo
    {
        L = L->nseg; //avançar para o próximo nodo na lista
    }
    //Quando o while terminar, L aponta para o último elemento da lista

    //definimos o nseg de L como nodo a inserir no fim da lista e o nant de nv como L
    L->nseg = nv;
    nv->nant = L;

    //Retornamos a cabeça da lista
    return Aux;
}

//Calcular o numero de elementos com IDs diferentes na lista L
int totalElementosDiferentes(Node *L)
{
    int total = 0;
    Node *aux;

    //Corremos a lista toda
    while (L != NULL)
    {
        aux = L->nant; //Definimos o aux igual ao nodo anterior a L

        //Corremos a lista para trás desde o nodo em que nos encontramos
        while (aux != NULL)
        {
            //Se encontramos algum nodo para trás com ID igual ao atual paramos
            if (aux->id == L->id)
            {
                break;
            }
            aux = aux->nant;
        }
        /*Se o aux for igual a NULL significa que corremos todos os elementos anteriores a L e não encontrámos
        nenhum com ID igual, então encrementamos o total de elementos diferentes*/
        if (aux == NULL)
            total++;
        L = L->nseg;
    }

    //Retornamos o total
    return total;
}

/*int totalElementosDiferentes(Node *L)
{
    int total = 0;
    Node *aux;

    while (L->nseg != NULL)
    {
        aux = L->nseg;
        while (aux != NULL)
        {
            if (aux->id == L->id)
            {
                break;
            }
            aux = aux->nseg;
        }
        if (aux == NULL)
            total++;
        L = L->nseg;
        if (L->nseg == NULL)
        {
            total++;
        }
    }
    return total;
}*/

//Inverter a ordem de uma lista
Node *inverteLista(Node *L)
{
    Node *aux, *R = NULL;

    //Corremos toda a lista
    while (L != NULL)
    {
        //Guardamos em aux o nodo em que nos encontramos
        aux = L;

        //Avançamos o L na lista
        L = L->nseg;

        //Cortamos a ligação do aux com o seu seguinte
        aux->nseg = NULL;

        //Caso o L não seja NULL cortamos a ligação do L com o seu anterior
        if (L != NULL)
            L->nant = NULL;
        //Inserimos o aux no início da lista R
        R = insertFirst(R, aux);
    }
    //Retornamos a lista R
    return R;
}

void printLista(Node *L)
{
    //Corremos toda a lista
    while (L != NULL)
    {
        //Imprimimos o id do nodo para o qual L aponta
        printf("%d\n", L->id);
        L = L->nseg;
    }
}

Node *insertFirst(Node *L, Node *nv)
{
    /*Para inserir um nodo no início de uma lista basta colocar o nant da cabeça da lista apontar para esse nodo
    e o nseg do nodo a apontar para a cabeça da lista e retornamos o nodo nv, que é a nova cabeça da lista*/
    nv->nseg = L;
    L->nant = nv;
    return (nv);
}

/*Remover os nodos com ids iguais - Funcionamento semelhante à totalElementosDiferentes()*/
Node *removeRepetidos(Node *L)
{
    Node *head = L;
    Node *aux, *aux2;

    //Corremos toda a lista
    while (L != NULL)
    {
        aux = L->nant;

        //Corremos a lista para trás desde o nodo em que nos encontramos
        while (aux != NULL)
        {
            //Se encontramos um elemento repetido paramos o ciclo
            if (aux->id == L->id)
            {
                break;
            }
            aux = aux->nant;
        }
        /*Caso o aux não seja NULL significa que entrámos no if do while
        então L é uma repetição de aux*/
        if (aux != NULL)
        {
            //Cortamos as ligações de L
            L->nant->nseg = L->nseg;
            if (L->nseg != NULL)
            {
                L->nseg->nant = L->nant;
            }

            //A variável aux2 guarda temporariamente o valor do seguinte de L
            aux2 = L->nseg;

            //Libertamos o espaço de memória do L
            free(L);

            //L toma o valor do próximo elemento da lista
            L = aux2;
        }
        else
        {
            //Caso aux seja NULL então L não está repetido e avançamos na lista
            L = L->nseg;
        }
    }

    //Retornamos a cabeça da lista
    return head;
}
