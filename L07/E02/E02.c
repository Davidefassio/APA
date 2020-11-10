#include <stdlib.h>
#include <stdio.h>
#include "list.h"

int main(int argc, char *argv[]){
    char nome_file[20];

    printf("Inserire nome file: ");
    scanf("%s", nome_file);

    FILE *f = fopen(nome_file, "r");
    if(f == NULL) exit(EXIT_FAILURE);

    


    return 0;
}
