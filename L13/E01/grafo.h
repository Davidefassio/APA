#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

#include "tab_simb.h"
#include "lista.h"
#include "mat.h"

typedef struct grf* Grafo;

Grafo GRF_init(FILE*);
int GRF_getNumVert(Grafo);
void GRF_DAGify(Grafo);
void GRF_printLongestPath(Grafo, int);
void GRF_free(Grafo);


#endif // GRAFO_H_INCLUDED
