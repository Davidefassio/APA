#include <stdlib.h>
#include <stdio.h>

// Sono messi in questo ordine per evitare sprechi di padding.
// Suppongo col1/val1 orizzontali e col2/val2 verticali.
typedef struct{
    int val1;
    int val2;
    char col1;
    char col2;
}Tile;

typedef struct{
    Tile *t; // Puntatore a Tile
    int rot; // 0 normale, 1 ruotata di 90 gradi
}Casa;

typedef struct{
    int rows;    // Righe
    int cols;    // Colonne
    Casa **data; // Contenuto della scacchiera
}Board;

void maximizeBoard(Board, Board, int*, Tile*, int*, int, int, int);
void printBoard(Board, int);

int main(int argc, char *argv[]){
    int i, j, nt, k, max = -1;

    Tile *vtile;
    int *mark;

    Board board, best;

    // Lettura file tiles.txt
    FILE *fp = fopen("tiles.txt", "r");
    if(fp == NULL) exit(EXIT_FAILURE);

    fscanf(fp, "%d\n", &nt); // Numero tiles
    vtile = (Tile*) malloc(nt * sizeof(Tile)); // Allocazione dinamica del vettore delle tiles
    mark = (int*) calloc(nt, sizeof(int));     // Allocazione dinamica del vettore dei mark azzerato

    for(i = 0; i < nt; ++i) // Acquisizione delle tiles
        fscanf(fp, "%c %d %c %d\n", &vtile[i].col1, &vtile[i].val1, &vtile[i].col2, &vtile[i].val2);

    fclose(fp); // Chiudi tiles.txt

    // Lettura file board.txt
    fp = fopen("board.txt", "r");
    if(fp == NULL) exit(EXIT_FAILURE);

    fscanf(fp, "%d %d", &board.rows, &board.cols);

    board.data = (Casa**) malloc(board.rows * sizeof(Casa*));

    // Allocazione di best
    best.rows = board.rows;
    best.cols = board.rows;
    best.data = (Casa**) malloc(board.rows * sizeof(Casa*));

    for(i = 0; i < board.rows; ++i){
        board.data[i] = (Casa*) malloc(board.cols * sizeof(Casa));
        best.data[i] = (Casa*) malloc(board.cols * sizeof(Casa));
        for(j = 0; j < board.cols; ++j){
            fscanf(fp, "%d/%d", &k, &board.data[i][j].rot);

            // Inizializzazione nulla di best
            best.data[i][j].t = NULL;
            best.data[i][j].rot = -1;

            // Se -1/-1 allora casella vuota.
            // Lascio -1 nella rot come indicatore.
            if(k == -1 && board.data[i][j].rot == -1){
                board.data[i][j].t = NULL;
            }
            else{
                board.data[i][j].t = vtile + k;
                mark[k] = 1;
            }

        }
    }

    fclose(fp); // Chiudi board.txt

    // Salva la soluzione ottima in best
    maximizeBoard(board, best, &max, vtile, mark, nt, 0, 0);

    printBoard(best, max);

    // Deallocazione
    for(i = 0; i < board.rows; ++i){
        free(board.data[i]);
        free(best.data[i]);
    }
    free(board.data);
    free(best.data);

    free(mark);
    free(vtile);

    return 0;
}

// Riempi la board massimizzandone il valore.
//
// Ogni volta che ricorro devo fare attenzione a non sforare sulla riga,
// incrementare le righe e azzerare le colonne.
void maximizeBoard(Board tmp, Board best, int *max, Tile *vtile, int *mark, int n, int r, int c){
    int i, j, sum, tsum, tr, tc;
    char c1, c2;

    // Condizione di terminazione.
    // Ho esaurito la scacchiera.
    if(r >= tmp.rows){
        // Calcolo il valore della board.
        // Faccio due giri: il primo row-major, il secondo col-major.
        sum = 0;
        for(i = 0; i < tmp.rows; ++i){
            tsum = (tmp.data[i][0].rot == 0) ? tmp.data[i][0].t->val1 : tmp.data[i][0].t->val2;
            c1 = (tmp.data[i][0].rot == 0) ? tmp.data[i][0].t->col1 : tmp.data[i][0].t->col2;
            for(j = 1; j < tmp.cols; ++j){ // Salto il primo
                c2 = (tmp.data[i][j].rot == 0) ? tmp.data[i][j].t->col1 : tmp.data[i][j].t->col2;

                if(c1 != c2){
                    tsum = 0;
                    break;
                }
                tsum += (tmp.data[i][j].rot == 0) ? tmp.data[i][j].t->val1 : tmp.data[i][j].t->val2;
            }
            sum += tsum;
        }

        for(j = 0; j < tmp.cols; ++j){
            tsum = (tmp.data[0][j].rot == 0) ? tmp.data[0][j].t->val2 : tmp.data[0][j].t->val1;
            c1 = (tmp.data[0][j].rot == 0) ? tmp.data[0][j].t->col2 : tmp.data[0][j].t->col1;
            for(i = 1; i < tmp.rows; ++i){ // Salto il primo
                c2 = (tmp.data[i][j].rot == 0) ? tmp.data[i][j].t->col2 : tmp.data[i][j].t->col1;

                if(c1 != c2){
                    tsum = 0;
                    break;
                }
                tsum += (tmp.data[i][j].rot == 0) ? tmp.data[i][j].t->val2 : tmp.data[i][j].t->val1;
            }
            sum += tsum;
        }

        // Se maggiore della best allora cambio best e max.
        if(sum > *max){
            *max = sum;

            for(i = 0; i < tmp.rows; ++i){
                for(j = 0; j < tmp.cols; ++j){
                    best.data[i][j].rot = tmp.data[i][j].rot;
                    best.data[i][j].t = tmp.data[i][j].t;
                }
            }
        }

        // Termino.
        return;
    }

    // Se la casella e' gia occupata ricorro a quella successiva e returno.
    if(tmp.data[r][c].rot != -1){
        if(c == tmp.cols-1){ tc = 0; tr = r+1; }
        else{ tc = c+1; tr = r;}

        maximizeBoard(tmp, best, max, vtile, mark, n, tr, tc);

        return;
    }

    // Se no ricorro su tutti i mark possibili.
    for(i = 0; i < n; ++i){
        if(mark[i] == 0){
            if(c == tmp.cols-1){ tc = 0; tr = r+1; }
            else{ tc = c+1; tr = r; }

            mark[i] = 1;

            tmp.data[r][c].t = vtile + i;

            tmp.data[r][c].rot = 0;
            maximizeBoard(tmp, best, max, vtile, mark, n, tr, tc);

            tmp.data[r][c].rot = 1;
            maximizeBoard(tmp, best, max, vtile, mark, n, tr, tc);

            tmp.data[r][c].rot = -1;
            mark[i] = 0;
        }
    }

    // Terminazione.
    return;
}

// Stampa board.
// I valori delle tiles devono essere nel range [0, 9].
// Se i valori superano la singola cifra verra visualizzato unn carattere errato,
// Secondo la tabella ascii: valore + 48. (Esempio: 11 -> ; ).
void printBoard(Board b, int val){
    int i, j;
    char *mat = (char*) malloc(9 * b.rows * b.cols * sizeof(char));

    printf("Valore scacchiera: %d\n", val);

    // Riempo la matrice con le informazioni sulle tiles.
    for(i = 0; i < b.rows; ++i){
        for(j = 0; j < b.cols; ++j){
            mat[3*j + (3*i+0)*3*b.cols + 0] = (char) 32;
            mat[3*j + (3*i+0)*3*b.cols + 2] = (char) 32;
            mat[3*j + (3*i+1)*3*b.cols + 1] = (char) 32;
            mat[3*j + (3*i+2)*3*b.cols + 0] = (char) 32;
            mat[3*j + (3*i+2)*3*b.cols + 2] = (char) 32;

            if(b.data[i][j].rot == -1){ // Casella vuota
                mat[3*j + (3*i+0)*3*b.cols + 1] = (char) 32;
                mat[3*j + (3*i+1)*3*b.cols + 0] = (char) 32;
                mat[3*j + (3*i+1)*3*b.cols + 2] = (char) 32;
                mat[3*j + (3*i+2)*3*b.cols + 1] = (char) 32;
            }
            else if(b.data[i][j].rot == 0){ // Casella normale
                mat[3*j + (3*i+0)*3*b.cols + 1] = b.data[i][j].t->col2;
                mat[3*j + (3*i+1)*3*b.cols + 0] = b.data[i][j].t->col1;
                mat[3*j + (3*i+1)*3*b.cols + 2] = (char) (b.data[i][j].t->val1 + 48);
                mat[3*j + (3*i+2)*3*b.cols + 1] = (char) (b.data[i][j].t->val2 + 48);
            }
            else if(b.data[i][j].rot == 1){ // Casella ruotata
                mat[3*j + (3*i+0)*3*b.cols + 1] = b.data[i][j].t->col1;
                mat[3*j + (3*i+1)*3*b.cols + 0] = b.data[i][j].t->col2;
                mat[3*j + (3*i+1)*3*b.cols + 2] = (char) (b.data[i][j].t->val2 + 48);
                mat[3*j + (3*i+2)*3*b.cols + 1] = (char) (b.data[i][j].t->val1 + 48);
            }
            else{
                exit(EXIT_FAILURE);
            }
        }
    }

    // Stampo la matrice e le linee verticali e orizzonatali.
    for(i = 0; i < 3*b.rows; ++i){
        if(i != 0 && i % 3 == 0){ // Intermezzo orizzontale
            for(j = 0; j < 8*b.cols - 2; ++j){
                if(j != 0 && (j+2) % 8 == 0)
                    printf("+");
                else
                    printf("-");
            }
            printf("\n");
        }

        for(j = 0; j < 3*b.cols; ++j){
            if(j != 0 && j % 3 == 0) // Intermezzo verticlae
                printf("| ");
            printf("%c ", mat[j + i*3*b.cols]);
        }
        printf("\n");
    }
    printf("\n");

    free(mat);
}
