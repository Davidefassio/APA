#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "listArray.h"
#include "tabella_simboli.h"

typedef struct grf* Grafo;

// Prototipi
Grafo GRF_initFromFile(FILE*);
void enumVertexes(Grafo);
void checkAdj(Grafo, int);
void generateAdjList(Grafo);
void GRF_free(Grafo);

#endif // GRAFO_H_INCLUDED
