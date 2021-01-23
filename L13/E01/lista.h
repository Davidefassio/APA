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

Lista L_init();
void L_push(Lista, int, int);
void L_pushNode(Lista, link);
link L_extract(Lista, int);
link L_getHead(Lista);
void L_free(Lista);

#endif // LISTA_H_INCLUDED
