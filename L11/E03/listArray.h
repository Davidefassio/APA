/*
    Libreria per un vettore di liste rappresentato come quasi-ADT.
*/

#ifndef LISTARRAY_H_INCLUDED
#define LISTARRAY_H_INCLUDED

#include <stdlib.h>

// Strutture dati
typedef struct{
    struct node **data;
    int len;
}listArray;

// Prototipi listArray
listArray* LA_init(int);
void LA_push(listArray*, int, int, int);
int LA_searchById(listArray*, int, int);
void LA_free(listArray*);

#endif // LISTARRAY_H_INCLUDED
