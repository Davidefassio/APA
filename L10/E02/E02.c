#include <stdlib.h>
#include <stdio.h>
#include "tensor.h"

int creaCollana(int*, int*);
void printCollana(int*, int);

int main(int argc, char * argv[]){
    int i, nr, len;
    int gems[4], *sol = NULL;

    Tensor5d mem;
    mem = TensorInit(4, 1, 1, 1, 1);

    FILE *fp;
    char nome_file[30];

    printf("Inserire nome file: ");
    scanf("%s", nome_file);
    fp = fopen(nome_file, "r");
    if(fp == NULL) exit(EXIT_FAILURE);

    fscanf(fp, "%d", &nr);

    for(i = 0; i < nr; ++i){ // Ciclo su ogni collana
        fscanf(fp, "%d %d %d %d", &gems[0], &gems[1], &gems[2], &gems[3]);

        // Lunghezza massima collana
        len = gems[0] + gems[1] + gems[2] + gems[3];
        // Vettore riallocato dinamicamente della soluzione
        sol = (int*) realloc(sol, len * sizeof(int));

        // Crea una collana e salvala in sol
        len = creaCollana(gems, sol);

        printCollana(sol, len);
    }
    fclose(fp);

    // Free
    free(sol);
    TensorFree(mem);

    return 0;
}

void printCollana(int *v, int n){
    int i;
    printf("%d: ", n);
    for(i = 0; i < n; ++i){
        switch(v[i]){
        case 0:
            printf("Z ");
            break;
        case 1:
            printf("R ");
            break;
        case 2:
            printf("T ");
            break;
        case 3:
            printf("S ");
            break;
        default:
            exit(EXIT_FAILURE);
            break;
        }
    }
    printf("\n");
}

int creaCollana(int *gems, int *sol){
    // TODO
    return 0;
}
