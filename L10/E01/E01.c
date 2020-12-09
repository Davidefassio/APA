#include <stdlib.h>
#include <stdio.h>

// Struttura delle attività
// Inizio, fine, durata
typedef struct{
    int sta, fin, dur;
}Att;

void attSel(Att*, int, int*);

int main(int argc, char *argv[]){
    int i, nr;
    char nome_file[20];
    FILE *fp;
    Att *arr;
    int *sol;

    printf("Inserire nome file: ");
    scanf("%s", nome_file);

    fp = fopen(nome_file, "r");
    if(fp == NULL) exit(EXIT_FAILURE);

    fscanf(fp, "%d", &nr);
    arr = (Att*) malloc(nr * sizeof(Att));
    sol = (int*) malloc(nr * sizeof(int));

    for(i = 0; i < nr; ++i){
        fscanf(fp, "%d %d", &arr[i].sta, &arr[i].fin);
        arr[i].dur = arr[i].fin - arr[i].sta;
    }
    fclose(fp);

    attSel(arr, nr, sol);

    free(sol);
    free(arr);

    return 0;
}

void attSel(Att *att, int n, int *sol){
    // Dichiaro le variabili
    int i, j, cnt = 0;
    int *tmp = (int*) malloc(n * sizeof(int));

    // Algoritmo

    // Stampa
}
