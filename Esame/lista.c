#include "lista.h"

// Dichiarazione e funzioni NODO
struct node{
    int id;
    int val;
    struct node* next;
};

link Node_new(int id, int val, link next){
    link tmp = (link) malloc(sizeof(struct node));
    tmp->id = id;
    tmp->val = val;
    tmp->next = next;
    return tmp;
}

int Node_getId(link n){
    return n->id;
}

int Node_getVal(link n){
    return n->val;
}

link Node_getNext(link n){
    return n->next;
}

void Node_free(link n){
    free(n);
}


// Dichiarazione e funzioni LISTA
struct lst{
    link head;
    int n;
};

Lista Lista_init(){
    Lista tmp = (Lista) malloc(sizeof(struct lst));
    tmp->head = NULL;
    tmp->n = 0;
    return tmp;
}

void Lista_push(Lista lst, int id, int val){
    lst->head = Node_new(id, val, lst->head);
    ++(lst->n);
}

int Lista_search(Lista lst, int id){
    link ptr;
    for(ptr = lst->head; ptr != NULL; ptr = ptr->next)
        if(ptr->id == id)
            return 1;
    return 0;
}

int Lista_getVal(Lista lst, int id){
    link ptr;
    for(ptr = lst->head; ptr != NULL; ptr = ptr->next)
        if(ptr->id == id)
            return ptr->val;
    return 0;
}

link Lista_getHead(Lista lst){
    return lst->head;
}

static void freeR(link n){
    if(n == NULL) return;
    freeR(n->next);
    Node_free(n);
}

void Lista_free(Lista lst){
    freeR(lst->head);
    free(lst);
}
