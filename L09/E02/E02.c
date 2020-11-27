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

void printBoard(Board);

int main(int argc, char *argv[]){
    int i, j, nt, k;

    Tile *vtile;
    int *mark;

    Board board;

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

    for(i = 0; i < board.rows; ++i){
        board.data[i] = (Casa*) malloc(board.cols * sizeof(Casa));
        for(j = 0; j < board.cols; ++j){
            fscanf(fp, "%d/%d", &k, &board.data[i][j].rot);

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

    printBoard(board);


    // Free
    for(i = 0; i < board.rows; ++i)
        free(board.data[i]);
    free(board.data);

    free(mark);
    free(vtile);

    return 0;
}

// Stampa board
void printBoard(Board b){
    int i, j, k;
    char *mat = (char*) malloc(9 * b.rows * b.cols * sizeof(char));

    for(i = 0; i < b.rows; ++i){
        for(j = 0; j < b.cols; ++j){
            mat[3*j + (3*i+0)*3*b.cols + 0] = (char) 32;
            mat[3*j + (3*i+0)*3*b.cols + 2] = (char) 32;
            mat[3*j + (3*i+1)*3*b.cols + 1] = (char) 32;
            mat[3*j + (3*i+2)*3*b.cols + 0] = (char) 32;
            mat[3*j + (3*i+2)*3*b.cols + 2] = (char) 32;

            if(b.data[i][j].rot == -1){
                mat[3*j + (3*i+0)*3*b.cols + 1] = (char) 32;
                mat[3*j + (3*i+1)*3*b.cols + 0] = (char) 32;
                mat[3*j + (3*i+1)*3*b.cols + 2] = (char) 32;
                mat[3*j + (3*i+2)*3*b.cols + 1] = (char) 32;
            }
            else if(b.data[i][j].rot == 0){
                mat[3*j + (3*i+0)*3*b.cols + 1] = b.data[i][j].t->col2;
                mat[3*j + (3*i+1)*3*b.cols + 0] = b.data[i][j].t->col1;
                mat[3*j + (3*i+1)*3*b.cols + 2] = (char) (b.data[i][j].t->val1 + 48);
                mat[3*j + (3*i+2)*3*b.cols + 1] = (char) (b.data[i][j].t->val2 + 48);
            }
            else if(b.data[i][j].rot == 1){
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

    for(i = 0; i < 3*b.rows; ++i){
        if(i != 0 && i % 3 == 0){
            for(j = 0; j < 8*b.cols - 2; ++j){
                if(j != 0 && (j+2) % 8 == 0)
                    printf("+");
                else
                    printf("-");
            }
            printf("\n");
        }

        for(j = 0; j < 3*b.cols; ++j){
            if(j != 0 && j % 3 == 0)
                printf("| ");
            printf("%c ", mat[j + i*3*b.cols]);
        }
        printf("\n");
    }
    printf("\n");

    free(mat);
}
