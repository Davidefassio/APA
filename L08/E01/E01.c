#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXP 4

// Mi permette di avere sempre la lunghezza che accompagna l'array.
typedef struct{
    int *data;
    int len;
}Vector;

// 1 = tutti zero.
// 0 = tutti gli altri casi.
int isZero(Vector v){
    int i;
    for(i = 0; i < v.len; ++i)
        if(v.data[i] != 0)
            return 0;
    return 1;
}

// Il Vector sol e' passato by reference per permettere il cambio di sol->len.
// Il puntatore perf serve a bloccare ogni azione dopo aver
// trovato una soluzione che utilizza tutte le pietre.
void creaCollanaR(Vector occ, Vector *sol, Vector tmp, int pos, int *perf){
    int i;

    if(isZero(occ)){
        sol->len = pos;
        *perf = 1;
        memcpy(sol->data, tmp.data, tmp.len * sizeof(int));
        return;
    }

    if((pos == 0 || tmp.data[pos-1] % 2 == 0) && occ.data[0] > 0){ // Zaffiri
        --occ.data[0];
        tmp.data[pos] = 0;
        ++tmp.len;

        creaCollanaR(occ, sol, tmp, pos+1, perf);

        if(*perf)
            return;

        --tmp.len;
        ++occ.data[0];
    }
    if((pos == 0 || tmp.data[pos-1] % 2 == 0) && occ.data[1] > 0){ // Rubini
        --occ.data[1];
        tmp.data[pos] = 1;
        ++tmp.len;

        creaCollanaR(occ, sol, tmp, pos+1, perf);

        if(*perf)
            return;

        --tmp.len;
        ++occ.data[1];
    }
    if((pos == 0 || tmp.data[pos-1] % 2 != 0) && occ.data[2] > 0){ // Topazi
        --occ.data[2];
        tmp.data[pos] = 2;
        ++tmp.len;

        creaCollanaR(occ, sol, tmp, pos+1, perf);

        if(*perf)
            return;

        --tmp.len;
        ++occ.data[2];
    }
    if((pos == 0 || tmp.data[pos-1] % 2 != 0) && occ.data[3] > 0){ // Smeraldi
        --occ.data[3];
        tmp.data[pos] = 3;
        ++tmp.len;

        creaCollanaR(occ, sol, tmp, pos+1, perf);

        if(*perf)
            return;

        --tmp.len;
        ++occ.data[3];
    }

    if(pos > sol->len){
        sol->len = pos;
        memcpy(sol->data, tmp.data, tmp.len * sizeof(int));
    }

    return;
}

// Wrapper di creaCollanaR.
Vector creaCollana(Vector occ){
    int i, sum = 0, perfection = 0;
    for(i = 0; i < occ.len; ++i)
        sum += occ.data[i];

    Vector tmp, sol;
    tmp.len = 0;
    sol.len = 0;
    tmp.data = (int*) malloc(sum * sizeof(int));
    sol.data = (int*) malloc(sum * sizeof(int));

    creaCollanaR(occ, &sol, tmp, 0, &perfection);

    free(tmp.data);
    return sol;
}

int main(int argc, char *argv[]){
    FILE *fp;
    char nome_file[30];
    int i, nr;
    Vector sol, occ;

    occ.len = MAXP;
    occ.data = (int*) malloc(occ.len * sizeof(int));
    
    printf("Inserire nome file: ");
    scanf("%s", nome_file);
    fp = fopen(nome_file, "r");
    if(fp == NULL) exit(EXIT_FAILURE);

    fscanf(fp, "%d", &nr);

    for(i = 0; i < nr; ++i){
        fscanf(fp, "%d %d %d %d", &occ.data[0], &occ.data[1], &occ.data[2], &occ.data[3]);

        printf("TEST #%d\n", i+1);
        printf("zaffiro = %d, ", occ.data[0]);
        printf("rubino = %d, ", occ.data[1]);
        printf("topazio = %d, ", occ.data[2]);
        printf("smeraldo = %d, ", occ.data[3]);
        printf("TOT = %d\n", occ.data[0] + occ.data[1] + occ.data[2] + occ.data[3]);

        sol = creaCollana(occ);

        printf("Collana massima di lunghezza %d\n", sol.len);
    }

    free(occ.data);
    free(sol.data);

    return 0;
}
