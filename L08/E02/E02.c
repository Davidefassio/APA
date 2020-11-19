#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Mi permette di avere sempre la lunghezza che accompagna l'array.
typedef struct{
    int *data;
    int len;
    int value;
    int cntZ, cntS; // Evita il passaggio sul vettore ogni volta
}Vector;

// 1 = tutti zero.
// 0 = tutti gli altri casi.
int isZero(int *occ){
    return occ[0] == 0 && occ[1] == 0 && occ[2] == 0 && occ[3] == 0;
}

// Il Vector sol e' passato by reference per permettere il cambio di sol->len.
// Il puntatore perf serve a bloccare ogni azione dopo aver
// trovato una soluzione che utilizza tutte le pietre.
void creaCollanaR(int *occ, Vector *sol, Vector tmp, int pos, int maxr, int prev, int rep, int *perf){
    if(isZero(occ)){ // Finito le pietre
        if(tmp.cntZ <= tmp.cntS){ // Devo avere piu smeraldi che zaffiri
            sol->len = pos;
            sol->value = tmp.value;
            *perf = 1;
            memcpy(sol->data, tmp.data, tmp.len * sizeof(int));
        }
        return;
    }

    // Pruning
    // Non ho abbastanza smeraldi da aggiungere per compensare gli zaffiri
    if(tmp.cntZ > tmp.cntS + occ[3])
        return;

    if((pos == 0 || tmp.data[pos-1] % 2 == 0) && occ[0] > 0){ // Zaffiri
        --occ[0]; // Tolgo un'occorrenza
        tmp.data[pos] = 0; // Inserisco la pietra nella soluzione temporanea
        ++tmp.len; // Incremento la lunghezza della soluzione temporanea
        tmp.value += occ[4]; // Incremento il valore
        ++tmp.cntZ; // Incremento il conteggio degli zaffiri

        if(prev == 0){ // La pietra prima era uno zaffiro
            if(rep < maxr - 1){ // Ho raggiunto maxrip
                creaCollanaR(occ, sol, tmp, pos+1, maxr, 0, rep+1, perf);
            }
        }
        else{ // La pietra prima non era uno zaffiro
            creaCollanaR(occ, sol, tmp, pos+1, maxr, 0, 0, perf);
        }

        // Backtracking
        --tmp.cntZ;
        tmp.value -= occ[4];
        --tmp.len;
        ++occ[0];

        // Se ho una collana perfetta ritorno direttamente
        if(*perf)
            return;
    }
    if((pos == 0 || tmp.data[pos-1] % 2 == 0) && occ[1] > 0){ // Rubini
        --occ[1];
        tmp.data[pos] = 1;
        ++tmp.len;
        tmp.value += occ[5];

        if(prev == 1){
            if(rep < maxr - 1){
                creaCollanaR(occ, sol, tmp, pos+1, maxr, 1, rep+1, perf);
            }
        }
        else{
            creaCollanaR(occ, sol, tmp, pos+1, maxr, 1, 0, perf);
        }

        tmp.value -= occ[5];
        --tmp.len;
        ++occ[1];

        if(*perf)
            return;
    }
    if((pos == 0 || tmp.data[pos-1] % 2 != 0) && occ[2] > 0){ // Topazi
        --occ[2];
        tmp.data[pos] = 2;
        ++tmp.len;
        tmp.value += occ[6];

        if(prev == 2){
            if(rep < maxr - 1){
                creaCollanaR(occ, sol, tmp, pos+1, maxr, 2, rep+1, perf);
            }
        }
        else{
            creaCollanaR(occ, sol, tmp, pos+1, maxr, 2, 0, perf);
        }

        tmp.value -= occ[6];
        --tmp.len;
        ++occ[2];

        if(*perf)
            return;
    }
    if((pos == 0 || tmp.data[pos-1] % 2 != 0) && occ[3] > 0){ // Smeraldi
        --occ[3];
        tmp.data[pos] = 3;
        ++tmp.len;
        tmp.value += occ[7];
        ++tmp.cntS;

        if(prev == 3){
            if(rep < maxr - 1){
                creaCollanaR(occ, sol, tmp, pos+1, maxr, 3, rep+1, perf);
            }
        }
        else{
            creaCollanaR(occ, sol, tmp, pos+1, maxr, 3, 0, perf);
        }

        --tmp.cntS;
        tmp.value -= occ[7];
        --tmp.len;
        ++occ[3];

        if(*perf)
            return;
    }

    // Il valore deve essere migliore e deve valere sempre zaffiri <= smeraldi.
    if(tmp.value > sol->value && tmp.cntZ <= tmp.cntS){
        sol->len = pos;
        sol->value = tmp.value;
        memcpy(sol->data, tmp.data, tmp.len * sizeof(int));
    }

    return;
}

// Wrapper di creaCollanaR.
Vector creaCollana(int *occ, int maxr){
    int perfection = 0, sum = occ[0] + occ[1] + occ[2] + occ[3];

    Vector tmp, sol;
    tmp.len = sol.len = tmp.value = sol.value = tmp.cntZ = tmp.cntS = 0;
    tmp.data = (int*) malloc(sum * sizeof(int));
    sol.data = (int*) malloc(sum * sizeof(int));

    creaCollanaR(occ, &sol, tmp, 0, maxr, -1, 0, &perfection);

    free(tmp.data);
    return sol; // sol.data verra' liberata dal chiamante.
}

// Stampa a schermo la collana sostituendo i numeri
// con l'iniziale della pietra.
// Se la collana e' vuota stampa lunghezza 0 e va a capo.
void printCollana(Vector v){
    int i;
    printf("%d: ", v.len);
    for(i = 0; i < v.len; ++i){
        switch(v.data[i]){
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
    printf(", Value: %d\n", v.value);
}

int main(int argc, char *argv[]){
    FILE *fp;
    char nome_file[30];
    int i, j, nr, occ[8], maxrep;
    Vector sol;

    printf("Inserire nome file: ");
    scanf("%s", nome_file);
    fp = fopen(nome_file, "r");
    if(fp == NULL)
        exit(EXIT_FAILURE);

    fscanf(fp, "%d", &nr);
    for(i = 0; i < nr; ++i){
        fscanf(fp, "%d %d %d %d %d %d %d %d %d", &occ[0], &occ[1], &occ[2], &occ[3], &occ[4], &occ[5], &occ[6], &occ[7], &maxrep);

        sol = creaCollana(occ, maxrep);

        printCollana(sol); // Lunghezza: collana ottimale, valore

        // Output come nel file dei risultati
        /*
        printf("TEST #%d\n", i+1);
        printf("zaffiro = %d [%d], ", occ[0], occ[4]);
        printf("rubino = %d [%d], ", occ[1], occ[5]);
        printf("topazio = %d [%d], ", occ[2], occ[6]);
        printf("smeraldo = %d [%d], ", occ[3], occ[7]);
        printf("TOT = %d ", occ[0] + occ[1] + occ[2] + occ[3]);
        printf("{max_rip = %d}\n", maxrep);
        printf("Soluzione ottima di valore %d usando %d gemma/e\n", sol.value, sol.len);
        printf("Composizione collana: ");
        for(j = 0; j < sol.len; ++j){
            switch(sol.data[j]){
            case 0:
                printf("z");
                break;
            case 1:
                printf("r");
                break;
            case 2:
                printf("t");
                break;
            case 3:
                printf("s");
                break;

            default:
                exit(EXIT_FAILURE);
                break;
            }
        }
        printf("\n");
        */
    }
    fclose(fp);

    free(sol.data);

    return 0;
}
