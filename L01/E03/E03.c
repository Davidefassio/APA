#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXN  30
#define LSTR 100

typedef struct{
    char selettore[8];
    int index;
    char dir[9];
    int pos;
}Op;

void ruota(int mat[MAXN][MAXN], int r, int c, Op *op){
    int tmp[MAXN], i;
    
    if(strcmp(op->selettore, "riga") == 0){
        if(strcmp(op->dir, "sinistra") == 0){
            for(i = 0; i < c; ++i){ tmp[i] = mat[op->index-1][((i+op->pos)+c)%c]; }
            for(i = 0; i < c; ++i){ mat[op->index-1][i] = tmp[i]; }
        }
        else if(strcmp(op->dir, "destra") == 0){
            for(i = 0; i < c; ++i){ tmp[i] = mat[op->index-1][((i-op->pos)+c)%c]; }
            for(i = 0; i < c; ++i){ mat[op->index-1][i] = tmp[i]; }
        }
        else{ return; }
    }
    else if(strcmp(op->selettore, "colonna") == 0){
        if(strcmp(op->dir, "su") == 0){
            for(i = 0; i < r; ++i){ tmp[i] = mat[((i+op->pos)+r)%r][op->index-1]; }
            for(i = 0; i < r; ++i){ mat[i][op->index-1] = tmp[i]; }
        }
        else if(strcmp(op->dir, "giu") == 0){
            for(i = 0; i < r; ++i){ tmp[i] = mat[((i-op->pos)+r)%r][op->index-1]; }
            for(i = 0; i < r; ++i){ mat[i][op->index-1] = tmp[i]; }
        }
        else{ return; }
    }
    else{ return; }
    return;
}

int main(int argc, char* argv[]){
    FILE *f;
    char nome_file[20], str[LSTR];
    int i, j, r, c, mat[MAXN][MAXN];
    Op oper;
    
    printf("Inserire nome file: ");
    scanf("%s", nome_file);
    fflush(stdin);
    
    f = fopen(nome_file, "r");
    if(f == NULL){ return -1; }
    
    fscanf(f, "%d", &r);
    fscanf(f, "%d", &c);
    for(i = 0; i < r; ++i){
        for(j = 0; j < c; ++j){
            fscanf(f, "%d", &mat[i][j]);
            printf("%2d ", mat[i][j]);
        }
        printf("\n");
    }
    
    while(1){
        printf("Inserire operazione (riga/colonna, 0 < index <= %d/%d, destra-sinistra/su-giu, pos) (fine): ", r, c);
        fgets(str, LSTR, stdin);
        sscanf(str, "%s", oper.selettore);
        if(strcmp(oper.selettore, "fine") == 0){ break; }
        sscanf(str, "%s %d %s %d", oper.selettore, &oper.index, oper.dir, &oper.pos);
        
        ruota(mat, r, c, &oper);
        for(i = 0; i < r; ++i){
            for(j = 0; j < c; ++j){
                printf("%2d ", mat[i][j]);
            }
            printf("\n");
        }
    }
    
    return 0;
}
