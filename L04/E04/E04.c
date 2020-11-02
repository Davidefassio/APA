#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXS 30
#define MAXCORSE 1000

typedef enum{stampa_log, o_data, o_codice, o_partenze, o_arrivo, ric_part, fine} Comando_e;

typedef struct{ // Formato data: aaaa/gg/mm
    int aaaa;
    int gg;
    int mm; // Mese
}Data;

typedef struct{ // Formato ora: hh/mm/ss
    int hh;
    int mm; // Minuti
    int ss;
}Ora;

typedef struct{
    char codice_tratta[MAXS];
    char partenza[MAXS];
    char destinazione[MAXS];
    
    Data data;
    Ora ora_partenza, ora_arrivo;
    
    int ritardo; // Minuti di ritardo
}Corsa;


// Funzioni di confronto
int cmp_data(Corsa c1, Corsa c2){
    if(c1.data.aaaa != c2.data.aaaa){ return c1.data.aaaa - c2.data.aaaa; }
    if(c1.data.mm   != c2.data.mm  ){ return c1.data.mm   - c2.data.mm  ; }
    if(c1.data.gg   != c2.data.gg  ){ return c1.data.gg   - c2.data.gg  ; }
    
    if(c1.ora_partenza.hh != c2.ora_partenza.hh){ return c1.ora_partenza.hh - c2.ora_partenza.hh; }
    if(c1.ora_partenza.mm != c2.ora_partenza.mm){ return c1.ora_partenza.mm - c2.ora_partenza.mm; }
    if(c1.ora_partenza.ss != c2.ora_partenza.ss){ return c1.ora_partenza.ss - c2.ora_partenza.ss; }
    return 0;
}

int cmp_codice(Corsa c1, Corsa c2){
    return strcmp(c1.codice_tratta, c2.codice_tratta);
}

int cmp_partenza(Corsa c1, Corsa c2){
    return strcmp(c1.partenza, c2.partenza);
}

int cmp_arrivo(Corsa c1, Corsa c2){
    return strcmp(c1.destinazione, c2.destinazione);
}

// Implementazione del selection sort che permette il passaggio
// di varie funzioni di confronto.
void selectionsort(Corsa cor[], int l, int (*cmp)(Corsa, Corsa)){
    int i, j, imin;
    Corsa tmp;
    
    for(i = 0; i < l - 1; ++i){
        imin = i;
        
        for(j = i + 1; j < l; ++j)
            if(cmp(cor[j], cor[imin]) < 0)  // cor[j] < cor[imin]
                imin = j;
        
        tmp = cor[j];
        cor[j] = cor[imin];
        cor[imin] = tmp;
    }
}

// Stampa su file i log
void stampa(Corsa cor[], int l, char *nome_file){
    FILE *fp = fopen(nome_file, "w");
    if(fp == NULL){ exit(EXIT_FAILURE); }
    
    int i;
    for(i = 0; i < l; ++i){
        fprintf(fp, "%s %s %s %d/%d/%d %d:%d:%d %d:%d:%d %d", cor[i].codice_tratta, cor[i].partenza, cor[i].destinazione, cor[i].data.aaaa, cor[i].data.gg, cor[i].data.mm, cor[i].ora_partenza.hh, cor[i].ora_partenza.mm, cor[i].ora_partenza.ss, cor[i].ora_arrivo.hh, cor[i].ora_arrivo.mm, cor[i].ora_arrivo.ss, cor[i].ritardo);
    }
}

// Legge comando da tastiera
Comando_e leggiComando(){
    char str[20];
    
    printf("Inserisci comando: ");
    scanf("%s", str);
    
    if(strcmp(str, "stampa_log") == 0){
        return stampa_log;
    }
    else if(strcmp(str, "o_data") == 0){
        return o_data;
    }
    else if(strcmp(str, "o_codice") == 0){
        return o_codice;
    }
    else if(strcmp(str, "o_partenze") == 0){
        return o_partenze;
    }
    else if(strcmp(str, "o_arrivo") == 0){
        return o_arrivo;
    }
    else if(strcmp(str, "ric_part") == 0){
        return ric_part;
    }
    else if(strcmp(str, "fine") == 0){
        return fine;
    }
    // Comando inserito sbagliato
    exit(EXIT_FAILURE);
}

// Acquisisce dati aggiungitivi e chiama le funzione per l'elaborazione
void selezionaDati(Comando_e com, Corsa cor[], int l, int *chiave){
    switch(com){
        case 0:{ // Stampa su file
            char nome_file[20];
            printf("Inserire nome del file di output (stampa a video = stdout): ");
            scanf("%s", nome_file);
            stampa(cor, l, nome_file);
            break;
        }
                   
        case 1: // Ordina per data
            selectionsort(cor, l, cmp_data);
            *chiave = 3;
            break;
                   
        case 2: // Ordina per codice tratta
            selectionsort(cor, l, cmp_codice);
            *chiave = 0;
            break;
                   
        case 3: // Ordina per stazione di partenza
            selectionsort(cor, l, cmp_partenza);
            *chiave = 1;
            break;
                   
        case 4: // Ordina per stazione di arrivo
            selectionsort(cor, l, cmp_arrivo);
            *chiave = 2;
            break;
                   
        case 5:{ // Ricerca tratta
            char codice[20];
            printf("Inserire codice tratta (o le lettere iniziali) : ");
            scanf("%s", codice);
          
            // TODO (anche da scrivere le funzioni)
            if(*chiave == 1){ // Ricerca dicotomica
                
            }
            else{ // Ricerca lineare
                
            }
            break;
        }
        
        default:
            exit(EXIT_FAILURE);
            break;
    }
}


int main(int argc, char* argv[]){
    int i, nr, flag = 1, chiave = -1;
    Corsa corse[MAXCORSE];
    FILE *f;
    Comando_e com = stampa_log;
    
    f = fopen("corse.txt", "r");
    if(f == NULL){
        exit(EXIT_FAILURE);
    }
    
    fscanf(f, "%d", &nr);
    
    // Lettura del file di log
    for(i = 0; i < nr; ++i){
        fscanf(f, "%s %s %s %d/%d/%d %d:%d:%d %d:%d:%d %d", corse[i].codice_tratta, corse[i].partenza, corse[i].destinazione, &corse[i].data.aaaa, &corse[i].data.gg, &corse[i].data.mm, &corse[i].ora_partenza.hh, &corse[i].ora_partenza.mm, &corse[i].ora_partenza.ss, &corse[i].ora_arrivo.hh, &corse[i].ora_arrivo.mm, &corse[i].ora_arrivo.ss, &corse[i].ritardo);
    }
    fclose(f);
    
    // Comando possibili
    printf("Comandi possibili:\n");
    printf(" - stampa_log\n");
    printf(" - o_data\n");
    printf(" - o_codice\n");
    printf(" - o_partenze\n");
    printf(" - o_arrivo\n");
    printf(" - ric_part\n");
    printf(" - fine\n\n");
    
    // Legge in loop i comandi e processa fino a che non viene richiesto r_fine
    while(flag){
        com = leggiComando();
        
        if(com == fine){
            flag = 0;
        }
        else{
            selezionaDati(com, corse, nr, &chiave);
        }
    }
    
    return 0;
}
