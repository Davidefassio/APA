#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXS   5
#define MAXR  20
#define MAXL 200

typedef struct{
    int cnt;
    
    struct{
        int pos;
        char word[MAXL];
    }words[10];
    
}Occurrence;

void str_tolower(char *str){
    int i;
    for(i = 0; i < strlen(str); ++i){
        str[i] = tolower(str[i]);
    }
}

int main(int argc, char *argv[]){
    FILE *f1, *f2;
    int nr, i, j, cnt = 0;
    char seq[MAXR][MAXS];
    Occurrence occ[MAXR];
    char line[MAXL+1];
    char *ptr;
    
    // Stringa che continiete tutta la punteggiatura piu lo spazio
    char punct[34] = " !#$%&'()*+,-./:;<=>?@[]^_`{|}~";
    punct[31] = 92; // Aggiungo il backslash
    punct[32] = 34; // Aggiungo le "
    punct[33] = 0;  // Terminatore di stringa
    
    f1 = fopen("sequenze.txt", "r");
    if(f1 == NULL){
        exit(EXIT_FAILURE);
    }
    
    // Leggo le sequenze e le rendo minuscole
    fscanf(f1, "%d", &nr);
    for(i = 0; i < nr; ++i){
        fscanf(f1, "%s", seq[i]);
        str_tolower(seq[i]);
        
        // Inizializzo lo struct
        occ[i].cnt = 0;
    }
    fclose(f1);
    
    f2 = fopen("testo.txt", "r");
    if(f2 == NULL){
        exit(EXIT_FAILURE);
    }
    
    while(fgets(line, MAXL+1, f2) != NULL){ // Leggo una linea
        line[strlen(line)-2] = 0; // Tolgo il carattere a capo
        
        // Divido la stringa in token delimitati dalla punteggiatura
        ptr = strtok(line, punct);
        while(ptr != NULL){
            ++cnt; // Parola trovata
            
            // Rendo la parola trovata minuscola
            str_tolower(ptr);
            
            for(i = 0; i < nr; ++i){
                // Se trovo un'istanza di seq[i] in ptr la salvo nello struct.
                if(strstr(ptr, seq[i]) != NULL){
                    if(occ[i].cnt < 10){
                        strcpy(occ[i].words[occ[i].cnt].word, ptr);
                        occ[i].words[occ[i].cnt].pos = cnt;
                        ++occ[i].cnt;
                    }
                }
            }
            
            // Passo al token successivo
            // Se non ci sono piu token punto a NULL
            // e quindi il while si ferma
            ptr = strtok(NULL, punct);
        }
    }
    fclose(f2);
    
    // Stampo lo struct delle occurrenze
    for(i = 0; i < nr; ++i){
        if(occ[i].cnt != 0){
            printf("%s: %s (%d)", seq[i], occ[i].words[0].word, occ[i].words[0].pos);
            for(j = 1; j < occ[i].cnt; ++j){
                printf(", %s (%d)", occ[i].words[j].word, occ[i].words[j].pos);
            }
            printf("\n");
        }
    }
    
    return 0;
}
