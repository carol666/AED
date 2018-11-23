int sorteiaNivel(){
    int i;
    float x;
    while(1){
        x = rand();
        for(i=0;i<TN;i++){
            if(x > 1/pow(2,i+1))
                return i;
        }
    }
}

Node* findNext(Node *L, int ID, int i){
    int j;
    Node *aux = L;
    while(aux != NULL){
        if( (aux->ID > ID) && (aux->nivel >= i) )  // se tiver um ID superior e um nível maior ou igual 
            return aux;
        for(j = (aux->nivel)-1 ; j >= 0 ; j--){ // Percorrer os níveis até chegar ao 0
            if(aux->nseg[j] == NULL)        // Existe com nível j ?
                continue;                   // Se não, então prossegue para a próxima iteração do loop
            if(aux->nseg[j]->ID > ID)       // Será o ID dele maior que o do aux ?
                continue;                   // Se não, então prossegue para a próxima iteração do loop
            aux = aux->nseg[j];             // Se chegar a este ponto já encontrou, o aux passar para o seguinte(para ser analisado)
            break;                          // Quebrar loop
        }
    }
    return NULL;
    
}