#include <stdio.h>
#include <stdlib.h>

#define MAXR 20
#define MAXC 20
#define NAME 20

int main(int argc, char* argv[]){
    FILE* f;
    char nome_file[NAME];
    int mat[MAXR][MAXC], max_mat[MAXR][MAXC];
    int r, c, min, i, j, m, n, dim, sum, max;
    
    printf("Inserire nome file: ");
    scanf("%s", nome_file);
    
    f = fopen(nome_file, "r");
    if(f == NULL){
        return -1;
    }
    
    fscanf(f, "%d", &r);
    fscanf(f, "%d", &c);
    
    if(r < c){ min = r; }
    else{ min = c; }
    
    for(i = 0; i < r; ++i){
        for(j = 0; j < c; ++j){
            fscanf(f, "%d", &mat[i][j]);
        }
    }
    
    while(1){
        printf("Inserire dim (1 < dim < min{r, c}): ");
        scanf("%d", &dim);
        if(dim <= 0 || dim > min){ return -1; }
        
        max = -1000000000;
        for(i = 0; i <= r - dim; ++i){
            for(j = 0; j <= c - dim; ++j){
                sum = 0;
                for(m = 0; m < dim; ++m){
                    for(n = 0; n < dim; ++n){
                        printf("%d ", mat[i+m][j+n]);
                        sum += mat[i+m][j+n];
                    }
                    printf("\n");
                }
                printf("\n");
                
                if(sum > max){
                    max = sum;
                    for(m = 0; m < dim; ++m){
                        for(n = 0; n < dim; ++n){
                            max_mat[m][n] = mat[i+m][j+n];
                        }
                    }
                }
                
            }
        }
        
        printf("Max Matrix: \n");
        for(i = 0; i < dim; ++i){
            for(j = 0; j < dim; ++j){
                printf("%d ", max_mat[i][j]);
            }
            printf("\n");
        }
        printf("\n");
    }
  return 0;
}
