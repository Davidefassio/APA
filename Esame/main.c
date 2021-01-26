#include <stdlib.h>
#include <stdio.h>
#include "grafo.h"

int main(int argc, char *argv[]){
    if(argc != 3) return -1;

    int M, PF, i;

    sscanf(argv[1], "%d", &M);
    sscanf(argv[2], "%d", &PF);

    FILE *fp = fopen("labirinto.txt", "r");
    if(fp == NULL) exit(EXIT_FAILURE);

    Graph g;

    g = GRAPHload(fp);

    PATH p = GRAPHpathBest(g, M, PF);

    for(i = 0; i < p->len; ++i)
        printf("%d ", p->vert[i]);
    printf("\n");

    return 0;
}
