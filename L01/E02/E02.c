#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define LSUB 10  // Lunghezza massima della parola da sostituire
#define LSTR 200 // Lunghezza massima stringa acquisita da sorgente

int substitute(char* word, char* ctrl, char* sub){
    int i, j, l = (int) strlen(ctrl), cnt = 0, flag = 0;
    char tmp[200] = {0};
    
    for(i = 0; word[i+l-1] != '\0'; ++i){
        for(j = 0; j < l; ++j){
            if(word[i+j] != ctrl[j]){
                break;
            }
        }
        if(j == l){
            // Sostituisco alla stringa di controllo la stringa da sostituire
            // e vado avanti di l-1 posizioni.
            flag = 1;
            for(j = 0; sub[j] != '\0'; ++j, ++cnt){
                tmp[cnt] = sub[j];
            }
            i += l-1;
        }
        else{ // Aggiungo alla stringa temporanea il carattere
            tmp[cnt] = word[i];
            ++cnt;
        }
    }
    strcpy(tmp+cnt, word+i);  // Completo la stringa temporanea con i caratteri finali
    strcpy(word, tmp);        // Copio la stringa temporanea nella stringa di partenza
    
    return flag; // Flag: (0/false) no sostituzioni, (1/true) sostituzione.
}

int main(int argc, char* argv[]){
    FILE *s, *d, *o;
    char dict[30][2][LSUB], str[LSTR], c;
    int i, j, r;
    
    // Salvo il dizionario nella matrice di stringhe dict
    d = fopen("dizionario.txt", "r");
    fscanf(d, "%d", &r);
    for(i = 0; i < r; ++i){
        for(j = 0; j < 2; ++j){
            fscanf(d, "%s", dict[i][j]);
        }
    }
    fclose(d);
    
    s = fopen("sorgente.txt", "r");
    o = fopen("output.txt", "w");
    
    // Analizzo parola per parola il file sorgente.txt
    while(fscanf(s, "%s", str) != EOF){
        fscanf(s, "%c", &c);
        
        for(i = 0; i < r; ++i){
            if(substitute(str, dict[i][1], dict[i][0])){
                // Se trovo una possibile sostituzione stampo e esco dal ciclo
                fprintf(o, "%s ", str);
                break;
            }
        }
        if(i == r){ // No sostituzioni, stampo parola iniziale
            fprintf(o, "%s ", str);
        }
        if(c == 10){ // A capo se necessario
            fprintf(o, "\n");
        }
    }
    fclose(s);
    fclose(o);
    
    return 0;
}
