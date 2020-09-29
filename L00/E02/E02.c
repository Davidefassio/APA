#include <stdio.h>
#include <stdlib.h>

int conta(char S[20], int n){
    int i, j, sum = 0, voc, x;
    
    for(i = 0; S[i+n-1] != '\0'; ++i){
        voc = 0;
        for(j = 0; j < n; ++j){
            x = (int) S[i+j];
            if(x == 97 || x == 101 || x == 105 || x == 111 || x == 117 || x == 65 || x == 69 || x == 73 || x == 79 || x == 85){ ++voc; }
        }
        if(voc == 2){ ++sum; }
    }
    return sum;
}

int main(int argc, char* argv[]){
    FILE* f;
    char nome_file[20], str[20];
    int n, r, i, sum = 0;
    
    printf("Inserire nome file: ");
    scanf("%s", nome_file);
    
    f = fopen(nome_file, "r");
    if(f == NULL){ return -1; }
    
    printf("Inserire lunghezza sottostringa: ");
    scanf("%d", &n);
    
    fscanf(f, "%d", &r);
    
    for(i = 0; i < r; ++i){
        fscanf(f, "%s", str);
        sum += conta(str, n);
    }
    fclose(f);
    
    printf("Somma: %d", sum);
    return 0;
}
