#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Includo headers
#include "personaggi.h"
#include "inventario.h"


int main(int argc, char *argv[]){
    int i;
    FILE *fp;
    pg_t tmp;

    // Lettura file inventario
    tabInv_t *tabInv = acqFileOgg("inventario.txt");

    // Lettura file dei personaggi
    tabPg_t *tabPg = acqFilePers("pg.txt");

    // Menu a scelta
    printf("Comandi possibili:\n");
    printf("  1) Aggiungi personaggio. (Esempio: 1 PG0200 Samira Combattente 2003 71 116 65 41 49)\n");
    printf("  2) Elimina personaggio.  (Esempio: 2 PG0200)\n");
    printf("  3) Aggiungi oggetto a un personaggio. (Esempio: 3 PG0200 MangiaMagia)\n");
    printf("  4) Elimina oggetto a un personaggio.  (Esempio: 4 PG0200 MangiaMagia)\n");
    printf("  5) Stampa un personaggio. (Esempio: 5 PG0200)\n");
    printf("  6) Stampa un oggetto. (Esempio: 6 Excalibur)\n");
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

        case 53: // 5
            sscanf(str+2, "%s", tmpStr);
            stampaPers(tabPg->headPg, tmpStr);
            break;

        case 54: // 6
            sscanf(str+2, "%s", tmpStr);
            stampaOgg(tabInv, tmpStr);
            break;

        default: // Comando errato.
            exit(EXIT_FAILURE);
            break;
        }
        printf("\n");
    }

    return 0; // Non dovrei mai arrivare a questo return.
}
