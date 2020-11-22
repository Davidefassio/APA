#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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

// Prototipi.
// Tutte le funzioni sottostanti ritornano 0 se tutto OK, 1 altrimenti.
nodoPg_t* addNodoInTesta(nodoPg_t*, pg_t); // Mi passi la testa e io la returno cambiata + payload.
int delNodo(nodoPg_t**, nodoPg_t**, char*); // Mi passi i puntatori a testa e coda e io li cambio + codice personaggio.
int addOggetto(nodoPg_t*, char*, tabInv_t, char*); // Mi passi il puntatore in testa + codice personaggio + vettore di oggetti + nome oggetto.
int delOggetto(nodoPg_t*, char*, tabInv_t, char*); // La testa resta costante + codice personaggio + vettore di oggetti + nome oggetto.
int calcStat(nodoPg_t*, char*, int*); // La testa resta costante + codice personaggio + vettore con le stats da restituire.

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
        ++(tabPg->nPg);
    }

    fclose(fp); // Chiusura file personaggi.

    // Menu a scelta
    printf("Comandi possibili:\n");
    printf("  1) Aggiungi personaggio. (Esempio: 1 PG0200 Samira Combattente 2003 71 116 65 41 49)\n");
    printf("  2) Elimina personaggio.  (Esempio: 2 PG0200)\n");
    printf("  3) Aggiungi oggetto a un personaggio. (Esempio: 3 PG0200 MangiaMagia)\n");
    printf("  4) Elimina oggetto a un personaggio.  (Esempio: 4 PG0200 MangiaMagia)\n");
    printf("  5) Calcola statistiche di un personaggio. (Esempio: 5 PG0200)\n");
    printf("  0) Chiudi programma.\n\n");

    char str[150], tmpStr[MAXL+1];
    int stats[6];
    inv_t tmpInv;

    while(1){
        printf("Inserire comando: ");
        fgets(str, 150, stdin);

        switch(str[0]){
        case 48: // 0
            return 0; // Fine programma.
            break;

        case 49: // 1
            // Legge dalla stringa il personaggio e inizializza equip.
            sscanf(str+2, "%s %s %s %d %d %d %d %d %d", tmp.codice, tmp.nome, tmp.classe, &tmp.stat.hp, &tmp.stat.mp, &tmp.stat.atk, &tmp.stat.def, &tmp.stat.mag, &tmp.stat.spr);
            tmp.equip = (tabEquip_t*) malloc(sizeof(tabEquip_t));
            tmp.equip->inUso = 0;

            // Aggiungo in testa il nuovo personaggio.
            tabPg->headPg = addNodoInTesta(tabPg->headPg, tmp);
            break;

        case 50: // 2
            sscanf(str+2, "%s", tmpStr);

            if(delNodo(&(tabPg->headPg), &(tabPg->tailPg), tmpStr) == 0)
                printf("Eliminazione eseguita con successo.\n");
            else
                printf("Eliminazione fallita.\n");

            break;

        case 51: // 3
            sscanf(str+2, "%s %s", tmpStr, tmpInv.nome);

            if(addOggetto(tabPg->headPg, tmpStr, *tabInv, tmpInv.nome) == 0)
                printf("Aggiunta eseguita con successo.\n");
            else
                printf("Aggiunta fallita.\n");

            break;

        case 52: // 4
            sscanf(str+2, "%s %s", tmpStr, tmpInv.nome);

            if(delOggetto(tabPg->headPg, tmpStr, *tabInv, tmpInv.nome) == 0)
                printf("Aggiunta eseguita con successo.\n");
            else
                printf("Aggiunta fallita.\n");

            break;
            break;

        case 53: // 5
            sscanf(str+2, "%s", tmpStr);

            if(calcStat(tabPg->headPg, tmpStr, stats) == 0){
                for(i = 0; i < 6; ++i)
                    printf("%d ", stats[i]);
                printf("\n");
            }
            else{
                printf("Personaggio non trovato.\n");
            }
            break;

        default: // Comando errato.
            exit(EXIT_FAILURE);
            break;
        }
        printf("\n");
    }

    return 0; // Non dovrei mai arrivare a questo ruturn.
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
