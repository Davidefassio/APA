#include <stdlib.h>
#include <stdio.h>
#include "grafo.h"

int main(int argc, char *argv[]){
    FILE *f;
    f = fopen("grafo.txt", "r");
    if(f == NULL) exit(EXIT_FAILURE);

    Grafo g = GRF_initFromFile(f);

    fclose(f);

    int input, flag;

    printf("Comandi possibili:\n");
    printf(" 1) elenca vertici in ordine alfabetico\n");
    printf(" 2) verifica adiacenza di 3 vertici\n");
    printf(" 3) genera liste di adiacenza\n");
    printf(" 0) fine\n");

    while(1){
        printf("Inserisci comando: ");
        scanf("%d", &input);

        switch(input){
        case 0:
            GRF_free(g);
            return 0;
            break;

        case 1:
            enumVertexes(g);
            break;

        case 2:
            printf("Tramite matrice (0) o liste (1) di adiacenza: ");
            scanf("%d", &flag);

            checkAdj(g, flag);
            break;

        case 3:
            generateAdjList(g);
            break;

        default:
            exit(EXIT_FAILURE);
            break;
        }
    }

    return 0;
}
