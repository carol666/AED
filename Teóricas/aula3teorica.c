Nodo *insertOrder(Nodo *L, Nodo *nv){
    Nodo *aux = L;
    while(aux != NULL){
        if(aux->ID > L->ID)
            break;
        aux=aux->nseg;
    }
    if(aux == NULL)
        return insertFirst(L,nv);
    if(aux->nant == NULL)
        return insertFirst(L,nv);
    nv->nseg = aux;
    aux->nant = nv;
    nv->nant = aux->nant;
    nv->nant->nseg = nv;
    return L;
}

Nodo *unionLists(Nodo **A, Nodo **B){
    Nodo *aux, *L =(*A);
    *A = NULL;
    while((*B)!=NULL){
        aux = *B;
        *B = (*B)->nseg;
        aux->nseg=NULL;
        if(*B != NULL)
            (*B)->nant=NULL;
        B = insertOrder(B,aux);
    }
    return B;
}