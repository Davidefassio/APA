#include <stdlib.h>
#include <stdio.h>

#define MAXL 100
#define NDIA 3
#define NELE 5
#define BONUS 8.0f

#define DBG 1

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


float calcValSolTmp(elemArray);
void addElemento(elemArray, Constr, int, int);
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
    }
    fclose(fp);
    
    printf("Difficolta massima diagonale: ");
    scanf("%d", &DD);
    printf("Difficolta massima totale: ");
    scanf("%d", &DP);
    
    generaProgramma(elem, DD, DP);
    
    return 0;
}

float calcValSolTmp(elemArray arr){
    float sum[NDIA] = {0};
    int i, j, l = 0;
    for(i = 0; i < NDIA; ++i){
        for(j = 0; j < NELE; ++j){
            if(glob_tmp[i][j] == -1) break;
            sum[i] += arr.data[glob_tmp[i][j]].val;
        }
        l = j-1;
    }
    return sum[0] + sum[1] + sum[2] * ((arr.data[glob_tmp[2][l]].diff >= BONUS) ? 1.5 : 1);
}

void addElemento(elemArray arr, Constr c, int index_diag, int index_elem){
    int i, j, flag = 0;

    /*printf("Diag: %d, Elem: %d\n", index_diag, index_elem);
    for(i = 0; i < NDIA; ++i){
        for(j = 0; j < NELE; ++j){
            printf("%d ", glob_tmp[i][j]);
        }
        printf("\n");
    }
    printf("\n");*/

    if(index_diag >= NDIA){ // Stop
        // Controllo ammissibilita (c.dacro e c.fbacro)
        if(c.fbacro[0] == 0 || c.fbacro[1] == 0)
            return;
        
        for(i = 0; i < NDIA; ++i){
            flag = 0;
            for(j = 0; j < NELE; ++j){
                if(arr.data[glob_tmp[i][j]].tipo > 0){
                    if(flag == 0){
                        flag = 1;
                    }
                    else{
                        // Trovata la doppia acrobazia
                        tmpval = calcValSolTmp(arr);
                        if(tmpval > maxval){
                            maxval = tmpval;
                            for(i = 0; i < NDIA; ++i)
                                for(j = 0; j < NELE; ++j)
                                    glob_sol[i][j] = glob_tmp[i][j];
                            
                            printf("%f\n", tmpval);
                            stampaSol(arr);
                            printf("\n");
                        }
                        return;
                    }
                }
                else{
                    flag = 0;
                }
            }
        }
    }
    
    // Metti tutti gli altri elementi
    // Sia in questa diagonale che ad iniziare la prossima
    // Se sono al 5 elemento metto solo nella prossima
    // Se non ho rispettato i constr di questa diagonale non vado alla prossima.
    // Metto solo elementi legali.
    
    for(i = 0; i < arr.len && index_elem < NELE; ++i){
        if(index_elem == 0 && arr.data[i].first == 1)
            continue;
        
        // Aggiungo alla diagonale se posso
        if((index_elem == 0 && arr.data[i].dir_in == 1) || (index_elem > 0 && ((!arr.data[glob_tmp[index_diag][index_elem-1]].dir_out ^ !arr.data[i].dir_in) == 0))){
            // Aggiorno constraints e glob_tmp
            c.dd[index_diag] -= arr.data[i].diff;
            c.dp -= arr.data[i].diff;
            c.acrxdiag[index_diag] += arr.data[i].tipo;
            c.fbacro[0] += (arr.data[i].tipo == 2);
            c.fbacro[1] += (arr.data[i].tipo == 1);
            tmpval += arr.data[i].val;
            glob_tmp[index_diag][index_elem] = i;
            
            // Ricorro
            if(c.dd[index_diag] >= 0 && c.dp >= 0){
                if(arr.data[i].last == 0)
                    addElemento(arr, c, index_diag, index_elem+1);
                else
                    addElemento(arr, c, index_diag+1, 0);
            }
            
            // Backtrack
            c.dd[index_diag] += arr.data[i].diff;
            c.dp += arr.data[i].diff;
            c.acrxdiag[index_diag] -= arr.data[i].tipo;
            c.fbacro[0] -= (arr.data[i].tipo == 2);
            c.fbacro[1] -= (arr.data[i].tipo == 1);
            tmpval -= arr.data[i].val;
            glob_tmp[index_diag][index_elem] = -1;
        }
    }
    // Se no passo alla prossima
    if(c.acrxdiag[index_diag] > 0){
        addElemento(arr, c, index_diag+1, 0);
    }
    return;
}

void stampaSol(elemArray arr){
    int i, j, l = 0;
    float sum[NDIA] = {0};
    
    for(i = 0; i < NDIA; ++i){
        for(j = 0; j < NELE; ++j){
            printf("%d ", glob_sol[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    
    for(i = 0; i < NDIA; ++i){
        for(j = 0; j < NELE; ++j){
            if(glob_sol[i][j] == -1) break;
            sum[i] += arr.data[glob_sol[i][j]].val;
        }
        l = j - 1;
    }
    
    printf("TOT = %f\n", maxval);
    
    for(i = 0; i < NDIA; ++i){
        printf("DIAG #%d > %f", i+1, sum[i]);
        
        if(i == 2 && arr.data[glob_sol[i][l]].diff >= BONUS)
            printf(" * 1.5 (BONUS)");
        printf("\n");
        
        for(j = 0; j < NELE; ++j){
            if(glob_sol[i][j] == -1) break;
            printf("%s ", arr.data[glob_sol[i][j]].nome);
        }
        printf("\n");
    }
}

void generaProgramma(elemArray arr, int dd, int dp){
    Constr c = {{dd, dd, dd}, dp, {0, 0, 0}, {0, 0}};
    
    int i, j;
    for(i = 0; i < NDIA; ++i)
        for(j = 0; j < NELE; ++j)
            glob_tmp[i][j] = glob_sol[i][j] = -1;
    
    addElemento(arr, c, 0, 0);
    
    stampaSol(arr);
}
