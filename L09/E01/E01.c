#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct{
    int start;
    int finish;
}att;

void attSel(int, att*);
void attSelR(int, att*, int**, int*, int*, int);

int main(int argc, char *argv[]){
    int nr, i;
    att *atts;

    FILE *fp;
    char nome_file[20];

    printf("Inserire nome file: ");
    scanf("%s", nome_file);
    fp = fopen(nome_file, "r");
    if(fp == NULL) exit(EXIT_FAILURE);

    fscanf(fp, "%d", &nr);
    atts = (att*) malloc(nr * sizeof(att));

    for(i = 0; i < nr; ++i)
        fscanf(fp, "%d %d", &atts[i].start, &atts[i].finish);
    fclose(fp);

    attSel(nr, atts);
    free(atts);

    return 0;
}

void attSel(int l, att *arr){
    int i, max = -1;
    int *sol = (int*) calloc(l, sizeof(int));
    int *tmp = (int*) calloc(l, sizeof(int));

    attSelR(l, arr, &sol, tmp, &max, 0);

    printf("Somma delle durate = %d\n", max);
    for(i = 0; i < l; ++i)
        if(sol[i] == 1)
            printf("(%d, %d) ", arr[i].start, arr[i].finish);
    printf("\n");

    free(sol);
    free(tmp);
}

void attSelR(int l, att *arr, int **sol, int *tmp, int *best, int pos){
    int dur = 0, i;
    if(pos >= l){
        // Controllo di massimalita
        for(i = 0; i < l; ++i)
            if(tmp[i] == 1)
                dur += (arr[i].finish - arr[i].start);
        
        // Cambio la soluzione migliore
        if(dur > *best){
            *best = dur;
            memcpy(*sol, tmp, l *sizeof(int));
        }

        return;
    }

    // Metto uno zero
    attSelR(l, arr, sol, tmp, best, pos+1);

    // Se non ho sovrapposizioni metto un uno
    for(i = 0; i < pos; ++i)
        if(tmp[i] == 1 && (arr[i].start < arr[pos].finish) && (arr[pos].start < arr[i].finish))
            return;
    
    tmp[pos] = 1;
    attSelR(l, arr, sol, tmp, best, pos+1);
    tmp[pos] = 0;  // Backtrack

    return;
}
