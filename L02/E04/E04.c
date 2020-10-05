#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>

void selection(int *v, int l){
    if(l < 2){ return; }
    if(v == NULL){ return ; }

    int i, j, min, imin, tmp;
    int nscambi = 0;

    printf("Selection sort\n");
    printf("Numero iterazioni esterne: %d\n", l);

    for(i = 0; i < l; ++i){
        min = INT_MAX;
        printf("%d ", l-i);

        for(j = i; j < l; ++j){
            if(v[j] < min){
                min = v[j];
                imin = j;
            }
        }

        if(i != imin){
            ++nscambi;
        }

        tmp = v[i];
        v[i] = v[imin];
        v[imin] = tmp;
    }
    printf("\nNumero iterazioni totali: %d\n", l*(l+1)/2);
    printf("Numero scambi: %d\n\n", nscambi);
}

void insertion(int *v, int l){
    if(l < 2){ return; }
    if(v == NULL){ return ; }

    int i, j, tmp;
    int nscambi = 0, itint, ittot = 0;

    printf("Insertion sort\n");
    printf("Numero iterazioni esterne: %d\n", l-1);

    for(i = 1; i < l; ++i) {
        tmp = v[i];
        itint = 0;
        for(j = i - 1; j >= 0 && v[j] > tmp; --j){
            ++itint; ++ittot; ++nscambi;
            v[j + 1] = v[j];
        }

        printf("%d ", itint);

        if(j + 1 != i){
            ++nscambi;
            v[j + 1] = tmp;
        }
    }

    printf("\nNumero iterazioni totali: %d\n", ittot);
    printf("Numero scambi: %d\n\n", nscambi);
}

void shell(int *v, int l){
    if(l < 2){ return; }
    if(v == NULL){ return ; }

    printf("Shell sort\n");

    // Sequenza dei gap di Hibbard.
    // 2^k - 1, k = [1, ceil(log2(l-1)) - 2]
    int k = ceil(log2((double) l+1)) - 2;

    int i, j, nc, nr, cm, m, n, tmp, *ins;
    int nscambi = 0, ittot = 0;

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
            for(m = 1; m < ((nc-i > cm) ? nr : nr-1); ++m) {
                tmp = ins[m];
                for(n = m - 1; (n >= 0 && ins[n] > tmp); --n){
                    ++ittot; ++nscambi;
                    ins[n + 1] = ins[n];
                }

                if(n + 1 != m){
                    ++nscambi;
                    ins[n + 1] = tmp;
                }
            }
            // Sostituisco il vettore ordinato
            for(j = 0; j < nr && j*nc+i < l; ++j){
                v[j*nc+i] = ins[j];
            }
        }
    }
    // Insertion sort finale (k == 1)
    for(m = 1; m < l; ++m) {
        tmp = v[m];
        for(n = m - 1; (n >= 0 && v[n] > tmp); --n){
            ++ittot; ++nscambi;
            v[n + 1] = v[n];
        }

        if(n + 1 != m){
            ++nscambi;
            v[n + 1] = tmp;
        }
    }

    printf("Numero iterazioni totali: %d\n", ittot);
    printf("Numero scambi: %d\n\n", nscambi);
}

int main(int argc, char* argv[]){
    char nome_file[20];
    int l, n, i, j, *v, *c;
    FILE *f;

    printf("Inserisci nome file: ");
    scanf("%s", nome_file);

    f = fopen(nome_file, "r");
    if(f == NULL){
        exit(EXIT_FAILURE);
    }

    fscanf(f, "%d", &n);

    for(i = 0; i < n; ++i){
        printf("########## %d ##########\n", i);

        fscanf(f, "%d", &l);
        v = (int*) malloc(sizeof(int)*l);
        c = (int*) malloc(sizeof(int)*l);

        for(j = 0; j < l; ++j){
            fscanf(f, "%d", &v[j]);
        }

        memcpy(c, v, l*sizeof(int));
        selection(c, l);

        memcpy(c, v, l*sizeof(int));
        insertion(c, l);

        memcpy(c, v, l*sizeof(int));
        shell(c, l);

        free(v);
        free(c);
    }
    fclose(f);

    return 0;
}

