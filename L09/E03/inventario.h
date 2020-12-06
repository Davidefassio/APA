#ifndef INVENTARIO_H_INCLUDED
#define INVENTARIO_H_INCLUDED

#define MAXL 50 // Lunghezza massima delle stringhe

// Sestupla delle statistiche.
typedef struct{
    int hp;
    int mp;
    int atk;
    int def;
    int mag;
    int spr;
}stat_t;

// Struct contenente un oggetto.
typedef struct{
    char nome[MAXL+1];
    char tipo[MAXL+1];
    stat_t stat;
}inv_t;

// Vector di inv_t, cioe' la tabella degli oggetti.
typedef struct{
    inv_t *vettInv;
    int nInv;
}tabInv_t;

// Prototipi funzioni.
tabInv_t* acqFileOgg(char*); // Mi passi il nome del file e io returno puntatore a tabella.
void stampaOgg(tabInv_t*, char*); // Stampa un oggetto sapendo il nome.

#endif /* INVENTARIO_H_INCLUDED */
