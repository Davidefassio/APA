#include <stdlib.h>
#include <stdio.h>

#define MAXR 50

void leggiMatrice(int M[MAXR][MAXR], int maxr, int *nr, int *nc){
    int i, j;
    FILE *fp = fopen("mat.txt", "r");
    if(fp == NULL){ exit(EXIT_FAILURE); }
    fscanf(fp, "%d %d", nr, nc);
    for(i = 0; i < *nr; ++i){ for(j = 0; j < *nc; ++j){ fscanf(fp, "%d", &M[i][j]); } }
}

int riconosciRegione(int M[MAXR][MAXR], int nr, int nc, int r, int c, int *b, int *h){
    if(!M[r][c] || ((r != 0 || c != 0) && ((r > 0 && M[r-1][c]) || (c > 0 && M[r][c-1])))){ return *b = *h = 0; }
    
    int i;
    for(i = r; i < nr && M[i][c]; ++i);
    *h = i-r;
    for(i = c; i < nc && M[r][i]; ++i);
    *b = i-c;
    return 1;
}

int main(int argc, char *argv[]){
    int mat[MAXR][MAXR], nr, nc, b, h, r, c;
    int *pnr = &nr, *pnc = &nc, *pb = &b, *ph = &h;
    
    leggiMatrice(mat, MAXR, pnr, pnc);
    
    while(1){
        printf("Inserisci riga e colonna: \n");
        scanf("%d %d", &r, &c);
        if(r < 0 || c < 0){ break; }
        if(riconosciRegione(mat, nr, nc, r, c, pb, ph)){ printf("Regione trovata a (%d/%d) con dimensioni (b x h): %d x %d\n\n", r, c, b, h); }
        else{ printf("Regione non trovata!\n\n"); }
    }
    
    return 0;
}
