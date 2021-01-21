#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

#include <stdlib.h>

// Nodo
typedef struct node* link;

link Node_new(int, int, link);
void Node_free(link);

// Lista
typedef struct lst* Lista;

Lista L_init();
void L_push(Lista, int, int);
link L_extract(Lista, int);
void L_free(Lista);

#endif // LISTA_H_INCLUDED
