#include <stdlib.h>
#include <stdio.h>
#include "stockList.h"

#define LEN 30

int main(int argc, char *argv[]){
    StockList sl = SL_init();
    int in, s;
    char nome[LEN];
    FILE* fp;
    Data d1, d2;
    Stock stc;
    DailyQuot *dq;

    printf("Menu:\n");
    printf(" 1) acquisisci da file\n");
    printf(" 2) ricerca titolo\n");
    printf(" 3) ricarca quotazione di un titolo in data\n");
    printf(" 4) ricerca quotazione massima e minima di un titolo in un intervallo di date\n");
    printf(" 5) ricerca quatazione massima e minima di un titolo\n");
    printf(" 6) bilancia BST\n");
    printf(" 0) esci\n\n");

    while(1){
        printf("> ");
        scanf("%d", &in);

        switch(in){
        case 0:
            return 0;
            break;

        case 1:
            printf("Inserisci nome file: ");
            scanf("%s", nome);

            fp = fopen(nome, "r");
            if(fp == NULL){
                printf("File non trovato.\n");
                break;
            }
            SL_insertFromFile(sl, fp);
            fclose(fp);
            break;

        case 2:
            printf("Inserisci codice titolo: ");
            scanf("%s", nome);
            stc = SL_search(sl, nome);
            if(Stock_getCode(stc)[0] == '\0'){
                printf("Titolo non trovato.\n");
                break;
            }

            Stock_fprint(stdout, stc);
            break;

        case 3:
            printf("Inserisci codice titolo: ");
            scanf("%s", nome);
            stc = SL_search(sl, nome);
            if(Stock_getCode(stc)[0] == '\0'){
                printf("Titolo non trovato.\n");
                break;
            }

            printf("Inserisci data (aaaa/mm/gg hh:mm): ");
            data_fscan(stdin, &d1);

            dq = BST_search(Stock_getBST(stc), d1);
            if(dq->ntrans == 0){
                printf("Quotazione giornaliera non trovata.\n");
                break;
            }

            DQ_fprint(stdout, *dq);
            break;

        case 4:
            printf("Inserisci codice titolo: ");
            scanf("%s", nome);
            stc = SL_search(sl, nome);
            if(Stock_getCode(stc)[0] == '\0'){
                printf("Titolo non trovato.\n");
                break;
            }

            printf("Inserisci data di inizio (aaaa/mm/gg hh:mm): ");
            data_fscan(stdin, &d1);

            printf("Inserisci data di fine (aaaa/mm/gg hh:mm): ");
            data_fscan(stdin, &d2);

            BST_minmaxInterval(Stock_getBST(stc), d1, d2);
            break;

        case 5:
            printf("Inserisci codice titolo: ");
            scanf("%s", nome);
            stc = SL_search(sl, nome);
            if(Stock_getCode(stc)[0] == '\0'){
                printf("Titolo non trovato.\n");
                break;
            }

            BST_minmaxAll(Stock_getBST(stc));
            break;

        case 6:
            printf("Inserisci codice titolo: ");
            scanf("%s", nome);
            stc = SL_search(sl, nome);
            if(Stock_getCode(stc)[0] == '\0'){
                printf("Titolo non trovato.\n");
                break;
            }

            printf("Inserisci soglia: ");
            scanf("%d", &s);

            BST_balance(Stock_getBST(stc), s);

        }
        printf("\n");
    }

    // Non dovrei mai arrivare qua
    return 0;
}
