#include <stdlib.h>
#include <stdio.h>

#define MAXS 30
#define MAXCORSE 1000

typedef struct{
    char codice_tratta[MAXS];
    char partenza[MAXS];
    char destinazione[MAXS];

    struct{ // Formato data: aaaa/gg/mm
        int aaaa;
        int gg;
        int mm;
    }Data;

    struct{ // Formato ora: hh/mm/ss
        int hh;
        int mm;
        int ss;
    }Ora_partenza, Ora_arrivo;

    int ritardo; // Minuti di ritardo
}Corsa;

int main(int argc, char* argv[]){
    int i, nr;
    Corsa corse[MAXCORSE];
    FILE *f;

    f = fopen("corse.txt", "r");
    if(f == NULL){
        exit(EXIT_FAILURE);
    }

    fscanf(f, "%d", &nr);

    for(i = 0; i < nr; ++i){
        fscanf(f, "%s %s %s %d/%d/%d %d:%d:%d %d:%d:%d %d", corse[i].codice_tratta, corse[i].partenza, corse[i].destinazione, &corse[i].Data.aaaa, &corse[i].Data.gg, &corse[i].Data.mm, &corse[i].Ora_partenza.hh, &corse[i].Ora_partenza.mm, &corse[i].Ora_partenza.ss, &corse[i].Ora_arrivo.hh, &corse[i].Ora_arrivo.mm, &corse[i].Ora_arrivo.ss, &corse[i].ritardo);
    }
    fclose(f);

    return 0;
}
