#include "inventario.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

tabInv_t* acqFileOgg(char *str){
    int i;

    // Lettura file degli oggetti.
    FILE *fp = fopen(str, "r");
    if(fp == NULL) exit(EXIT_FAILURE);

    tabInv_t *tmp = (tabInv_t*) malloc(sizeof(tabInv_t));

    fscanf(fp, "%d", &tmp->nInv);
    tmp->vettInv = (inv_t*) malloc(tmp->nInv * sizeof(inv_t));
    for(i = 0; i < tmp->nInv; ++i)
        fscanf(fp, "%s %s %d %d %d %d %d %d", tmp->vettInv[i].nome, tmp->vettInv[i].tipo, &tmp->vettInv[i].stat.hp, &tmp->vettInv[i].stat.mp, &tmp->vettInv[i].stat.atk, &tmp->vettInv[i].stat.def, &tmp->vettInv[i].stat.mag, &tmp->vettInv[i].stat.spr);

    fclose(fp); // Chiusura file oggetti.

    return tmp;
}

void stampaOgg(tabInv_t* tab, char *nome){
    int i;

    for(i = 0; i < tab->nInv; ++i){
        if(strcmp(nome, tab->vettInv[i].nome) == 0){
            printf("%s %s %d %d %d %d %d %d\n", tab->vettInv[i].nome, tab->vettInv[i].tipo, tab->vettInv[i].stat.hp, tab->vettInv[i].stat.mp, tab->vettInv[i].stat.atk, tab->vettInv[i].stat.def, tab->vettInv[i].stat.mag, tab->vettInv[i].stat.spr);
            return;
        }
    }
    printf("Oggetto non trovato.\n");
}
