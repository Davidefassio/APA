#ifndef PERSONAGGI_H_INCLUDED
#define PERSONAGGI_H_INCLUDED

#include "inventario.h"

// Tab dell'equipaggiamento di un pg.
typedef struct{
    int inUso;
    inv_t *vettEq[8]; // Vettore di 8 puntatori.
}tabEquip_t;

// Player contenuto in un nodo.
typedef struct{
    char codice[7];
    char nome[MAXL+1];
    char classe[MAXL+1];
    tabEquip_t *equip;
    stat_t stat;
}pg_t;

// Nodo contenuto nella lista.
typedef struct nodoPg{
    pg_t pg;
    struct nodoPg *next;
}nodoPg_t;

// Lista di player.
typedef struct{
    nodoPg_t *headPg;
    nodoPg_t *tailPg;
    int nPg;
}tabPg_t;

// Prototipi funzioni.
nodoPg_t* addNodoInTesta(nodoPg_t*, pg_t); // Mi passi la testa e io la returno cambiata + payload.
int delNodo(nodoPg_t**, nodoPg_t**, char*); // Mi passi i puntatori a testa e coda e io li cambio + codice personaggio.
int addOggetto(nodoPg_t*, char*, tabInv_t, char*); // Mi passi il puntatore in testa + codice personaggio + vettore di oggetti + nome oggetto.
int delOggetto(nodoPg_t*, char*, tabInv_t, char*); // La testa resta costante + codice personaggio + vettore di oggetti + nome oggetto.
int calcStat(nodoPg_t*, char*, int*); // La testa resta costante + codice personaggio + vettore con le stats da restituire.

#endif /* PERSONAGGI_H_INCLUDED */
