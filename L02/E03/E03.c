#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXR  20
#define MAXS   5
#define MAXL 200

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
    char line[MAXL+1];
    char *ptr;

    // Stringa che continiete tutta la punteggiatura piu lo spazio
    char punct[34] = " !#$%&'()*+,-./:;<=>?@[]^_`{|}~";
    punct[31] = 92; // Aggiungo il backslash
    punct[32] = 34; // Aggiungo le "
    punct[33] = 0; // Terminatore di stringa

    f1 = fopen("sequenze.txt", "r");
    if(f1 == NULL){
        exit(EXIT_FAILURE);
    }

    // Leggo le sequenze e le rendo minuscole
    fscanf(f1, "%d", &nr);
    for(i = 0; i < nr; ++i){
        fscanf(f1, "%s", seq[i]);
        str_tolower(seq[i]);
    }
    fclose(f1);

    f2 = fopen("testo.txt", "r");
    if(f2 == NULL){
        exit(EXIT_FAILURE);
    }

    while(fgets(line, MAXL+1, f2) != NULL){ // Leggo una linea
        line[strlen(line)-1] = 0; // Tolgo il carattere a capo

        // Divido la stringa in token delimitati dalla puteggiatura
        ptr = strtok(line, punct);
        while(ptr != NULL){
            ++cnt; // Parola trovata

            // Rendo la parola trovata minuscola
            str_tolower(ptr);

            for(i = 0; i < nr; ++i){
                // Se trovo un'istanza di seq[i] in ptr stampo.
                if(strstr(ptr, seq[i]) != NULL){
                    printf("'%s' in '%s' alla posizione: %d.\n", seq[i], ptr, cnt);
                }
            }

            // Passo al token successivo
            // Se non ci sono piu token punto a NULL
            // e quindi il while si ferma
            ptr = strtok(NULL, punct);
        }
    }
    fclose(f2);

    return 0;
}
