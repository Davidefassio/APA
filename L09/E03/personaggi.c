#include "personaggi.h"

#include <stdlib.h>
#include <string.h>

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

// Elimina un nodo (personaggio) dalla lista e libera la memoria.
int delNodo(nodoPg_t **head, nodoPg_t **tail, char *codPers){
    if(*head == NULL && *tail == NULL){ // Lista vuota.
        return 1;
    }
    if(*head == *tail){ // Lista con un elemento.
        if(strcmp((*head)->pg.codice, codPers) == 0){
            free((*head)->pg.equip);
            free(*head);
            *head = *tail = NULL; // Diventa una lista vuota.
            return 0;
        }
        else{
            return 1;
        }
    }
    // Lista con piu elementi.
    nodoPg_t *tmp, *prev;
    if(strcmp((*head)->pg.codice, codPers) == 0){ // Primo elemento.
        tmp = (*head)->next;
        free((*head)->pg.equip);
        free(*head);
        *head = tmp;
        return 0;
    }
    prev = *head;
    tmp = (*head)->next;

    while(tmp->next != NULL){
        if(strcmp(tmp->pg.codice, codPers) == 0){ // Elemento in mezzo
            prev->next = tmp->next;
            free(tmp->pg.equip);
            free(tmp);
            return 0;
        }
    }

    if(strcmp(tmp->pg.codice, codPers) == 0){ // Ultimo elemento
        prev->next = NULL;
        free(tmp->pg.equip);
        free(tmp);
        *tail = prev;
        return 0;
    }

    return 1; // Non trovato
}

// Aggiunge un oggetto all'inventario del personaggio.
int addOggetto(nodoPg_t *head, char *codPers, tabInv_t tab, char *nomeOgg){
    int i;
    for(i = 0; i < tab.nInv; ++i)
        if(strcmp(tab.vettInv[i].nome, nomeOgg) == 0)
            break;

    if(i == tab.nInv) // Oggetto non trovato.
        return 1;

    while(head != NULL){ // Traverso la lista fino alla fine
        if(strcmp(head->pg.codice, codPers) == 0){
            if(head->pg.equip->inUso == 8)
                return 1; // Inventario pieno.

            // Assegno il puntatore e incremento il numero di oggetti in uso.
            head->pg.equip->vettEq[head->pg.equip->inUso] = tab.vettInv + i;
            ++(head->pg.equip->inUso);
            return 0; // Successo!
        }
        head = head->next;
    }
    return 1; // Non ho trovato il personaggio.
}

// Elimina un oggetto dall'inventario del personaggio.
int delOggetto(nodoPg_t *head, char *codPers, tabInv_t tab, char *nomeOgg){
    int i;
    while(head != NULL){ // Traverso la lista fino alla fine
        if(strcmp(head->pg.codice, codPers) == 0){ // Trovato il personaggio
            for(i = 0; i < head->pg.equip->inUso; ++i){ // Ciclo sull'inventario
                if(strcmp(head->pg.equip->vettEq[i]->nome, nomeOgg) == 0){ // Trovato l'oggetto
                    // Scambio l'oggetto con l'ultimo e decremento il numero di oggetti in uso.
                    head->pg.equip->vettEq[i] = head->pg.equip->vettEq[--(head->pg.equip->inUso)];
                    return 0; // Successo!
                }
            }
        }
        head = head->next;
    }
    return 1; // Non ho trovato il personaggio.
}

// Calcolo le statistiche di un personaggio.
// Modifica il vettor stat.
int calcStat(nodoPg_t *head, char *codPers, int *stat){
    int i;
    while(head != NULL){ // Traverso la lista fino alla fine
        if(strcmp(head->pg.codice, codPers) == 0){
            // Inizializzo il vettorecon le stat del personaggio.
            stat[0] = head->pg.stat.hp;
            stat[1] = head->pg.stat.mp;
            stat[2] = head->pg.stat.atk;
            stat[3] = head->pg.stat.def;
            stat[4] = head->pg.stat.mag;
            stat[5] = head->pg.stat.spr;

            // Per ogni oggetto nell'inventario sommo le stat.
            for(i = 0; i < head->pg.equip->inUso; ++i){
                stat[0] += head->pg.equip->vettEq[i]->stat.hp;
                stat[1] += head->pg.equip->vettEq[i]->stat.mp;
                stat[2] += head->pg.equip->vettEq[i]->stat.atk;
                stat[3] += head->pg.equip->vettEq[i]->stat.def;
                stat[4] += head->pg.equip->vettEq[i]->stat.mag;
                stat[5] += head->pg.equip->vettEq[i]->stat.spr;
            }

            // Azzero le stat negative
            for(i = 0; i < 6; ++i)
                if(stat[i] < 0)
                    stat[i] = 0;

            return 0; // Tutto a posto.
        }
        head = head->next;
    }
    return 1; // Non ho trovato il personaggio.
}
