#include <stdlib.h>
#include <stdio.h>
#include "grafo.h"

int main(int argc, char *argv[]){
    char nome_file[31];
    FILE *fp;

    printf("Inserisci nome file: ");
    scanf("%s", nome_file);

    fp = fopen(nome_file, "r");
    if(fp == NULL) exit(EXIT_FAILURE);

    Grafo g = GRF_init(fp);

    fclose(fp);

    return 0;
}
