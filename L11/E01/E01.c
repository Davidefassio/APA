#include <stdlib.h>
#include <stdio.h>

#define MAXL 100
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
}Elemento;

typedef struct{
    int dd;
    int dp;
    // TODO
}Constraints;

void generaDiagonale(Elemento*, int, int, int[NELE], int);
void stampaDiagonale(Elemento*, int[NELE], int);
void generaProgramma(Elemento*, int, int);

int main(int argc, char *argv[]){
    Elemento *elemArray;
    
    int nr, i, DD, DP;
    
    FILE *fp = fopen("elementi.txt", "r");
    if(fp == NULL) exit(EXIT_FAILURE);
    
    fscanf(fp, "%d", &nr);
    
    elemArray = (Elemento*) malloc(nr * sizeof(Elemento));
    if(elemArray == NULL) exit(EXIT_FAILURE);
    
    for(i = 0; i < nr; ++i)
        fscanf(fp, "%s %d %d %d %d %d %f %d", elemArray[i].nome, &elemArray[i].tipo, &elemArray[i].dir_in, &elemArray[i].dir_out, &elemArray[i].first, &elemArray[i].last, &elemArray[i].val, &elemArray[i].diff);
    fclose(fp);
    
    printf("Difficolta massima diagonale: ");
    scanf("%d", &DD);
    printf("Difficolta massima totale: ");
    scanf("%d", &DP);
    
    generaProgramma(elemArray, DD, DP);
    
    return 0;
}

void generaDiagonale(Elemento *elem, int dd, int dp, int sol[NELE], int index){
    
}

void stampaDiagonale(Elemento *elem, int sol[NELE], int index){
    int i, j;
    float sum = 0.0f;
    
    for(i = 0; i < NELE; ++i){
        if(sol[i] == -1) break;
        sum += elem[sol[i]].val;
    }
    j = i;
    
    printf("DIAG #%d > %f", index, sum);
    if(index == 3 && elem[sol[i-1]].val >= BONUS)
        printf(" * 1.5 (BONUS)");
    printf("\n");
    
    for(i = 0; i < j; ++i)
        printf("%s ", elem[sol[i]].nome);
    printf("\n");
}

void generaProgramma(Elemento *elem, int dd, int dp){
    
}
