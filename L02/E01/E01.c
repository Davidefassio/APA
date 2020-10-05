#include <stdlib.h>
#include <stdio.h>

#define MAXR 50
#define MAXC 50

typedef struct{
    int x;
    int y;
    int b;
    int h;
    int a;
}Rect;

int main(int argc, char* argv[]){
    int nr, nc, mat[MAXR][MAXC];
    int i, j, p, q, max, imax, rcnt = 0;
    Rect rects[MAXR*MAXC/2];
    FILE *f;

    // Apertura e lettura file
    f = fopen("mappa.txt", "r");
    if(f == NULL){
        exit(EXIT_FAILURE);
    }

    fscanf(f, "%d %d", &nr, &nc);

    for(i = 0; i < nr; ++i){
        for(j = 0; j < nc; ++j){
            fscanf(f, "%d", &mat[i][j]);
        }
    }
    fclose(f);

    // Analizzo i rettangoli
    for(i = 0; i < nr; ++i){
        for(j = 0; j < nc; ++j){
            if(mat[i][j]){
                rects[rcnt].x = i;
                rects[rcnt].y = j;

                // Trovo base
                for(p = 0; mat[i][p+j] && p+j < nc; ++p){}
                rects[rcnt].b = p;

                // Trovo altezza
                for(p = 0; mat[p+i][j] && p+i < nr; ++p){}
                rects[rcnt].h = p;

                // Calcolo area
                rects[rcnt].a = rects[rcnt].b * rects[rcnt].h;

                // Azzero le caselle del rettangolo
                for(p = 0; p < rects[rcnt].h; ++p){
                    for(q = 0; q < rects[rcnt].b; ++q){
                        mat[p+i][q+j] = 0;
                    }
                }

                ++rcnt;
            }
        }
    }

    // Base
    max = -1;
    for(i = 0; i < rcnt; ++i){
        if(rects[i].b > max){
            max = rects[i].b;
            imax = i;
        }
    }
    printf("Max base:    <%d, %d>, b=%d, h=%d, Area=%d\n", rects[imax].x, rects[imax].y, rects[imax].b, rects[imax].h, rects[imax].a);

    // Area
    max = -1;
    for(i = 0; i < rcnt; ++i){
        if(rects[i].a > max){
            max = rects[i].a;
            imax = i;
        }
    }
    printf("Max area:    <%d, %d>, b=%d, h=%d, Area=%d\n", rects[imax].x, rects[imax].y, rects[imax].b, rects[imax].h, rects[imax].a);

    // Altezza
    max = -1;
    for(i = 0; i < rcnt; ++i){
        if(rects[i].h > max){
            max = rects[i].h;
            imax = i;
        }
    }
    printf("Max altezza: <%d, %d>, b=%d, h=%d, Area=%d\n", rects[imax].x, rects[imax].y, rects[imax].b, rects[imax].h, rects[imax].a);

    return 0;
}
