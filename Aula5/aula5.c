#include <stdio.h>

typedef struct NODE
{
    int valor;
    int nivel;
    struct NODE **nant;
    struct NODE *nseg[];
} Node;

Node *makeNode();
int numNodos(Node *L, Node *X);
int maiorSalto(Node *L);
Node *soma(Node *A, Node *B);      //calcula a soma de duas listas
Node *produto(Node *A, Node *B);   //calcula o produto entre duas listas
Node *produto_Aux(Node *L, int d); //calcula o produto entre uma lista por um dígito

main(int argc, char const *argv[])
{
    /* code */
    return 0;
}

//Contar o numero de nodos entre dois nodos L e X
int numNodos(Node *L, Node *X)
{
    int cont = 0;
    /*Corremos todos os elementos da lista a partir de L*/
    while (L != NULL)
    {
        /*Quando L for igual a X já percorremos o intervalo todo, retornamos o contador*/
        if (L == X)
        {
            return cont;
        }
        /*Damos um salto de nível 0 e incrementamos o contador*/
        L = L->nseg[0];
        cont++;
    }
    return cont;
}

/*Calcular o maior salto que podemos dar numa lista*/
int maiorSalto(Node *L)
{
    int i, salto, max = 0;
    /*Corremos toda a lista L*/
    while (L != NULL)
    {
        /*Começamos por tentar dar o maior salto possível e caso não dê reduzimos o nível*/
        for (i = L->nivel - 1; i >= 0; i--)
        {
            /*Caso seja possível dar o salto, contamos quantos nodos saltámos, através da função numNodos()
            se o salto for maior que o max guardado anteriormente, atualizamos o max, paramos o ciclo for*/
            if (L->nseg[i] != NULL)
            {
                salto = numNodos(L, L->nseg[i]);
                if (salto > max)
                {
                    max = salto;
                }
                break;
            }
        }
        /*O ciclo for pode terminar de duas maneiras, ou através da instrução de break, o que significa que
        conseguimos dar o salto, ou quando j deixa de cumprir a condição j>=0, ou seja quando j==-1. 
        Este último caso significa que estamos no último nodo da lista, logo podemos parar o while*/
        if (i == -1)
            break;

        L = L->nseg[i];
    }
    /*Quando o while terminar teremos armazenado em max o maior salto que é possível dar na lista*/

    return max;
}

/*Calcular a soma entre dois números armazenados em duas listas (cada digito é um nodo)*/
Node *soma(Node *A, Node *B)
{
    Node *R, X;
    /*Necessitamos de uma variavel para armazenar o transporte, uma vez que a soma entre dois digitos
    pode ser superior a 9 (ter mais do que 1 digito)*/
    int transporte = 0;

    /*Verificação se A e B não são NULL*/
    if (A == NULL)
    {
        return B;
    }
    if (B == NULL)
    {
        return A;
    }

    /*Avançamos na lista, até A estar a apontar para o último nodo*/
    while (A->nseg != NULL)
    {
        A = A->nseg;
    }

    /*Avançamos na lista, até B estar a apontar para o último nodo*/
    while (B->nseg != NULL)
    {
        B = B->nseg;
    }

    /*O ciclo while abaixo irá correr enquanto A ou B forem diferentes de NULL, ou seja até termos somado
    todos os dígitos de ambos os números*/
    while (A != NULL || B != NULL)
    {
        /*Armazenamos o transporte em X*/
        //X = makeNode(); //criar a função makeNode()
        X.valor = transporte;
        /*Se A não for NULL, somamos ao tranporte*/
        if (A != NULL)
            X.valor += A->valor;
        /*Se B não for NULL, somamos ao tranporte e a A*/
        if (B != NULL)
            X.valor += B->valor;
        /*Calculamos o tranporte da conta anterior, ou seja, o dígito das dezenas*/
        transporte = X.valor / 10;
        /*Armazenamos em X apenas o dígito das unidades da soma de A+B+transporte*/
        X.valor = X.valor % 10;
        /*Inserimos no início da lista R o nodo X*/
        R = insertFirst(R, X);
        /*avançamos em A ou B, caso não sejam nulos, para o próximo dígito a somar*/
        if (A != NULL)
            A = A->nant;
        if (B != NULL)
            B = B->nant;
    }
    /*No fim do ciclo while teremos corrida ambas as lista A e B do fim para o início, no entanto na soma dos
    últimos dois dígitos poderá ter havido transporte, isto é, o resultado da soma de A e B pode resultar num número
    com mais dígitos que ambas as listas (ex. 99(2 digitos) + 2(1 digito) = 101(3 digitos))
    
    Então temos que colocar o tranporte no resultado caso este exista
    */
    if (transporte)
    {
        //X = makeNode();
        X.valor = transporte;
        R = insertFirst(R, X);
    }
    return R;
}

/*Calcular o produto entre um número L e um dígito d*/
Node *produto_Aux_V1(Node *L, int d)
{
    Node *R, X;
    int transporte = 0;
    if (L == NULL)
    {
        return NULL;
    }

    /*Avançamos até ao último nodo(dígito) de L*/
    while (L->nseg != NULL)
    {
        L = L->nseg;
    }

    /*Corremos L do fim para o início*/
    while (L != NULL)
    {
        //X = makeNode();
        X.valor = transporte;
        /*Somamos ao tranporte o dígito em que nos encontramos multiplicado por d*/
        if (L != NULL)
            X.valor += L->valor * d;
        /*Calculamos o tranporte da conta anterior, ou seja, o dígito das dezenas*/
        transporte = X.valor / 10;
        /*Armazenamos em X apenas o dígito das unidades da operação transporte + L * d */
        X.valor = X.valor % 10;
        /*Inserimos o dígito calculado no início da lista R*/
        R = insertFirst(R, X);
        /*Retrocedemos na lista caso seja possível*/
        if (L != NULL)
            L = L->nant;
    }
    /*No fim do ciclo while teremos corrido a lista L do fim para o início, no entanto na última operação efectuada
    poderá ter havido transporte, isto é, o resultado da multiplicação de L por d pode resultar num número
    com mais dígitos que L
    
    Então temos que colocar o tranporte no resultado caso este exista
    */
    if (transporte > 0)
    {
        //X = makeNode();
        X.valor = transporte;
        R = insertFirst(R, X);
    }
    return R;
}

/*Calcular o produto entre um número L e um dígito d*/
Node *produto_Aux_V2(Node *L, int d)
{
    Node *R = NULL, *aux;
    int i;
    /*Multiplicar um número L por um dígito d é o mesmo que somar L, d vezes
    Então fazemos um ciclo que corre d vezes, e de cada vez soma L ao resultado*/
    for (i = 0; i < d; i++)
    {
        /*Quando utilizamos a função soma ela cria e devolve uma nova lista, então ao somarmos R e L e 
        armazenarmos em R, a antiga lista R(que foi passada como argumento) continua a existir, portanto
        antes de atualizarmos R temos de limpara a lista antiga*/
        aux = soma(R, L);
        R = clearList(R);
        R = aux;
    }
}

/*Calcular o produto entre dois números armazenados em duas listas A e B (cada dígito é um nodo) */
Node *produto(Node *A, Node *B)
{
    Node *R = NULL, *nv, *Aux, *Aux2;
    int c = 0, i;

    /*Caso B não seja uma lista vazia corremos a lista até estarmos no último dígito (nodo)*/
    if (B != NULL)
    {
        while (B->nseg != NULL)
        {
            B = B->nseg;
        }
    }

    /*Corremos a lista B do fim para o inicio*/
    while (B != NULL)
    {
        /*Fazemos o produto entre A e cada dígito de B*/
        Aux = produto_Aux_V1(A, B->valor);
        /*Adicionamos c zeros ao resultado anterior*/
        for (i = 0; i < c; i++)
        {
            nv = makeNode();
            nv->valor = 0;
            Aux = insertLast(Aux, nv);
        }

        /*Somamos ao resultado o último cálculo*/
        Aux2 = soma(R, Aux);

        /*Quando utilizamos a função soma ela cria e devolve uma nova lista, então ao somarmos R e L e 
        armazenarmos em R, a antiga lista R(que foi passada como argumento) continua a existir, 
        portanto antes de atualizarmos R temos de limpar a lista antiga */
        R = clearList(R);
        R = Aux2;
        Aux = clearList(Aux);

        /*Retrocedemos na lista B e incrementamos o número de zeros a adiconar (c)*/
        B = B->nant;
        c++;
    }
    return (R);
}
