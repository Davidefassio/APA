#include "personaggi.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


tabPg_t* acqFilePers(char *str){
    // Lettura file dei personaggi
    FILE *fp = fopen("pg.txt", "r");
    if(fp == NULL) exit(EXIT_FAILURE);

    tabPg_t *tabPg = (tabPg_t*) malloc(sizeof(tabPg_t));
    tabPg->headPg = tabPg->tailPg = NULL;
    tabPg->nPg = 0;

    pg_t tmp;

    int i = 0;
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
        ++(tabPg->nPg);
    }

    fclose(fp); // Chiusura file personaggi.

    return tabPg;
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

// Stampa un personaggio e il suo equipaggiamento.
void stampaPers(nodoPg_t *head, char *codPers){
    int i;
    while(head != NULL){ // Traverso la lista fino alla fine
        if(strcmp(head->pg.codice, codPers) == 0){
            printf("%s %s %s %d %d %d %d %d %d\n", head->pg.codice, head->pg.nome, head->pg.classe, head->pg.stat.hp, head->pg.stat.mp, head->pg.stat.atk, head->pg.stat.def, head->pg.stat.mag, head->pg.stat.spr);

            for(i = 0; i < head->pg.equip->inUso; ++i)
                printf("%d) %s %s %d %d %d %d %d %d\n", i+1, head->pg.equip->vettEq[i]->nome, head->pg.equip->vettEq[i]->tipo, head->pg.equip->vettEq[i]->stat.hp, head->pg.equip->vettEq[i]->stat.mp, head->pg.equip->vettEq[i]->stat.atk, head->pg.equip->vettEq[i]->stat.def, head->pg.equip->vettEq[i]->stat.mag, head->pg.equip->vettEq[i]->stat.spr);

            return;
        }
        head = head->next;
    }
    printf("Personaggio non trovato.\n");
}
