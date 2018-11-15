#include <stdio.h>
#include <stdlib.h>

typedef struct NODE
{
    int id;
    struct NODE *nseg;
} Node;

int countNodes(Node *L);
Node *insertLast(Node *L, Node *nv);
Node *removeFirst(Node *L);
Node *removeLast(Node *L);
Node *clearList(Node *L);
Node *insertFirst(Node *L, Node *nv);

int main(void)
{
    Node *P, *R, *X = NULL;
    int a;

    P = malloc(sizeof(Node));
    P->id = 1245;
    P->nseg = NULL;

    R = malloc(sizeof(Node));
    R->id = 2323;
    R->nseg = NULL;

    X = insertLast(X, P);
    X = insertLast(X, R);
    a = countNodes(X);
    printf("%d\n", a);
    X = removeFirst(X);
    a = countNodes(X);
    printf("%d\n", a);
    X = removeLast(X);
    a = countNodes(X);
    printf("%d\n", a);
    X = clearList(X);
    a = countNodes(X);
    printf("%d\n", a);

    return 0;
}

//contar o numero de nodos numa lista
int countNodes(Node *L)
{
    int count = 0; //iniciamos o num de nodos o 0, caso a lista esteja vazia retorna este numero

    while (L != NULL) //enquanto a lista nao tiver terminado
    {
        count++;     //incrimentar o numero de nodos
        L = L->nseg; //avançar na lista
    }

    return count; //retornar o numero de nodos
}

//Inserir um nodo no fim da lista
Node *insertLast(Node *L, Node *nv)
{
    Node *Aux = L; //Guardamos a cabeça da lista porque vamos fazer alterações à lista L

    if (L == NULL) //se a lista estiver vazia retornamos o elemento que queremos inserir como a nova lista
    {
        return nv;
    }

    while (L->nseg != NULL) //continuar enquanto houver próximo elemento, pára quando estivermos no último nodo
    {
        L = L->nseg;
    }
    //quando o while termina o L está a apontar para o último elemento da lista

    L->nseg = nv; //definimos que o nseg do último nodo é o nodo a adicionar

    return Aux; //retornamos a cabeça da lista
}

//Remover o primeiro nodo de uma lista
Node *removeFirst(Node *L)
{
    Node *aux = L; //Guardamos o endereço do primeiro nodo da lista

    if (L == NULL) //se a lista estiver vazia não há um 1º nodo para remover por isso retornamos a lista vazia
    {
        return L;
    }

    L = L->nseg; //avançamos para o 2º nodo da lista

    free(aux); //libertamos o espaço de memória do primeiro nodo da lista

    return (L); //retornamos a nova cabeça da lista, que passa a ser o 2º nodo
}

//Remover o último elemento da lista
Node *removeLast(Node *L)
{
    if (L == NULL) //se a lista estiver vazia não há nenhum nodo para remover por isso retornamos a lista vazia
    {
        return L;
    }

    Node *aux = L, *B = L; //Guardamos a cabeça da lista em aux e B

    while (L->nseg != NULL) //Continuar enquanto houver um próximo nodo na lista
    {
        B = L;       //B guarda o valor atualizado de L
        L = L->nseg; //Avançamos com o L
    }
    //Quando o while terminar o L aponta para o último elemento da lista e o B para o penúltimo elemento da lista

    free(L);        //Libertamos o espaço de memória do último nodo
    B->nseg = NULL; //O nseg do penúltimo nodo passa a ser NULL

    //Se o B for igual a L significa que nunca entrámos no while, ou seja, a lista só tinha 1 elemento então retornamos NULL
    //Caso contrário retornamos a cabeça da lista
    return (B == L ? NULL : aux);
}

//Apagar a lista
Node *clearList(Node *L)
{

    while (L != NULL) //Continuar enquanto a lista não estiver vazia
    {
        L = removeFirst(L); //Chamar a função removeFirst para apagar a atual cabeça da lista
    }

    return (L); //retornar o L que está a NULL
}

//Inserir um nodo na cabeça da lista
Node *insertFirst(Node *L, Node *nv)
{
    nv->nseg = L; //Definimos o nseg do nodo a adicionar à lista como sendo a cabeça da lista onde o queremos adiconar
    return (nv);  //Retornamos o nv, que é a nova cabeça da lista
}
