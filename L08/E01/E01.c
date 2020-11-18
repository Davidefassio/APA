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

// Stampa la soluzione sostituendo i numeri con le iniziali della pietra.
void printSol(Vector sol){
    int i;
    for(i = 0; i < sol.len; ++i){
        switch(sol.data[i]){
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
    return;
}


int main(int argc, char *argv[]){
    int i;
    Vector sol, occ;

    occ.len = MAXP;
    occ.data = (int*) malloc(occ.len * sizeof(int));
    
    /**
     * 0: zaffiri
     * 1: rubini
     * 2: topazi
     * 3: smeraldi
     */
    printf("Numero di zaffiri, rubini, topazi e smeraldi:\n");
    for(i = 0; i < MAXP; ++i)
        scanf("%d", &occ.data[i]);

    sol = creaCollana(occ);

    printSol(sol);

    free(occ.data);
    free(sol.data);

    return 0;
}
