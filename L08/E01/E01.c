/**
Il programma sottostante e' stato fatto usando due strategie differenti.

In tutti e due i programmi si puo' scegliere se avere l'output come
i file dei risultati oppure con la stampa della sequenza.

Parte 1: (non commentata)
    E' la soluzione matematica del problema.
    Ho calcolato tutte le soluzioni ottimali
    sia quando si hanno tutte le pietre a disposizioni
    sia quando alcune non ne ho a disposizione.
    L'algoritmo ha complessita' O(1) per quanto riguarda
    la determinazione della lunghezza e O(n) per elencare
    una soluzione ottimale.

Perte 2: (commentata)
    E' la soluzione informatica/ricorsiva del problema.
    Si esegue senza errori ma visto il grande numero di possibili
    collane e' molto lento (>45 minuti per alcuni test in hard_test_set.txt).
    L'unico pruning effettuato e' se si trova la soluzione ottimale.
    Complessita': O(2^n), ogni pietra mi permette due scelte successive.
*/

#include <stdlib.h>
#include <stdio.h>

typedef struct{
    int *data;
    int len;
}Vector;

int min(int a, int b){
    return (a < b) ? a : b;
}

int max(int a, int b){
    return (a > b) ? a : b;
}

/**
Elenco di tutti i casi possibili (16).
Per ogni caso indico la lunghezza della collana e come ottenerla.

Nota Bene:
    - I tre puntini indicano che la sequenza precedente si ripete
      fino all'esurimento delle pietre coinvolte.
    - Quando si indica ad esempio Z == 0 si presuppone che
      tutt gli altri siano diversi da zero.

1) TUTTI DIVERSI DA ZERO:
    - se R == T ==> len = Z + R + T + S, coll = ZZ...ZZ|RTRT..RTR|SS...SS|T
    - se R > T  ==> len = Z + 2T + S + 1, coll = ZZ...ZZ|RT...TR|SS...SS
    - se T > R  ==> len = Z + 2R + S + 1, coll = SS...SS|TR...RT|ZZ...ZZ

2) Z == 0
    - se R == T ==> len = R + T + S, coll = RT..RTR|SS...SS|T
    - se R > T  ==> len = 2T + S + 1, coll = RT...RTR|SS...SS
    - se T > R  ==> len = 2R + S + 1, coll = SS...SS|TR...TRT

3) R == 0
    len = Z + S + 1, coll = SS...SS|T|ZZ...ZZ

4) T == 0
    len = Z + S + 1, coll = ZZ...ZZ|R|SS...SS

5) S == 0
    - se R == T ==> len = Z + R + T, coll = T|ZZ...ZZ|RT...RTR
    - se R > T  ==> len = Z + 2T + 1, coll = ZZ...ZZ|RT...RTR
    - se T > R  ==> len = Z + 2R + 1, coll = TR...TRT|ZZ...ZZ

6) Z == R == 0
    len = S + 1, coll = SS...SS|T

7) Z == T == 0
    len = S + 1, coll = R|SS...SS

8) Z == S == 0
    - se R == T ==> len = R + T, coll = RT...RT
    - se R > T  ==> len = 2T + 1, coll = RT...RTR
    - se T > R  ==> len = 2R + 1, coll = TR...TRT

9) R == T == 0
    - se Z > S ==> len = Z, coll = ZZ...ZZ
    - se S > Z ==> len = S, coll = SS...SS
    - se Z == S qualunque dei due casi precedenti

10) R == S == 0
    len = Z + 1, coll = T|ZZ...ZZ

11) T == S == 0
    len = Z + 1, coll = ZZ...ZZ|R

12) R == T == S == 0
    len = Z, coll = ZZ...ZZ

13) T == S == Z == 0
    len = 1, coll = R

14) S == Z == R == 0
    len = 1, coll = T

15) Z == R == T == 0
    len = S, coll = SS...SS

16) TUTTI UGUALI A ZERO
    len = 0, coll = NULL
*/
Vector creaCollana(int *occ){
    int i;
    Vector sol = {NULL, 0};

    // Tutti diversi da zero
    if(occ[0] != 0 && occ[1] != 0 && occ[2] != 0 && occ[3] != 0){
        sol.len = occ[0] + occ[3];
        if(occ[1] == occ[2]){
            sol.len += (occ[1] + occ[2]);

            sol.data = (int*) malloc(sol.len * sizeof(int));
            for(i = 0; i < occ[0]; ++i)
                sol.data[i] = 0;
            for(; i < occ[0] + occ[1] + occ[2] - 1;){
                sol.data[i++] = 1;
                sol.data[i++] = 2;
            }
            sol.data[i++] = 1;
            for(; i < occ[0] + occ[1] + occ[2] + occ[3] - 1; ++i)
                sol.data[i] = 3;
            sol.data[i] = 2;
        }
        else{
            sol.len += (2 * min(occ[1], occ[2]) + 1);
            sol.data = (int*) malloc(sol.len * sizeof(int));

            if(occ[1] > occ[2]){
                for(i = 0; i < occ[0]; ++i)
                    sol.data[i] = 0;
                for(; i < occ[0] + occ[2] + occ[2];){
                    sol.data[i++] = 1;
                    sol.data[i++] = 2;
                }
                sol.data[i++] = 1;
                for(; i < occ[0] + occ[2] + occ[2] + occ[3] + 1; ++i)
                    sol.data[i] = 3;
            }
            else{
                for(i = 0; i < occ[3]; ++i)
                    sol.data[i] = 3;
                for(; i < occ[3] + occ[1] + occ[1];){
                    sol.data[i++] = 2;
                    sol.data[i++] = 1;
                }
                sol.data[i++] = 2;
                for(; i < occ[3] + occ[1] + occ[1] + occ[0] + 1; ++i)
                    sol.data[i] = 0;
            }
        }
    }
    // Tre diversi da zero (4 casi)
    else if(occ[1] != 0 && occ[2] != 0 && occ[3] != 0){
        sol.len = occ[3];
        if(occ[1] == occ[2]){
            sol.len += (occ[1] + occ[2]);
            sol.data = (int*) malloc(sol.len * sizeof(int));
            for(i = 0; i < occ[1] + occ[2] - 1;){
                sol.data[i++] = 1;
                sol.data[i++] = 2;
            }
            for(; i < sol.len -1; ++i)
                sol.data[i] = 3;
            sol.data[i] = 2;
        }
        else{
            sol.len += (2 * min(occ[1], occ[2]) + 1);
            sol.data = (int*) malloc(sol.len * sizeof(int));
            if(occ[1] > occ[2]){
                for(i = 0; i < occ[2] + occ[2];){
                    sol.data[i++] = 1;
                    sol.data[i++] = 2;
                }
                sol.data[i++] = 1;
                for(; i < sol.len; ++i)
                    sol.data[i] = 3;
            }
            else{
                for(i = 0; i < occ[3]; ++i)
                    sol.data[i] = 3;
                for(; i < sol.len - 1;){
                    sol.data[i++] = 2;
                    sol.data[i++] = 1;
                }
                sol.data[i] = 2;
            }
        }
    }
    else if(occ[0] != 0 && occ[2] != 0 && occ[3] != 0){
        sol.len = occ[0] + occ[3] + 1;
        sol.data = (int*) malloc(sol.len * sizeof(int));
        for(i = 0; i < occ[3]; ++i)
            sol.data[i] = 3;
        sol.data[i++] = 2;
        for(; i < occ[3] + occ[0] + 1; ++i)
            sol.data[i] = 0;
    }
    else if(occ[0] != 0 && occ[1] != 0 && occ[3] != 0){
        sol.len = occ[0] + occ[3] + 1;
        sol.data = (int*) malloc(sol.len * sizeof(int));
        for(i = 0; i < occ[0]; ++i)
            sol.data[i] = 0;
        sol.data[i++] = 1;
        for(; i < occ[0] + occ[3] + 1; ++i)
            sol.data[i] = 3;
    }
    else if(occ[0] != 0 && occ[1] != 0 && occ[2] != 0){
        sol.len = occ[1];
        if(occ[1] == occ[2]){
            sol.len += (occ[1] + occ[2]);
            sol.data = (int*) malloc(sol.len * sizeof(int));
            sol.data[0] = 2;
            for(i = 1; i < occ[0]; ++i)
                sol.data[i] = 0;
            for(; i < sol.len -1;){
                sol.data[i++] = 1;
                sol.data[i++] = 2;
            }
            sol.data[i] = 1;
        }
        else{
            sol.len += (2 * min(occ[1], occ[2]) + 1);
            sol.data = (int*) malloc(sol.len * sizeof(int));
            if(occ[1] > occ[2]){
                for(i = 0; i < occ[0]; ++i)
                    sol.data[i] = 0;
                for(; i < sol.len - 1; ++i){
                    sol.data[i++] = 1;
                    sol.data[i++] = 2;
                }
                sol.data[i] = 1;
            }
            else{
                for(i = 0; i < occ[i] + occ[i];){
                    sol.data[i++] = 2;
                    sol.data[i++] = 1;
                }
                sol.data[i++] = 2;
                for(; i < sol.len; ++i)
                    sol.data[i] = 0;
            }
        }
    }
    // Due diversi da zero (6 casi)
    else if(occ[2] != 0 && occ[3] != 0){
        sol.len = occ[3] + 1;
        sol.data = (int*) malloc(sol.len * sizeof(int));
        for(i = 0; i < occ[3]; ++i)
            sol.data[i] = 3;
        sol.data[i] = 2;
    }
    else if(occ[1] != 0 && occ[3] != 0){
        sol.len = occ[3] + 1;
        sol.data = (int*) malloc(sol.len * sizeof(int));
        sol.data[0] = 1;
        for(i = 1; i < occ[3]; ++i)
            sol.data[i] = 3;
    }
    else if(occ[1] != 0 && occ[2] != 0){
        if(occ[1] == occ[2]){
            sol.len = occ[1] + occ[2];
            sol.data = (int*) malloc(sol.len * sizeof(int));
            for(i = 0; i < sol.len;){
                sol.data[i++] = 1;
                sol.data[i++] = 2;
            }
        }
        else{
            sol.len = (2 * min(occ[1], occ[2]) + 1);
            sol.data = (int*) malloc(sol.len * sizeof(int));
            if(occ[1] > occ[2]){
                for(i = 0; i < sol.len - 1; ++i){
                    sol.data[i++] = 1;
                    sol.data[i++] = 2;
                }
                sol.data[i] = 1;
            }
            else{
                for(i = 0; i < sol.len - 1; ++i){
                    sol.data[i++] = 2;
                    sol.data[i++] = 1;
                }
                sol.data[i] = 2;
            }
        }
    }
    else if(occ[0] != 0 && occ[3] != 0){
        sol.len = max(occ[0], occ[3]);
        sol.data = (int*) malloc(sol.len * sizeof(int));
        if(occ[0] > occ[3]){
            for(i = 0; i < occ[0]; ++i)
                sol.data[i] = 0;
        }
        else{
            for(i = 0; i < occ[3]; ++i)
                sol.data[i] = 3;
        }
    }
    else if(occ[0] != 0 && occ[2] != 0){
        sol.len = occ[0] + 1;
        sol.data = (int*) malloc(sol.len * sizeof(int));
        sol.data[0] = 2;
        for(i = 1; i < occ[0]; ++i)
            sol.data[i] = 0;
    }
    else if(occ[0] != 0 && occ[1] != 0){
        sol.len = occ[0] + 1;
        sol.data = (int*) malloc(sol.len * sizeof(int));
        for(i = 0; i < occ[0]; ++i)
            sol.data[i] = 0;
        sol.data[i] = 1;
    }
    // Uno diverso da zero (4 casi)
    else if(occ[0] != 0){
        sol.len = occ[0];
        sol.data = (int*) malloc(sol.len * sizeof(int));
        for(i = 0; i < occ[0]; ++i)
            sol.data[i] = 0;
    }
    else if(occ[1] != 0){
        sol.len = 1;
        sol.data = (int*) malloc(sol.len * sizeof(int));
        sol.data[0] = 1;
    }
    else if(occ[2] != 0){
        sol.len = 1;
        sol.data = (int*) malloc(sol.len * sizeof(int));
        sol.data[0] = 2;
    }
    else if(occ[3] != 0){
        sol.len = occ[3];
        sol.data = (int*) malloc(sol.len * sizeof(int));
        for(i = 0; i < occ[3]; ++i)
            sol.data[i] = 3;
    }
    // Tutti uguali a zero (1 caso)
    else{
        sol.len = 0;
    }

    return sol;
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
    printf("\n");
}

int main(int argc, char *argv[]){
    FILE *fp;
    char nome_file[30];
    int i, nr, occ[4];
    Vector sol;

    printf("Inserire nome file: ");
    scanf("%s", nome_file);
    fp = fopen(nome_file, "r");
    if(fp == NULL)
        exit(EXIT_FAILURE);

    fscanf(fp, "%d", &nr);
    for(i = 0; i < nr; ++i){
        fscanf(fp, "%d %d %d %d", &occ[0], &occ[1], &occ[2], &occ[3]);

        sol = creaCollana(occ);

        printCollana(sol); // Lunghezza: collana ottimale

        // Output come nei file dei risultati
        // printf("TEST #%d\n", i+1);
        // printf("zaffiro = %d, ", occ[0]);
        // printf("rubino = %d, ", occ[1]);
        // printf("topazio = %d, ", occ[2]);
        // printf("smeraldo = %d, ", occ[3]);
        // printf("TOT = %d\n", occ[0] + occ[1] + occ[2] + occ[3]);
        // printf("Collana massima di lunghezza %d\n", sol.len);
    }
    fclose(fp);

    free(sol.data);

    return 0;
}



/* Risoluzione ricorsiva

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

        --tmp.len;
        ++occ.data[0];

        if(*perf)
            return;
    }
    if((pos == 0 || tmp.data[pos-1] % 2 == 0) && occ.data[1] > 0){ // Rubini
        --occ.data[1];
        tmp.data[pos] = 1;
        ++tmp.len;

        creaCollanaR(occ, sol, tmp, pos+1, perf);

        --tmp.len;
        ++occ.data[1];

        if(*perf)
            return;
    }
    if((pos == 0 || tmp.data[pos-1] % 2 != 0) && occ.data[2] > 0){ // Topazi
        --occ.data[2];
        tmp.data[pos] = 2;
        ++tmp.len;

        creaCollanaR(occ, sol, tmp, pos+1, perf);

        --tmp.len;
        ++occ.data[2];

        if(*perf)
            return;
    }
    if((pos == 0 || tmp.data[pos-1] % 2 != 0) && occ.data[3] > 0){ // Smeraldi
        --occ.data[3];
        tmp.data[pos] = 3;
        ++tmp.len;

        creaCollanaR(occ, sol, tmp, pos+1, perf);

        --tmp.len;
        ++occ.data[3];

        if(*perf)
            return;
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
    printf("\n");
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
    if(fp == NULL)
        exit(EXIT_FAILURE);

    fscanf(fp, "%d", &nr);
    for(i = 0; i < nr; ++i){
        fscanf(fp, "%d %d %d %d", &occ.data[0], &occ.data[1], &occ.data[2], &occ.data[3]);

        sol = creaCollana(occ);

        printCollana(sol); // Lunghezza: collana ottimale

        // Output come nei file dei risultati
        // printf("TEST #%d\n", i+1);
        // printf("zaffiro = %d, ", occ[0]);
        // printf("rubino = %d, ", occ[1]);
        // printf("topazio = %d, ", occ[2]);
        // printf("smeraldo = %d, ", occ[3]);
        // printf("TOT = %d\n", occ[0] + occ[1] + occ[2] + occ[3]);
        // printf("Collana massima di lunghezza %d\n", sol.len);
    }
    fclose(fp);

    free(occ.data);
    free(sol.data);

    return 0;
}

*/
