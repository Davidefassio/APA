#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tab_simb.h"
#include "lista.h"

#define MAXL 31

typedef struct grf* Graph; // ADT di I classe

struct path{     // Quasi ADT
    int *vert;   // Indici dei vertici del grafo
    int len;     // Lunghezza di vert
    int prstes;  // Flag per la presa di un tesoro (0: non preso, 1: preso)
    int val, pf; // Valore acquisito lungo il percorso e punti ferita subiti
};

typedef struct path* PATH;

Graph GRAPHload(FILE*);
PATH GRAPHpathLoad(Graph, FILE*);
int GRAPHpathCheck(Graph, PATH, int, int);
PATH GRAPHpathBest(Graph, int, int);
void PATH_print(Graph, PATH);
void GRAPH_free(Graph);
void PATH_free(PATH);

#endif // GRAFO_H_INCLUDED
