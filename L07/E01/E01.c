#include <stdlib.h>
#include <stdio.h>
#include "record.h"

typedef struct{
    int v1;
    int v2;
}Edge;

Record *rec = NULL;

void vertexCover(int *v, int nv, Edge *e, int ne){
    if(search(rec, v))
        return; // Gia analizzato

    int *cov = (int*) calloc(ne, sizeof(int));
    int i, j;

    // Calcola la copertura
    for(i = 0; i < nv; ++i)
        if(v[i] == 1)
            for(j = 0; j < ne; ++j)
                if(i == e[j].v1 || i == e[j].v2)
                    cov[j] = 1;
    
    // Controlla che la copertura sia completa
    for(i = 0; i < ne; ++i)
        if(cov[i] != 1)
            return;

    // Aggiunge alla lista dei vertex covers
    push(rec, v);

    // Ricorre togliendo un vertice
    for(i = 0; i < nv; ++i){
        if(v[i] == 1){
            v[i] = 0;
            vertexCover(v, nv, e, ne);
            v[i] = 1;
        }
    }

    return;
}

int main(int argc, char *argv[]){
    // Gestione file
    FILE *fp = fopen("grafo.txt", "r");
    if(fp == NULL) exit(EXIT_FAILURE);

    int nv, ne, i;
    int *vertex;
    Edge *edges;

    fscanf(fp, "%d %d", &nv, &ne);

    // Inizializza il record globale
    rec = initRec(nv);

    // Inizializza i vettore dei vertici e archi
    vertex = (int*) malloc(nv * sizeof(int));
    edges = (Edge*) malloc(ne * sizeof(Edge));

    for(i = 0; i < nv; ++i)
        vertex[i] = 1; // Uso ogni vertex per la prima vertex cover

    // Archi del grafo
    for(i = 0; i < ne; ++i)
        fscanf(fp, "%d %d", &edges[i].v1, &edges[i].v2);

    // Riempe il Record rec di tutti i vertex cover
    vertexCover(vertex, nv, edges, ne);

    // Stampa il record a video
    print(rec, stdout);

    return 0;
}
