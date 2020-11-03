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

void swap(Corsa *c1, Corsa *c2){
    Corsa tmp = *c1;
    *c1 = *c2;
    *c2 = tmp;
}

// Implementazione del selection sort che permette il passaggio
// di varie funzioni di confronto.
void selectionsort(Corsa *cor, int l, int (*cmp)(Corsa, Corsa)){
    int i, j, imin;
    
    for(i = 0; i < l - 1; ++i){
        imin = i;
        
        for(j = i + 1; j < l; ++j)
            if(cmp(cor[j], cor[imin]) < 0)  // cor[j] < cor[imin]
                imin = j;
        
        if(i != imin)
            swap(cor + imin, cor + i);
    }
}

// Stampa su file i log
void stampa(Corsa *cor, int l, FILE *fp){ 
    int i;
    for(i = 0; i < l; ++i){
        fprintf(fp, "%s %s %s %d/%d/%d %d:%d:%d %d:%d:%d %d\n", cor[i].codice_tratta, cor[i].partenza, cor[i].destinazione, cor[i].data.aaaa, cor[i].data.gg, cor[i].data.mm, cor[i].ora_partenza.hh, cor[i].ora_partenza.mm, cor[i].ora_partenza.ss, cor[i].ora_arrivo.hh, cor[i].ora_arrivo.mm, cor[i].ora_arrivo.ss, cor[i].ritardo);
    }
}

// Ricerca lineare
void ric_lineare(Corsa *cor, int l, char *part){
	int i;
	for(i = 0; i < l; ++i){
		if(strncmp(cor[i].partenza, part, strlen(part)) == 0){
			stampa(cor + i, 1, stdout);
		}
	}
}

// Ricerca dicotomica
void ric_binaria(Corsa *cor, int l, int r, char *part){
    if(r < l) return;
    
    int m = (l + r) / 2;
    int len = strlen(part);
    int diff = strncmp(part, cor[m].partenza, len);
    
    if(diff < 0)
        ric_binaria(cor, l, m-1, part);
    else if(diff > 0)
        ric_binaria(cor, m+1, r, part);
    else{
        int el, er;
        for(el = m-1; el >= l; --el)
            if(strncmp(cor[el].partenza, part, len) != 0)
                break;
        for(er = m+1; el <= r; ++er)
            if(strncmp(cor[er].partenza, part, len) != 0)
                break;
        ++el;
        stampa(cor + el, er - el, stdout);
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
            FILE *fp;
            printf("Inserire nome del file di output (stampa a video = stdout): ");
            scanf("%s", nome_file);
            if(strcmp(nome_file, "stdout") == 0)
                stampa(cor, l, stdout);
            else{
                fp = fopen(nome_file, "w");
                if(fp == NULL) exit(EXIT_FAILURE);
                
                stampa(cor, l, fp);
            }
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
            
            if(*chiave == 1){ // Ricerca dicotomica
                ric_binaria(cor, 0, l-1, codice);
            }
            else{ // Ricerca lineare
                ric_lineare(cor, l, codice);
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
        
        if(com == fine)
            flag = 0;
        else{
            selezionaDati(com, corse, nr, &chiave);
            printf("\n");
        }
    }
    
    return 0;
}
