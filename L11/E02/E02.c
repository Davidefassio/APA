#include <stdlib.h>
#include <stdio.h>

#define MAXL 100
#define NDIA 3
#define NELE 5
#define BONUS 8.0f

typedef struct{
    char nome[MAXL];  // Nome dell'elemento
    int tipo;         // Tipologia: 2 = avanti, 1 = indietro, 0 = di transizione
    int dir_in;       // Direzione di ingresso: 1 = frontale, 0 = di spalle
    int dir_out;      // Direzione di uscita: 1 = frontale, 0 = di spalle
    int first;        // 0 = puo essere il primo, 1 = deve essere preceduto da un altro
    int last;         // 1 = deve essere l'ultimo, 0 = puo non essere l'ultimo
    float val;        // Valore dell'elemento
    int diff;         // Difficolta dell'elemento
    float gain;       // Guadagno dell'elemento per l'algoritmo greedy
}Elemento;

typedef struct{
    Elemento *data;
    int len;
}elemArray;

typedef struct{
    int dd[NDIA];       // Difficolta massima per diagonale
    int dp;             // Difficolta massima del programma
    int acrxdiag[NDIA]; // Almeno un elemento acrobatico per diagonale
    int dacro;          // Almeno due acro di fila nel programma
    int fbacro[2];      // Almeno un elemento acrobatico frontale e di spalle nel programma
}Constr;


// Variabili globali
int sol[NDIA][NELE];  // Soluzione ottimale.
float solval = 0.0f;  // Valore della soluzione ottimale.
Constr cons;          // Constraint

// Prototipi
float calcCosto(elemArray, Elemento, int, int);
void stampaSol(elemArray);
void generaProgramma(elemArray);
int cmp_elem(const void*, const void*);

int main(int argc, char *argv[]){
    elemArray elems;
    
    int i, j, DD, DP;

    // Inizializzo sol a -1
    for(i = 0; i < NDIA; ++i)
        for(j = 0; j < NELE; ++j)
            sol[i][j] = -1;

    // Inserimento da tastiera delle difficolta massime
    printf("Difficolta massima diagonale: ");
    scanf("%d", &DD);
    printf("Difficolta massima totale: ");
    scanf("%d", &DP);

    // Genero constraints
    for(i = 0; i < NDIA; ++i){
        cons.dd[i] = DD;
        cons.acrxdiag[i] = 0;
    }
    cons.dp = DP;
    cons.fbacro[0] = cons.fbacro[1] = cons.dacro = 0;
    
    // Lettura file
    FILE *fp = fopen("elementi.txt", "r");
    if(fp == NULL) exit(EXIT_FAILURE);
    
    fscanf(fp, "%d", &elems.len);
    
    elems.data = (Elemento*) malloc(elems.len * sizeof(Elemento));
    if(elems.data == NULL) exit(EXIT_FAILURE);
    
    for(i = 0; i < elems.len; ++i){
        fscanf(fp, "%s %d %d %d %d %d %f %d", elems.data[i].nome, &elems.data[i].tipo, &elems.data[i].dir_in, &elems.data[i].dir_out, &elems.data[i].first, &elems.data[i].last, &elems.data[i].val, &elems.data[i].diff);
        elems.data[i].gain = calcCosto(elems, elems.data[i], 0, 0);
        
        // DEBUG
        // printf("%s %d %d %d %d %d %f %d\n", elems.data[i].nome, elems.data[i].tipo, elems.data[i].dir_in, elems.data[i].dir_out, elems.data[i].first, elems.data[i].last, elems.data[i].val, elems.data[i].diff);
    }
    fclose(fp); /* elementi.txt */
    
    // Genera e stampa il programma
    generaProgramma(elems);
    
    return 0;
}

// Da modificare i gain.
float calcCosto(elemArray elems, Elemento elem, int diag, int ind){
    float gain = 0.0f;
    
    gain += (elem.val / elem.diff); // Guadagno specifico

    if(cons.acrxdiag[diag] == 0 && elem.tipo > 0) 
        gain += 1;  // Primo elemento acrobatico della diagonale
    
    if(cons.fbacro[1] == 0 && elem.dir_out == 0)
        gain += 2 + ind*ind;  // Elemento con uscita di spalle 
    
    if(cons.dacro == 0 && ind > 0 && elems.data[sol[diag][ind-1]].tipo > 0 && elem.tipo > 0)
        gain += 3 + ind*ind;  // Doppia acro

    return gain;
}

void generaProgramma(elemArray elems){
    int i, j, k;

    qsort(elems.data, elems.len, sizeof(Elemento), cmp_elem);

    for(j = 0; j < NELE; ++j){
        for(i = 0; i < NDIA; ++i){

        }
    }
}

// Ordine decrescente sui gain
int cmp_elem(const void *a, const void *b){
    return (*(Elemento*)b).gain - (*(Elemento*)a).gain;
}


//              ### Roadmap algoritmo greedy ### 
// X Guadagno = val / difficolta.
// In parallelo dall'alto verso il basso inserisco gli elementi.
// X Do un bonus al primo acro di una diag.
// X Do un bonus al punteggio degli elementi che hanno dir_out 
//      di spalle per invogliare il fbacro. (pesante)
// X Do un bonus al concatenare due acro per avere il dacro.
// X Piu inserisco elementi piu alzo i due bonus precedenti.
// X Smetto di dare i bonus se ho soddisfatto il constraint.
// Importante quindi ricalcolare e riordinare tutti gli elementi ancora prendibili
//      ogni volta che se ne aggiunge uno.

/*

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXL 100
#define NDIA 3
#define NELE 5
#define BONUS 8.0f

typedef struct{
    char nome[MAXL];  // Nome dell'elemento
    int tipo;         // Tipologia: 2 = avanti, 1 = indietro, 0 = di transizione
    int dir_in;       // Direzione di ingresso: 1 = frontale, 0 = di spalle
    int dir_out;      // Direzione di uscita: 1 = frontale, 0 = di spalle
    int first;        // 0 = puo essere il primo, 1 = deve essere preceduto da un altro
    int last;         // 1 = deve essere l'ultimo, 0 = puo non essere l'ultimo
    float val;        // Valore dell'elemento
    int diff;         // Difficolta dell'elemento
    float gain;       // Guadagno dell'elemento per l'algoritmo greedy
}Elemento;

typedef struct{
    Elemento *data;
    int len;
}elemArray;

typedef struct{
    int dd[NDIA];       // Difficolta massima per diagonale
    int dp;             // Difficolta massima del programma
    int acrxdiag[NDIA]; // Almeno un elemento acrobatico per diagonale
    int dacro;          // Almeno due acro di fila nel programma
    int fbacro[2];      // Almeno un elemento acrobatico frontale e di spalle nel programma
}Constr;

// Variabili globali
int sol[NDIA][NELE];  // Soluzione ottimale.
float solval = 0.0f;  // Valore della soluzione ottimale.
Constr cons;          // Constraint

// Prototipi
float calcCosto(elemArray, Elemento, int, int);
void stampaSol(elemArray);
void generaProgramma(elemArray);
int cmp_elem(const void*, const void*);
int getIndex(elemArray, Elemento);

int main(int argc, char *argv[]){
    elemArray elems;
    
    int i, j, DD, DP;

    // Inserimento da tastiera delle difficolta massime
    printf("Difficolta massima diagonale: ");
    scanf("%d", &DD);
    printf("Difficolta massima totale: ");
    scanf("%d", &DP);

    // Genero constraints
    for(i = 0; i < NDIA; ++i){
        cons.dd[i] = DD;
        cons.acrxdiag[i] = 0;
    }
    cons.dp = DP;
    cons.fbacro[0] = cons.fbacro[1] = cons.dacro = 0;
    
    // Lettura file
    FILE *fp = fopen("elementi.txt", "r");
    if(fp == NULL) exit(EXIT_FAILURE);
    
    fscanf(fp, "%d", &elems.len);
    
    elems.data = (Elemento*) malloc(elems.len * sizeof(Elemento));
    if(elems.data == NULL) exit(EXIT_FAILURE);
    
    for(i = 0; i < elems.len; ++i){
        fscanf(fp, "%s %d %d %d %d %d %f %d", elems.data[i].nome, &elems.data[i].tipo, &elems.data[i].dir_in, &elems.data[i].dir_out, &elems.data[i].first, &elems.data[i].last, &elems.data[i].val, &elems.data[i].diff);
        elems.data[i].gain = calcCosto(elems, elems.data[i], 0, 0);
        
        // DEBUG
        // printf("%s %d %d %d %d %d %f %d\n", elems.data[i].nome, elems.data[i].tipo, elems.data[i].dir_in, elems.data[i].dir_out, elems.data[i].first, elems.data[i].last, elems.data[i].val, elems.data[i].diff);
    }
    fclose(fp); // elementi.txt
    
    // Genera e stampa il programma
    generaProgramma(elems);
    
    return 0;
}

// Da modificare i gain.
float calcCosto(elemArray elems, Elemento elem, int diag, int ind){
    float gain = 0.0f;
    
    gain += (elem.val / elem.diff); // Guadagno specifico

    if(cons.acrxdiag[diag] == 0 && elem.tipo > 0) 
        gain += 1 + ind;  // Primo elemento acrobatico della diagonale
    
    if(cons.fbacro[1] == 0 && elem.dir_out == 0)
        gain += 2 + ind*ind;  // Elemento con uscita di spalle 
    
    if(cons.dacro == 0 && ind > 0 && elems.data[sol[diag][ind-1]].tipo > 0 && elem.tipo > 0)
        gain += 3 + ind*ind;  // Doppia acro

    return gain;
}

void generaProgramma(elemArray elems){
    int i, j, k;

    // Copio il vettore di elementi in tmp per poterlo riordinare
    Elemento *tmp = NULL;
    memcpy(tmp, elems.data, sizeof(Elemento) * elems.len);

    // Inizializzo sol a -1
    for(i = 0; i < NDIA; ++i)
        for(j = 0; j < NELE; ++j)
            sol[i][j] = -1;

    // Ordino gli elementi per gain
    for(k = 0; k < elems.len; ++k)
        elems.data[k].gain = calcCosto(elems, elems.data[k], 0, 0);
    qsort(tmp, elems.len, sizeof(Elemento), cmp_elem);

    for(j = 0; j < NELE; ++j){
        for(i = 0; i < NDIA; ++i){
            for(k = 0; k < elems.len; ++k){
                if(j == 0){ // Primo elemento della diagonale
                    if(tmp[k].dir_in == 1 && cons.dd[i] - tmp[k].diff >= 0){ // Inserisco
                        sol[i][j] = getIndex(elems, tmp[k]);

                        // Constraints
                        cons.dd[i] -= tmp[k].diff;
                        cons.dp -= tmp[k].diff;
                        cons.acrxdiag[i] += tmp[k].tipo;
                        cons.fbacro[0] += (tmp[k].tipo == 2) ? 1 : 0;
                        cons.fbacro[1] += (tmp[k].tipo == 1) ? 1 : 0;

                        break;
                    }
                }
                else{ // Tutti gli altri
                    if(elems.data[sol[i][j-1]].dir_out == tmp[k].dir_in && cons.dd[i] - tmp[k].diff >= 0){ // Inserisco
                        sol[i][j] = getIndex(elems, tmp[k]);

                        // Constraints
                        cons.dd[i] -= tmp[k].diff;
                        cons.dp -= tmp[k].diff;
                        cons.acrxdiag[i] += tmp[k].tipo;
                        cons.fbacro[0] += (tmp[k].tipo == 2) ? 1 : 0;
                        cons.fbacro[1] += (tmp[k].tipo == 1) ? 1 : 0;
                        cons.dacro += (elems.data[sol[i][j]].tipo > 0 && tmp[k].tipo > 0) ? 1 : 0;

                        break;
                    }
                }
            }
            for(k = 0; k < elems.len; ++k)
                elems.data[k].gain = calcCosto(elems, elems.data[k], i, j);
            qsort(tmp, elems.len, sizeof(Elemento), cmp_elem);
        }
    }

    for(i = 0; i < NDIA; ++i){
        for(j = 0; j < NELE; ++j){
            printf("%s ", elems.data[sol[i][j]].nome);
        }
        printf("\n");
    }
    printf("\n");
}

// Ordine decrescente sui gain
int cmp_elem(const void *a, const void *b){
    return (*(Elemento*)b).gain - (*(Elemento*)a).gain;
}

int getIndex(elemArray elems, Elemento el){
    int i;
    for(i = 0; i < elems.len; ++i)
        if(strcmp(elems.data[i].nome, el.nome) == 0)
            return i;
    return -1;
}


//              ### Roadmap algoritmo greedy ### 
// X Guadagno = val / difficolta.
// X In parallelo dall'alto verso il basso inserisco gli elementi.
// X Do un bonus al primo acro di una diag.
// X Do un bonus al punteggio degli elementi che hanno dir_out 
//      di spalle per invogliare il fbacro. (pesante)
// X Do un bonus al concatenare due acro per avere il dacro.
// X Piu inserisco elementi piu alzo i due bonus precedenti.
// X Smetto di dare i bonus se ho soddisfatto il constraint.
// X Importante quindi ricalcolare e riordinare tutti gli elementi ancora prendibili
//      ogni volta che se ne aggiunge uno.

*/
