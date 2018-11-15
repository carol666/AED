#include <stdio.h>

typedef struct FILA
{
    int idade;
    struct FILA *nseg;
} Fila;

typedef struct NODE
{
    int id;
    struct NODE *nseg;
    struct NODE *nant;
} Node;

Fila *push(Fila *L, Fila *nv);
Fila *pop(Fila **L);
Fila *juntaFilas(Fila **A, Fila **B);
Fila *divideFila(Fila *F, Fila **M, Fila **m);
Node *removeNode(Node *L, Node *r);
int contaOcorrencias(Node *L, int ID);
Node *insertLast(Node *L, Node *nv);

int main(void)
{

    return 0;
}

//Separa os maiores e menores de idade em duas filas
Fila *divideFila(Fila *F, Fila **M, Fila **m)
{
    //Corremos a lista F
    while (F != NULL)
    {
        //Caso seja maior de idade removemos o nodo de F e colocamos na lista M
        if (F->idade >= 18)
        {
            *M = push(*M, pop(&F));
        }
        //Caso contrário removemos de F e colocamos na lista m
        else
        {
            *m = push(*m, pop(&F));
        }
    }

    //Retornamos F que ficará vazia
    return (F);
}

//Unir duas filas A e B
Fila *juntaFilas(Fila **A, Fila **B)
{
    Fila *F;
    /*Corremos enquanto uma das filas ainda tiver elementos*/
    while (*A != NULL || *B != NULL)
    {
        /*Se a fila A ainda tiver elementos removemos o primeiro nodo de A e colocamos em F*/
        if (A != NULL)
        {
            F = push(F, pop(A));
        }

        /*Se a fila B ainda tiver elementos removemos o primeiro nodo de B e colocamos em F*/
        if (B != NULL)
        {
            F = push(F, pop(B));
        }
    }

    //Retornamos F que tem a junção dos elementos de A e B
    return F;
}

//Ordenar uma lista pelo numero de vezes que o id se repete
Node *ordenaOcorrencias(Node *L)
{
    Node *aux, *R = L, *temp = L;
    int max, id_max, c;

    //Corremos toda a lista l
    while (L != NULL)
    {
        max = 0;
        aux = L;
        //Usamos o aux para correr toda a lista e encontrar o id que se repete mais vezes
        while (aux != NULL)
        {
            /*Contamos o número de vezes que o id do aux se repete
            caso este numero seja superior ao max guardado anteriormente, atualizamos o max e guardamos o id*/
            c = contaOcorrencias(aux, aux->id);
            if (c > max)
            {
                id_max = aux->id;
                max = c;
            }
            aux = aux->nseg;
        }
        /*Quando o while termina o aux está a NULL e em id_max temos guardado o id que ocorre mais vezes
        Colocamos o auxiliar novamente igual a L*/
        aux = L;
        //Usamos o aux para correr novamente a lista
        while (aux != NULL)
        {
            /*Sempre que encontramos um nodo com id igual ao guardado anteriormente em id_max
            removemos esse nodo da lista L e colocamos no fim da lista R*/
            if (aux->id == id_max)
            {
                temp = aux->nseg;       //temp guarda temporariamente o endereço do próximo nodo
                L = removeNode(L, aux); //removemos aux da lista L
                R = insertLast(R, aux); //inserimos aux no fim de R
                aux = temp;             //aux toma o valor do endereço do próximo nodo
            }
            else
            {
                aux = aux->nseg;
            }
        }
        /*Em cada iteração do ciclo while voltamos a encontra o id que ocorre mais vezes na nova lista L e 
        inserimos todos os nodos com esse id em R
        Quando o while termina L fica a NULL e R tem todas os nodos ordenados por ocorrencia por ordem decrescente*/
    }
    //Retornamos a lista R ordenada
    return R;
}

//Inserir um elemento numa fila(inserir no fim)
Fila *push(Fila *L, Fila *nv)
{
    //Guardamos em Aux a cabeça da fila
    Fila *Aux = L;

    //Caso a fila esteja vazia devolvemos o elemento a inserir
    if (L == NULL)
    {
        return nv;
    }

    //Corremos a fila enquanto houver um proximo elemento
    while (L->nseg != NULL)
    {
        L = L->nseg;
    }
    //Quando o while termina L aponta para o último nodo da fila

    //Definimos o nseg do último nodo como nv
    L->nseg = nv;

    //Retornamos a cabeça da fila
    return Aux;
}

//Remover um nodo de uma fila(o primeiro nodo)
Fila *pop(Fila **L)
{
    //Guardamos em aux o endereço do 1º nodo da fila
    Fila *aux = *L;

    //Caso a fila esteja vazia retornamos NULL
    if (*L == NULL)
    {
        return *L;
    }

    //Cortamos a ligação do aux com o seu seguinte
    aux->nseg = NULL;
    //definimos a nova cabeça da fila com o segundo nodo
    *L = (*L)->nseg;

    //retornamos o nodo removido
    return (aux);
}

//Contar o numero de vezes que um dado ID se repete
int contaOcorrencias(Node *L, int ID)
{
    int c = 0;

    //Corremos toda a lista L
    while (L != NULL)
    {
        //Caso o id do nodo para o qual L aponta for igual ao ID incrementamos o contador
        if (L->id == ID)
        {
            c++;
        }
        L = L->nseg;
    }
    //Retornamos o contador
    return c;
}

//Remover um nodo de uma lista
Node *removeNode(Node *L, Node *r)
{
    //Se L igual a r, o nodo a remover é o primeiro da lista
    if (L == r)
    {
        //mudamos a cabeça da lista para o segundo nodo
        L = L->nseg;
    }

    //cortamos as ligações do elemento anterior e seguinte de r (caso existam)
    if (r->nant != NULL)
    {
        r->nant->nseg = r->nseg;
    }
    if (r->nseg != NULL)
    {
        r->nseg->nant = r->nant;
    }

    //Cortamos as ligações de r com o seu anterior e seguinte
    r->nant = NULL;
    r->nseg = NULL;

    //Retornamos a cabeça da lista
    return (L);
}

//Inserir um nodo no fim de uma lista duplamente ligada
Node *insertLast(Node *L, Node *nv)
{
    //Guardamos a cabeça da lista em Aux
    Node *Aux = L;

    //Caso a lista esteja vazia a lista passa a ser o nodo nv
    if (L == NULL)
    {
        return nv;
    }

    //Avançamos ate ao ultimo elemento da lista
    while (L->nseg != NULL)
    {
        L = L->nseg;
    }
    //Quando o ciclo termina L aponta para o ultimo nodo da lista

    //Definimos o nseg de L igual ao elemento a inserir no fim da lista e o nant do nv igual ao L
    L->nseg = nv;
    nv->nant = L;

    //Retornamos a cabeça da lista
    return Aux;
}
