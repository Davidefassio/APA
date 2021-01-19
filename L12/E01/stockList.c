#include "stockList.h"

typedef struct node{
    Stock data;
    struct node* prev;
    struct node* next;
}Node;

struct stockList{
    Node* head;
};

// Node's functions
static Node* Node_new(Stock s){
    Node *tmp = (Node*) malloc(sizeof(Node));
    tmp->data = s;
    tmp->prev = tmp->next = NULL;
    return tmp;
}

static void Node_free(Node *n){
    Stock_free(n->data);
    free(n);
}


// StockList's fuctions
StockList SL_init(){
    StockList tmp = (StockList) malloc(sizeof(struct stockList));
    tmp->head = NULL;
    return tmp;
}

void SL_insert(StockList sl, Stock s){
    // Crea nodo nuovo
    Node *n = Node_new(s);

    // Lista vuota
    if(sl->head == NULL){
        sl->head = n;
        return;
    }

    Node *ptr = sl->head;

    // Aggiunta in testa
    if(Stock_cmp_cod(s, ptr->data) == -1){ // Non so se mettere 1 o -1 (ordine alfabetico: a,b,...,z)
        sl->head = n;
        n->next = ptr;
        return;
    }

    while(Stock_cmp_cod(s, ptr->data) == 1){ // Non so se mettere 1 o -1 (ordine alfabetico: a,b,...,z)
        // Aggiunta in coda
        if(ptr->next == NULL){
            n->prev = ptr;
            ptr->next = n;
            return;
        }

        ptr = ptr->next;
    }

    // Aggiunta in mezzo
    n->prev = ptr->prev;
    n->next = ptr->prev->next;
    n->prev->next = n->next->prev = n;
    return;
}

void SL_insertFromFile(StockList sl, FILE *fp){
    Stock tmp = NULL;
    int n, i;
    char cod[MAXL];

    fscanf(fp, "%d", &n);

    for(i = 0; i < n; ++i){
        fscanf(fp, "%s", cod);

        tmp = SL_search(sl, cod);

        if(tmp == NULL){
            tmp = Stock_init(cod);
            Stock_fscan(fp, tmp);
            SL_insert(sl, tmp);
        }
        else{
            Stock_fscan(fp, tmp);
        }
    }
}

Stock SL_search(StockList sl, char *str){
    Node *ptr = sl->head;

    while(ptr != NULL){
        if(strcmp(Stock_getCode(ptr->data), str) == 0){
            return ptr->data;
        }
        ptr = ptr->next;
    }
    return NULL;
}

void SL_delete(StockList sl, char *str){
    // Non fai nulla
    if(sl->head == NULL) return;

    Node *ptr = sl->head;

    // Cancella in testa
    if(strcmp(Stock_getCode(ptr->data), str) == 0){
        sl->head = ptr->next;
        Node_free(ptr);
        return;
    }

    while(1){
        // Cancella in mezzo
        if(strcmp(Stock_getCode(ptr->data), str) == 0){
            ptr->prev->next = ptr->next;
            ptr->next->prev = ptr->prev;
            Node_free(ptr);
            return;
        }

        // Cancella in coda
        if(ptr->next == NULL){
            ptr->prev->next = NULL;
            Node_free(ptr);
            return;
        }

        ptr = ptr->next;
    }
}

// Funzione privata per cancellare una lista ricorsivamente
static void freeR(Node *n){
    if(n == NULL) return;
    freeR(n->next);
    Node_free(n);
}

void SL_free(StockList sl){
    freeR(sl->head);
    free(sl);
}
