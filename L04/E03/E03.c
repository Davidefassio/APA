#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

char* cercaRegexp(char *src, char *regexp){
    int i, j, creg = 0, flag;
    char *ptr = NULL;
    
    for(i = 0; src[i] != '\0'; ++i){
        ptr = src + i;
        creg = 0;
        j = i;
        while(ptr != NULL){
            switch (regexp[creg]) {
                case 46: // Punto '.'
                    ++creg;
                    break;

                case 91: // Aperta quadra '['
                    flag = 0;
                    if(regexp[++creg] == 94){ // Caso con '^'
                        ++creg;
                        while(regexp[creg] != 93){
                            if(src[j] == regexp[creg]){
                                flag = 1;
                                break;
                            }
                            ++creg;
                        }
                        if(flag){ ptr = NULL; }
                    }
                    else{
                        // Finisco il ciclo per allineare la ]
                        while(regexp[creg] != 93){
                            if(src[j] == regexp[creg]){ flag = 1; }
                            ++creg;
                        }
                        if(!flag){ ptr = NULL; }
                    }
                    ++creg;
                    break;

                case 92: // Backslash '\'
                    if(regexp[++creg] == 'a'){
                        if(islower(src[j])){ ++creg; }
                        else{ ptr = NULL; }
                    }
                    else{
                        if(isupper(src[j])){ ++creg; }
                        else{ ptr = NULL; }
                    }
                    break;

                default: // Tutte le lettere
                    if(src[j] == regexp[creg]){ ++creg; }
                    else{ ptr = NULL; }
                    break;
            }
            
            if(regexp[creg] == '\0' && ptr != NULL){
                return ptr;
            }
            ++j;
        }
    }
    return NULL;
}

int main(int argc, char *argv[]){
    char src[200];
    char regex[50];
    char *res;
    
    while(1){
        printf("Inserire stringa sorgente: ");
        scanf("%s", src);
        printf("Inserire stringa da ricercare: ");
        scanf("%s", regex);
        
        res = cercaRegexp(src, regex);
        if(res == NULL){
            printf("Regex not found\n\n");
        }
        else{
            printf("Indice: %ld\n\n", res - src);
        }
    }
    return 0;
}
