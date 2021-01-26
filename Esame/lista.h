#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

#include <stdlib.h>

// Nodo
typedef struct node* link;

link Node_new(int, int, link);
int Node_getId(link);
int Node_getVal(link);
link Node_getNext(link);
void Node_free(link);

// Lista
typedef struct lst* Lista;

Lista Lista_init();
void Lista_push(Lista, int, int);
int Lista_search(Lista, int);
int Lista_getVal(Lista, int);
link Lista_getHead(Lista);
void Lista_free(Lista);

#endif // LISTA_H_INCLUDED
