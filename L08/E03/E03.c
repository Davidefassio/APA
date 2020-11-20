#include <stdlib.h>
#include <stdio.h>

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

// Prototipi
nodoPg_t* addNodoInTesta(nodoPg_t*, pg_t); // Mi passi la testa e io la returno cambiata + payload.
void delNodo(nodoPg_t**, nodoPg_t**, char*); // Mi passi i puntatori a testa e coda e io li cambio + codice personaggio.
void delOggetto(nodoPg_t*, char*, char*); // La testa resta costante + codice personaggio + nome oggetto.
int* calcStat(nodoPg_t*, char*); // La testa resta costante + codice personaggio. Returno un vettore con le stats.

int main(int argc, char *argv[]){
    int i;

    // Lettura file degli oggetti.
    FILE *fp = fopen("inventario.txt", "r");
    if(fp == NULL) exit(EXIT_FAILURE);

    tabInv_t *tabInv = (tabInv_t*) malloc(sizeof(tabInv_t));

    fscanf(fp, "%d", &tabInv->nInv);
    tabInv->vettInv = (inv_t*) malloc(tabInv->nInv * sizeof(inv_t));
    for(i = 0; i < tabInv->nInv; ++i)
        fscanf(fp, "%s %s %d %d %d %d %d %d", tabInv->vettInv[i].nome, tabInv->vettInv[i].tipo, &tabInv->vettInv[i].stat.hp, &tabInv->vettInv[i].stat.mp, &tabInv->vettInv[i].stat.atk, &tabInv->vettInv[i].stat.def, &tabInv->vettInv[i].stat.mag, &tabInv->vettInv[i].stat.spr);

    fclose(fp); // Chiusura file oggetti.

    // Lettura file dei personaggi.
    fp = fopen("pg.txt", "r");
    if(fp == NULL) exit(EXIT_FAILURE);

    tabPg_t *tabPg = (tabPg_t*) malloc(sizeof(tabPg_t));
    tabPg->headPg = tabPg->tailPg = NULL;
    tabPg->nPg = 0;

    pg_t tmp;

    i = 0;
    while(fscanf(fp, "%s %s %s %d %d %d %d %d %d", tmp.codice, tmp.nome, tmp.classe, &tmp.stat.hp, &tmp.stat.mp, &tmp.stat.atk, &tmp.stat.def, &tmp.stat.mag, &tmp.stat.spr) > 0){
        // Completo l'inizializzazione di tmp.
        tmp.equip = (tabEquip_t*) malloc(sizeof(tabEquip_t));
        tmp.equip->inUso = 0;

        // Cambio ogni volta la testa.
        // La coda la assegno solo la prima volta.
        tabPg->headPg = addNodoInTesta(tabPg->headPg, tmp);
        if(i == 0){
            tabPg->tailPg = tabPg->headPg;
            ++i;
        }
    }

    fclose(fp); // Chiusura file personaggi.

    return 0;
}

// Aggiungi un nodo in testa.
// La head cambia sempre.
// Caso speciale: head == NULL, allora next = NULL.
nodoPg_t* addNodoInTesta(nodoPg_t *head, pg_t payload){
    nodoPg_t *tmp = NULL;
    if(head != NULL) tmp = head;
    head = (nodoPg_t*) malloc(sizeof(nodoPg_t));
    head->pg = payload;
    head->next = tmp;
    return head;
}
