#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Definisco un tipo che e' una stringa di MAXL caratteri
#define MAXL 31
typedef char id[MAXL];

typedef struct grf* Grafo;

Grafo GRF_init(FILE*);
int GRF_getNodeIndex(Grafo, id);
void GRF_free(Grafo);


#endif // GRAFO_H_INCLUDED
