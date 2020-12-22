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
    float cost;       // Costo dell'elemento per l'algoritmo greedy
}Elemento;

typedef struct{
    Elemento *data;
    int len;
}elemArray;

typedef struct{
    int dd[NDIA];       // Difficolta massima per diagonale
    int dp;             // Difficolta massima del programma
    int acrxdiag[NDIA]; // Almeno un elemento acrobatico per diagonale
    int fbacro[2];      // Almeno un elemento acrobatico frontale e di spalle nel programma
}Constr;


// Variabili globali
int glob_sol[NDIA][NELE]; // Soluzione ottimale.
int glob_tmp[NDIA][NELE]; // Soluzione currente.
float maxval = -1.0f;     // Valore della soluzione ottimale.
float tmpval = 0.0f;     // Valore della soluzione corrente.


float calcCosto(Elemento);
void stampaSol(elemArray);
void generaProgramma(elemArray, int, int);

int main(int argc, char *argv[]){
    elemArray elem;
    
    int i, DD, DP;
    
    FILE *fp = fopen("elementi.txt", "r");
    if(fp == NULL) exit(EXIT_FAILURE);
    
    fscanf(fp, "%d", &elem.len);
    
    elem.data = (Elemento*) malloc(elem.len * sizeof(Elemento));
    if(elem.data == NULL) exit(EXIT_FAILURE);
    
    for(i = 0; i < elem.len; ++i){
        fscanf(fp, "%s %d %d %d %d %d %f %d", elem.data[i].nome, &elem.data[i].tipo, &elem.data[i].dir_in, &elem.data[i].dir_out, &elem.data[i].first, &elem.data[i].last, &elem.data[i].val, &elem.data[i].diff);
        // printf("%s %d %d %d %d %d %f %d\n", elem.data[i].nome, elem.data[i].tipo, elem.data[i].dir_in, elem.data[i].dir_out, elem.data[i].first, elem.data[i].last, elem.data[i].val, elem.data[i].diff);
        
        elem.data[i].cost = calcCosto(elem.data[i]);
    }
    fclose(fp);
    
    printf("Difficolta massima diagonale: ");
    scanf("%d", &DD);
    printf("Difficolta massima totale: ");
    scanf("%d", &DP);
    
    generaProgramma(elem, DD, DP);
    
    return 0;
}

// Da migliorare
float calcCosto(Elemento elem){
    return (elem.val / elem.diff) + ((elem.diff >= BONUS) ? 1 : 0) + ((elem.tipo > 0) ? 1 : 0);
}


//              ### Roadmap algoritmo greedy ### 
// Inserisco l'ultimo elemento in modo da ottenere il bonus, se possibile.
// In parallelo da basso verso l'alto inserisco gli elementi.
// Do un bonus al punteggio degli elementi che hanno dir_out 
//      di spalle per invogliare il fbacro.
// Do un bonus al concatenare due acro per avere il dacro.
// Piu inserisco elementi piu alzo i due bonus precedenti.
// Importante quindi ricalcolare e riordinare tutti gli elementi ancora prendibili
//      ogni volta che se ne aggiunge uno.
