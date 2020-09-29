#include <stdlib.h>
#include <stdio.h>

#define SQUAD 20
#define GIORN 20

int main(int argc, char* argv[]){
    FILE *f, *o;
    char nome_file[20];
    int r, c, i, j, max, imax = -1, mat[SQUAD][GIORN], vec[SQUAD] = {0};
    
    printf("Inserisci nome file: ");
    scanf("%s", nome_file);
    
    f = fopen(nome_file, "r");
    
    fscanf(f, "%d", &r);
    fscanf(f, "%d", &c);
    
    for(i = 0; i < r; ++i){
        for(j = 0; j < c; ++j){
            fscanf(f, "%d", &mat[i][j]);
        }
    }
    fclose(f);
    
    o = fopen("output.txt", "w");
    
    for(i = 0; i < c; ++i){
        for(j = 0; j < r; ++j){
            vec[j] += mat[j][i];
        }
        
        max = -1;
        
        for(j = 0; j < r; ++j){
            if(vec[j] > max){
                max = vec[j];
                imax = j;
            }
        }
        
        fprintf(o, "%d ", imax);
    }
    
    return 0;
}
