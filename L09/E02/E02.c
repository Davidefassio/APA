#include <stdlib.h>
#include <stdio.h>

// Sono messi in questo ordine per evitare sprechi di padding.
// Suppondo col1/val1 orizzontali e col2/val2 verticali,
// in caso di rotazioni scambio.
typedef struct{
    int val1;
    int val2;
    char col1;
    char col2;
}Tile;

int main(int argc, char *argv[]){
    int i, j, nt;
    Tile *vtile;
    
    FILE *fp = fopen("tiles.txt", "r");
    if(fp == NULL) exit(EXIT_FAILURE);
    
    fscanf(fp, "%d", &nt); // Numero tiles
    vtile = (Tile*) malloc(nt * sizeof(Tile)); // Allocazione dinamica del vettore
    
    for(i = 0; i < nt; ++i) // Acquisizione delle tiles
        fscanf(fp, "%c %d %c %d", &vtile[i].col1, &vtile[i].val1, &vtile[i].col2, &vtile[i].val2);
    
    fclose(fp); // Chiusi tiles.txt
    
    return 0;
}
