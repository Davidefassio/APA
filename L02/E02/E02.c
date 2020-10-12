#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXS 30
#define MAXCORSE 1000

typedef enum{r_date, r_partenza, r_capolinea,
             r_ritardo, r_ritardo_tot, r_fine} Comando_e;

typedef struct{ // Formato data: aaaa/gg/mm
    int aaaa;
    int gg;
    int mm;
}Data;

typedef struct{ // Formato ora: hh/mm/ss
    int hh;
    int mm;
    int ss;
}Ora;

typedef struct{
    char codice_tratta[MAXS];
    char partenza[MAXS];
    char destinazione[MAXS];

    Data date;
    Ora ora_partenza, ora_arrivo;

    int ritardo; // Minuti di ritardo
}Corsa;

// Legge comando da tastiera
Comando_e leggiComando(){
    char str[20];

    printf("Inserisci comando: ");
    scanf("%s", str);

    if(strcmp(str, "r_date") == 0){
        return r_date;
    }
    else if(strcmp(str, "r_partenza") == 0){
        return r_partenza;
    }
    else if(strcmp(str, "r_capolinea") == 0){
        return r_capolinea;
    }
    else if(strcmp(str, "r_ritardo") == 0){
        return r_ritardo;
    }
    else if(strcmp(str, "r_ritardo_tot") == 0){
        return r_ritardo_tot;
    }
    else if(strcmp(str, "r_fine") == 0){
        return r_fine;
    }
    // Comando inserito sbagliato
    exit(EXIT_FAILURE);
}

// Stampa le corse partite tra d1 e d2
void func_date(Corsa cor[], int l, Data d1, Data d2){
    int i;

    printf("Corse partite tra %d/%d/%d e %d/%d/%d:\n", d1.aaaa, d1.gg, d1.mm, d2.aaaa, d2.gg, d2.mm);
    for(i = 0; i < l; ++i){
        if(d1.aaaa <= cor[i].date.aaaa && cor[i].date.aaaa <= d2.aaaa){
            if(d1.mm <= cor[i].date.mm && cor[i].date.mm <= d2.mm){
                if(d1.gg <= cor[i].date.gg && cor[i].date.gg <= d2.gg){
                    printf(" - %s\n", cor[i].codice_tratta);
                }
            }
        }
    }
    printf("\n");
}

// Stampa le corse partite da ferm
void func_fermata(Corsa cor[], int l, char *ferm){
    int i;
    printf("Corse partite da %s:\n", ferm);
    for(i = 0; i < l; ++i){
        if(strcmp(cor[i].partenza, ferm) == 0){
            printf(" - %s\n", cor[i].codice_tratta);
        }
    }
    printf("\n");
}

// Stampa le corse che arrivano a cap
void func_capolinea(Corsa cor[], int l, char *cap){
    int i;
    printf("Corse arrivate a %s:\n", cap);
    for(i = 0; i < l; ++i){
        if(strcmp(cor[i].destinazione, cap) == 0){
            printf(" - %s\n", cor[i].codice_tratta);
        }
    }
    printf("\n");
}

// Stampa le corse arrivate in ritardo tra d1 e d2
void func_ritardo(Corsa cor[], int l, Data d1, Data d2){
    int i;

    printf("Corse partite tra %d/%d/%d e %d/%d/%d e arrivate in ritardo:\n", d1.aaaa, d1.gg, d1.mm, d2.aaaa, d2.gg, d2.mm);
    for(i = 0; i < l; ++i){
        if(cor[i].ritardo != 0){
            if(d1.aaaa <= cor[i].date.aaaa && cor[i].date.aaaa <= d2.aaaa){
                if(d1.mm <= cor[i].date.mm && cor[i].date.mm <= d2.mm){
                    if(d1.gg <= cor[i].date.gg && cor[i].date.gg <= d2.gg){
                        printf(" - %s\n", cor[i].codice_tratta);
                    }
                }
            }
        }
    }
    printf("\n");
}

// Stampa il ritardo totale delle corse cod
void func_ritardo_tot(Corsa cor[], int l, char *cod){
    int i, sum = 0;
    for(i = 0; i < l; ++i){
        if(strcmp(cor[i].codice_tratta, cod) == 0){
            sum += cor[i].ritardo;
        }
    }
    printf("Ritardo totale: %d\n\n", sum);
}

// Acquisisce dati aggiungitivi e chiama le funzione per l'elaborazione e stampa
void selezionaDati(Comando_e com, Corsa cor[], int l){
    switch (com) {
        case 0: {
            Data d1, d2;
            printf("Inserire due date (d1 <= d2): \n> ");
            scanf("%d/%d/%d", &d1.aaaa, &d1.gg, &d1.mm);
            printf("> ");
            scanf("%d/%d/%d", &d2.aaaa, &d2.gg, &d2.mm);

            func_date(cor, l, d1, d2);

            break;
        }

        case 1: {
            char fermata[30];
            printf("Inserisci fermata: ");
            scanf("%s", fermata);

            func_fermata(cor, l, fermata);

            break;
        }

        case 2: {
            char capolinea[30];
            printf("Inserisci capolinea: ");
            scanf("%s", capolinea);

            func_capolinea(cor, l, capolinea);

            break;
        }

        case 3: {
            Data d1, d2;
            printf("Inserire due date (d1 <= d2): \n> ");
            scanf("%d/%d/%d", &d1.aaaa, &d1.gg, &d1.mm);
            printf("> ");
            scanf("%d/%d/%d", &d2.aaaa, &d2.gg, &d2.mm);

            func_ritardo(cor, l, d1, d2);

            break;
        }

        case 4: {
            char codice[20];
            printf("Inserire codice tratta: ");
            scanf("%s", codice);

            func_ritardo_tot(cor, l, codice);

            break;
        }

        default:
            break;
    }
    return;
}

int main(int argc, char* argv[]){
    int i, nr, flag = 1;
    Corsa corse[MAXCORSE];
    FILE *f;
    Comando_e com = r_date;

    f = fopen("corse.txt", "r");
    if(f == NULL){
        exit(EXIT_FAILURE);
    }

    fscanf(f, "%d", &nr);
  
    // Lettura del file di log
    for(i = 0; i < nr; ++i){
        fscanf(f, "%s %s %s %d/%d/%d %d:%d:%d %d:%d:%d %d", corse[i].codice_tratta, corse[i].partenza, corse[i].destinazione, &corse[i].date.aaaa, &corse[i].date.gg, &corse[i].date.mm, &corse[i].ora_partenza.hh, &corse[i].ora_partenza.mm, &corse[i].ora_partenza.ss, &corse[i].ora_arrivo.hh, &corse[i].ora_arrivo.mm, &corse[i].ora_arrivo.ss, &corse[i].ritardo);
    }
    fclose(f);
    
    // Comando possibili
    printf("Comandi possibili:\n");
    printf(" - r_date\n");
    printf(" - r_partenza\n");
    printf(" - r_capolinea\n");
    printf(" - r_ritardo\n");
    printf(" - r_ritardo_tot\n");
    printf(" - r_fine\n\n");
  
    // Legge in loop i comandi e processa fino a che non viene richiesto r_fine
    while(flag){
        com = leggiComando();

        if(com == r_fine){
            flag = 0;
        }
        else{
            selezionaDati(com, corse, nr);
        }
    }

    return 0;
}
