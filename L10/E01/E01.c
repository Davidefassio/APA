#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

// Struttura delle attività
// Inizio, fine, durata
typedef struct{
    int sta, fin, dur;
}Att;

void attSel(Att*, int, int*);
int cmp_att(const void*, const void*);
int compatible(Att, Att);
void printSeq(Att*, int*, int, int);

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
    // Ordino per ordine crescente dei tempi di fine il vettore delle attivita
    qsort(att, n, sizeof(Att), cmp_att);
    
    // Dichiaro le variabili
    int i, j, max, imax, lmax = INT_MIN, limax = -1, flag;
    int *len = (int*) malloc(n * sizeof(int));

    // Algoritmo
    len[0] = att[0].dur;
    sol[0] = -1;
    
    for(i = 1; i < n; ++i){
        flag = 1;
        max = INT_MIN;
        imax = -1;
        
        // Compatibilita indietro e ricerca della sequenza ottimale
        for(j = i-1; j >= 0; --j){
            if(compatible(att[i], att[j]) && len[j] + att[i].dur > max){
                flag = 0;
                max = len[j] + att[i].dur;
                imax = j;
            }
        }
        
        // Trovata compatibilita o meno
        if(flag){
            len[i] = att[i].dur;
            sol[i] = -1;
        }
        else{
            len[i] = max + att[i].dur;
            sol[i] = imax;
        }
        
        // Aggiornamento della sequenza massima
        if(len[i] > lmax){
            lmax = len[i];
            limax = i;
        }
    }
    
    // Stampa
    printf("Durata massima: %d\n", lmax);
    printSeq(att, sol, n, limax);
    
    // Free
    free(len);
}

void printSeq(Att *att, int *sol, int n, int index){
    if(index == -1) return;
    printSeq(att, sol, n, sol[index]);
    printf("(%d, %d)\n", att[index].sta, att[index].fin);
    return;
}

// Ordine crescente sul tempo finale delle attivita
int cmp_att(const void *p1, const void *p2){
    int t1 = (*(const Att*)p1).sta;
    int t2 = (*(const Att*)p2).sta;
    return (t1 > t2) - (t1 < t2);
}

int compatible(Att a1, Att a2){
    if(a1.sta < a2.fin && a1.fin > a2.sta)
        return 0; // Non compatibili
    return 1; // Compatibili
}
