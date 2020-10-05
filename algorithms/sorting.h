#ifndef ALGS_H
#define ALGS_H

#include <stdlib.h>
#include <limits.h>
#include <math.h>

void selection(int *v, int l){
    if(l < 2){ return; }
    if(v == NULL){ return ; }

    int i, j, min, imin, tmp;

    for(i = 0; i < l; ++i){
        min = INT_MAX;

        for(j = i; j < l; ++j){
            if(v[j] < min){
                min = v[j];
                imin = j;
            }
        }

        tmp = v[i];
        v[i] = v[imin];
        v[imin] = tmp;
    }
}

void insertion(int *v, int l){
    if(l < 2){ return; }
    if(v == NULL){ return ; }

    int i, j, tmp;

    for(i = 1; i < l; ++i) {
        tmp = v[i];
        for(j = i - 1; (j >= 0 && v[j] > tmp); --j){
            v[j + 1] = v[j];
        }

        if(j + 1 != i){
            v[j + 1] = tmp;
        }
    }
}

void shell(int *v, int l){
    if(l < 2){ return; }
    if(v == NULL){ return ; }

    // Sequenza dei gap di Hibbard.
    // 2^k - 1, k = [1, ceil(log2(l-1)) - 2]
    int k = ceil(log2((double) l+1)) - 2;

    int i, j, nc, nr, cm, *ins;

    for(; k > 1; --k){ // Ciclo i gap
        nc = pow(2, k) - 1; // Numero colonne
        nr = ceil(l / (double) nc); // Numero righe
        cm = nr*nc - l; // Numero di colonne con un elemento in meno

        ins = (int*) malloc(sizeof(int)*nr);

        for(i = 0; i < nc; ++i){
            // Copio la colonna nel vettore
            for(j = 0; j < nr && j*nc+i < l; ++j){
                ins[j] = v[j*nc+i];
            }

            // Ordino il vettore con l'insertion
            insertion(ins, (nc-i > cm) ? nr : nr-1);

            // Sostituisco il vettore ordinato
            for(j = 0; j < nr && j*nc+i < l; ++j){
                v[j*nc+i] = ins[j];
            }
        }
    }
    // Insertion sort finale (k == 1)
    insertion(v, l);
}

#endif /*ALGS_H */
