#include "listArray.h"

// Gestione lista semplice
// Struttura dati + funzioni
struct node{
    int id;
    int value;
    struct node* next;
};

typedef struct node* link;

// Crea e inizializza un nuovo nodo
// Returno un puntatore al nodo
link node_create(int id, int value, link next){
    link tmp = (link) malloc(sizeof(struct node));
    tmp->id = id;
    tmp->value = value;
    tmp->next = next;
    return tmp;
}

// Aggiunge in testa un nodo alla lista
link list_push(link head, int id, int value){
    return node_create(id, value, head);
}

// Cerca per id un nodo
// Se lo trova return value
// Se no return -1
int list_searc(link head, int id){
    if(head == NULL) return -1;
    if(head->id == id) return head->value;
    return list_searc(head->next, id);
}

// Libera la memoria della lista
void list_free(link head){
    if(head == NULL) return;
    list_free(head->next);
    free(head);
}

// listArray
/// Inizializzi una listArray
listArray* LA_init(int l){
    listArray* tmp = (listArray*) malloc(sizeof(listArray));
    tmp->len = l;
    tmp->data = (link*) calloc(l, sizeof(link));
    if(tmp->data == NULL) exit(EXIT_FAILURE);
    return tmp;
}

/// pushi un node in testa a una lista
void LA_push(listArray *la, int index, int id, int value){
    la->data[index] = list_push(la->data[index], id, value);
}

/// cerca l'id int(2) nella lista all'indice int(1), value se trovato, -1 se non c'e'
int LA_searchById(listArray *la, int index, int id){
    return list_searc(la->data[index], id);
}

/// libera tutti i nodi e la listArray
void LA_free(listArray *la){
    int i;
    for(i = 0; i < la->len; ++i)
        list_free(la->data[i]);
    free(la->data);
    free(la);
}

