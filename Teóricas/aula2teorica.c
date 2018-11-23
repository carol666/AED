Nodo *makeNode(){
    Nodo *nv;
    nv = (Nodo*)malloc(sizeof(Nodo));
    (*nv).ID = 0;
    nv->nseg = NULL
    return nv;
}

Nodo *insertFirst(Nodo *L, Nodo *nv){
    nv->nseg = L;
    return nv;
}

int main(){
    Nodo *L = NULL;
    Nodo *x;
    x = makeNode();
    L = insertFirst(L,x);
}