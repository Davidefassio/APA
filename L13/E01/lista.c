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

void Node_free(link n){
    free(n);
}


// Dichiarazione e funzioni LISTA
struct lst{
    link head;
    int n;
};

Lista L_init(){
    Lista tmp = (Lista) malloc(sizeof(struct lst));
    tmp->head = NULL;
    tmp->n = 0;
    return tmp;
}

void L_push(Lista lst, int id, int val){
    lst->head = Node_new(id, val, lst->head);
    ++(lst->n);
}

link L_extract(Lista lst, int id){
    link ptr, tmp;

    if(lst->head->id == id){ // Estrazione in testa
        tmp = lst->head;
        lst->head = lst->head->next;
        return tmp;
    }

    // Estrazione NON in testa
    for(ptr = lst->head; ptr->next != NULL; ptr = ptr->next){
        if(ptr->next->id == id){
            tmp = ptr->next;
            ptr->next = ptr->next->next;
            return tmp;
        }
    }

    return NULL;
}

static void freeR(link n){
    if(n == NULL) return;
    freeR(n->next);
    Node_free(n);
}

void L_free(Lista lst){
    freeR(lst->head);
    free(lst);
}
