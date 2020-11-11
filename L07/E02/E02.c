#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "list.h"

typedef enum{acq_elem, acq_file, ric_code, del_code, del_dates, stampa, fine} Comando;

// Legge comando da tastiera
Comando leggiComando(){
    char str[12];

    printf("Inserisci comando: ");
    scanf("%s", str);

    if(strcmp(str, "acq_elem") == 0)
        return acq_elem;
    else if(strcmp(str, "acq_file") == 0)
        return acq_file;
    else if(strcmp(str, "ric_code") == 0)
        return ric_code;
    else if(strcmp(str, "del_code") == 0)
        return del_code;
    else if(strcmp(str, "del_dates") == 0)
        return del_dates;
    else if(strcmp(str, "stampa") == 0)
        return stampa;
    else if(strcmp(str, "fine") == 0)
        return fine;
    // Inserito comando sbagliato
    exit(EXIT_FAILURE);
}

void selezionaDati(Comando com, Item **p){
    switch (com){
        case 0:{
            Info tmp;

            // Acquisisco da tastiera i dati
            printf("Codice: ");
            scanf("%s", tmp.codice);
            printf("Nome: ");
            scanf("%s", tmp.nome);
            printf("Cognome: ");
            scanf("%s", tmp.cognome);
            printf("Data (gg/mm/aaaa): ");
            scanf("%d/%d/%d", &tmp.data.gg, &tmp.data.mm, &tmp.data.aaaa);
            printf("Via: ");
            scanf("%s", tmp.via);
            printf("Citta: ");
            scanf("%s", tmp.citta);
            printf("Cap: ");
            scanf("%d", &tmp.cap);

            addRow(p, tmp); // Aggiungo alla lista
            break;
        }

        case 1:{
            char nome_file[20];
            printf("Nome file: ");
            scanf("%s", nome_file);

            FILE *fp = fopen(nome_file, "r");
            if(fp == NULL) exit(EXIT_FAILURE);

            addMult(p, fp);

            fclose(fp);
            break;
        }

        case 2:{
            char code[7];
            printf("Codice: ");
            scanf("%s", code);

            searchByCode(*p, code);
            break;
        }

        case 3:{
            char code[7];
            printf("Codice: ");
            scanf("%s", code);

            Item *tmp = deleteByCode(p, code);
            tmp->next = NULL;

            print(tmp, stdout);

            free(tmp);

            break;
        }

        case 4:{
            Date d1, d2;
            printf("Data iniziale (gg/mm/aaaa): ");
            scanf("%d/%d/%d", &d1.gg, &d1.mm, &d1.aaaa);
            printf("Data finale (gg/mm/aaaa): ");
            scanf("%d/%d/%d", &d2.gg, &d2.mm, &d2.aaaa);

            Item *headDel = deleteByDates(p, d2, d1), *tmp = headDel;
            print(headDel, stdout);

            while(tmp != NULL){
                headDel = headDel->next;
                free(tmp);
                tmp = headDel;
            }
            break;
        }

        case 5:{
            char nome_file[20];
            printf("Nome file: ");
            scanf("%s", nome_file);

            if(strcmp(nome_file, "stdout") != 0){
                FILE *fp = fopen(nome_file, "w");
                if(fp == NULL) exit(EXIT_FAILURE);
                print(*p, fp);
                fclose(fp);
            }
            else
                print(*p, stdout);
            break;
        }
    
        default:
            exit(EXIT_FAILURE);
            break;
    }
}

int main(int argc, char *argv[]){
    Comando com;

    Item* head = NULL; // Testa della lista

    // Comando possibili
    printf("Comandi possibili:\n");
    printf(" - acq_elem\n");
    printf(" - acq_file\n");
    printf(" - ric_code\n");
    printf(" - del_code\n");
    printf(" - del_dates\n");
    printf(" - stampa\n");
    printf(" - fine\n\n");

    // Legge in loop i comandi e processa fino a che non viene richiesto fine
    while(1){
        com = leggiComando();

        if(com == fine)
            return 0;
        selezionaDati(com, &head);
        printf("\n");
    }

    return 0;
}
