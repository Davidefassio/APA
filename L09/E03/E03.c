#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Includo headers
#include "personaggi.h"
#include "inventario.h"


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

    return 0; // Non dovrei mai arrivare a questo return.
}
