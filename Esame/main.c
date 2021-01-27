#include <stdlib.h>
#include <stdio.h>
#include "grafo.h"

int main(int argc, char *argv[]){
    if(argc != 3) return -1;

    int M, PF, s = 0;
    char nome_file[31];

    sscanf(argv[1], "%d", &M);
    sscanf(argv[2], "%d", &PF);

    FILE *fp = fopen("labirinto.txt", "r");
    if(fp == NULL) exit(EXIT_FAILURE);

    Graph g;

    g = GRAPHload(fp);

    fclose(fp);

    PATH p;

    printf("Trovare il percorso migliore (1) oppure controllare un percorso (2) ?\n> ");
    scanf("%d", &s);

    if(s == 1){
        p = GRAPHpathBest(g, M, PF);
        PATH_print(g, p);
    }

    if(s == 2){
        printf("Inserire nome file: ");
        scanf("%s", nome_file);

        fp = fopen("path.txt", "r");
        if(fp == NULL) exit(EXIT_FAILURE);

        PATH p = GRAPHpathLoad(g, fp);

        printf("Percorso %s\n", (GRAPHpathCheck(g, p, M, PF) == 1) ? "corretto" : "irregolare");

        PATH_print(g, p);
    }

    return 0;
}
