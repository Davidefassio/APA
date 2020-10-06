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
    exit(EXIT_FAILURE);
}

void selezionaDati(Comando_e com, Corsa cor[], int l){
    switch (com) {
        case 0: {
            Data d1, d2;
            printf("Inserire due date: \n> ");
            scanf("%d/%d/%d", &d1.aaaa, &d1.gg, &d1.mm);
            printf("> ");
            scanf("%d/%d/%d", &d2.aaaa, &d2.gg, &d2.mm);
            
            break;
        }
            
        case 1: {
            char fermata[30];
            printf("Inserisci fermata: ");
            scanf("%s", fermata);
            
            break;
        }
            
        case 2: {
            char capolinea[30];
            printf("Inserisci capolinea: ");
            scanf("%s", capolinea);
            
            break;
        }
            
        case 3: {
            Data d1, d2;
            printf("Inserire due date: \n> ");
            scanf("%d/%d/%d", &d1.aaaa, &d1.gg, &d1.mm);
            printf("> ");
            scanf("%d/%d/%d", &d2.aaaa, &d2.gg, &d2.mm);
            
            break;
        }
            
        case 4: {
            char codice[20];
            printf("Inserire codice tratta: ");
            scanf("%s", codice);
            
            break;
        }
            
        default:
            break;
    }
    return;
}

int main(int argc, char* argv[]){
    int i, nr;
    Corsa corse[MAXCORSE];
    FILE *f;
    Comando_e com = r_date;
    
    f = fopen("corse.txt", "r");
    if(f == NULL){
        exit(EXIT_FAILURE);
    }
    
    fscanf(f, "%d", &nr);
    
    for(i = 0; i < nr; ++i){
        fscanf(f, "%s %s %s %d/%d/%d %d:%d:%d %d:%d:%d %d", corse[i].codice_tratta, corse[i].partenza, corse[i].destinazione, &corse[i].date.aaaa, &corse[i].date.gg, &corse[i].date.mm, &corse[i].ora_partenza.hh, &corse[i].ora_partenza.mm, &corse[i].ora_partenza.ss, &corse[i].ora_arrivo.hh, &corse[i].ora_arrivo.mm, &corse[i].ora_arrivo.ss, &corse[i].ritardo);
    }
    fclose(f);
    
    printf("Comandi possibili:\n");
    printf(" - r_date\n");
    printf(" - r_partenza\n");
    printf(" - r_capolinea\n");
    printf(" - r_ritardo\n");
    printf(" - r_ritardo_tot\n");
    printf(" - r_fine\n\n");
    
    while(1){
        com = leggiComando();
        
        if(com == r_fine){
            break;
        }
        
        selezionaDati(com, corse, nr);
    }
    
    return 0;
}
