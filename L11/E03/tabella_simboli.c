#include "tabella_simboli.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


/**
    Inizializza una nuova tabella di simboli.
    Param: void
    Return: Puntatore a tabella di simboli
*/
TS* TS_init(){
    TS *tmp = (TS*) malloc(sizeof(TS));
    tmp->len = 0;
    tmp->cap = 1;
    tmp->data = NULL;
    return tmp;
}


/**
    Aggiunge in coda una nuova stringa se unica,
    se serve raddoppia la capacita.
    Param:
        tab: puntatore a tabella di simboli
        str: stringa da aggiungere
    Return: void
    Exception:
        in caso di errore in allocazione chiude il programma
*/
void TS_push(TS *tab, char *str){
    if(TS_getIndexByName(tab, str) != -1)
        return; // Elemento gia presente

    if(tab->len >= tab->cap){ // Raddoppio la capacita
        tab->cap *= 2;
        tab->data = realloc(tab->data, tab->cap * sizeof(char*));
        if(tab->data == NULL) exit(EXIT_FAILURE);
    }
    // Aggiungo l'elemento in coda
    tab->data[(tab->len)++] = strdup(str);
}


/**
    Cancella un elemento dato l'indice.
    NON rialloca la memoria.
    Param:
        tab: puntatore a tabella di simboli
        index: indice da cancellare
    Return:
        1: fallimento
        0: successo
*/
int TS_deleteByIndex(TS *tab, int index){
    if(index >= tab->len || index < 0) return 1; // Fallimento
    for(;index < (tab->len - 1); ++index)
        tab->data[index] = tab->data[index+1]; // Sposto
    tab->data[index] = NULL; // Cancello
    return 0; // Successo
}


/**
    Cancella un elemento dato il nome.
    NON rialloca la memoria.
    Param:
        tab: puntatore a tabella di simboli
        str: nome da cancellare
    Return:
        1: fallimento
        0: successo
*/
int TS_deleteByName(TS *tab, char *str){
    // Cerco l'indice e poi lo cancello tramite l'indice
    return TS_deleteByIndex(tab, TS_getIndexByName(tab, str));
}


/**
    Alloca la memoria per una stringa uguale
    a quella all'indice passato.
    Param:
        tab: puntatore a tabella di simboli
        index: indice da copiare
    Return:
        stringa allocata dinamicamente contenente un copia
        del nome all'indice index
*/
char* TS_getNameByIndex(TS *tab, int index){
    // Duplica la stringa all'indice e returna
    return strdup(tab->data[index]);
}


/**
    Returna l'indice a cui si trova il nome passato.
    Param:
        tab: puntatore a tabella di simboli
        str: nome da cercare
    Return:
        indice del nome passato
*/
int TS_getIndexByName(TS *tab, char *str){
    int i;
    for(i = 0; i < tab->len; ++i)
        if(strcmp(tab->data[i], str) == 0)
            return i; // Trovato
    return -1; // NON trovato
}


/**
    Libera la memoria in eccesso in modo che capacita == lunghezza.
    Param:
        tab: puntatore a tabella di simboli
    Return: void
*/
void TS_shrinkToFit(TS *tab){
    tab->cap = tab->len;
    tab->data = realloc(tab->data, tab->cap * sizeof(char*));
    if(tab->data == NULL) // Non dovrebbe MAI accadere
        exit(EXIT_FAILURE);
}


/**
    Libera la memoria associata alla tabella.
    Param:
        tab: puntatore a tabella di simboli
    Return: void
*/
void TS_free(TS *tab){
    int i;
    for(i = 0; i < tab->len; ++i)
        free(tab->data[i]); // Libera le stringhe
    free(tab->data); // Libera il vettore
    free(tab); // Libera la struct
}

