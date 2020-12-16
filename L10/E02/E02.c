#include <stdlib.h>
#include <stdio.h>
#include "tensor.h"

int creaCollana(int*);
int fz(int*, Tensor5d);
int fr(int*, Tensor5d);
int ft(int*, Tensor5d);
int fs(int*, Tensor5d);

int main(int argc, char * argv[]){
    int i, nr, len;
    int gems[4];

    FILE *fp;
    char nome_file[30];

    printf("Inserire nome file: ");
    scanf("%s", nome_file);
    fp = fopen(nome_file, "r");
    if(fp == NULL) exit(EXIT_FAILURE);

    fscanf(fp, "%d", &nr);

    for(i = 0; i < nr; ++i){ // Ciclo su ogni collana
        fscanf(fp, "%d %d %d %d", &gems[0], &gems[1], &gems[2], &gems[3]);

        // Crea una collana e restituisci la lunghezza massima
        len = creaCollana(gems);
        
        printf("%2d) %d\n", i+1, len);
    }
    fclose(fp);

    return 0;
}

int creaCollana(int *gems){
    Tensor5d mem = TensorInit(4, gems[0], gems[1], gems[2], gems[3]);
    
    int max = -1, n = 0;
    
    n = fz(gems, mem);
    if(n > max) max = n;
    
    n = fr(gems, mem);
    if(n > max) max = n;
    
    n = ft(gems, mem);
    if(n > max) max = n;
    
    n = fs(gems, mem);
    if(n > max) max = n;
    
    // TensorFree(mem);
    return max;
}

int fz(int *gems, Tensor5d t){
    // Ho finito le gemme
    if(gems[0] == 0)
        return 0;
    
    // Conosco gia la posiziones
    if(t.ten[0][gems[0]][gems[1]][gems[2]][gems[3]] != -1)
        return t.ten[0][gems[0]][gems[1]][gems[2]][gems[3]];
    
    --gems[0]; // Metto una pietra
    
    int max = fz(gems, t), n = fr(gems, t);
    if(n > max) max = n;
    ++max;
    
    ++gems[0];
    
    // Salvo il risultato per la memoization
    t.ten[0][gems[0]][gems[1]][gems[2]][gems[3]] = max;
    
    return max;
}

int fr(int *gems, Tensor5d t){
    // Ho finito le gemme
    if(gems[1] == 0)
        return 0;
    
    // Conosco gia la posizione
    if(t.ten[1][gems[0]][gems[1]][gems[2]][gems[3]] != -1)
        return t.ten[1][gems[0]][gems[1]][gems[2]][gems[3]];
    
    --gems[1]; // Metto una pietra
    
    int max = ft(gems, t), n = fs(gems, t);
    if(n > max) max = n;
    ++max;
    
    ++gems[1];
    
    // Salvo il risultato per la memoization
    t.ten[1][gems[0]][gems[1]][gems[2]][gems[3]] = max;
    
    return max;
}

int ft(int *gems, Tensor5d t){
    // Ho finito le gemme
    if(gems[2] == 0)
        return 0;
    
    // Conosco gia la posizione
    if(t.ten[2][gems[0]][gems[1]][gems[2]][gems[3]] != -1)
        return t.ten[2][gems[0]][gems[1]][gems[2]][gems[3]];
    
    --gems[2]; // Metto una pietra
    
    int max = fz(gems, t), n = fr(gems, t);
    if(n > max) max = n;
    ++max;
    
    ++gems[2];
    
    // Salvo il risultato per la memoization
    t.ten[2][gems[0]][gems[1]][gems[2]][gems[3]] = max;
    
    return max;
}

int fs(int *gems, Tensor5d t){
    // Ho finito le gemme
    if(gems[3] == 0)
        return 0;
    
    // Conosco gia la posizione
    if(t.ten[3][gems[0]][gems[1]][gems[2]][gems[3]] != -1)
        return t.ten[3][gems[0]][gems[1]][gems[2]][gems[3]];
    
    --gems[3]; // Metto una pietra
    
    int max = ft(gems, t), n = fs(gems, t);
    if(n > max) max = n;
    ++max;
    
    ++gems[3];
    
    // Salvo il risultato per la memoization
    t.ten[3][gems[0]][gems[1]][gems[2]][gems[3]] = max;
    
    return max;
}
