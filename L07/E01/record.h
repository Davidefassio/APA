#ifndef RECORD_H
#define RECORD_H

#include <stdlib.h>
#include <stdio.h>

typedef struct{
    int **data;
    int capacity;
    int length;
    int datalen;
}Record;

// Inizializza un Record
Record* initRec(int n){
    Record *tmp = (Record*) malloc(sizeof(Record));
    tmp->data = (int**) malloc(sizeof(int*));
    tmp->capacity = 1;
    tmp->length = 0;
    tmp->datalen = n;
    return tmp;
}

// Aggiunge una vertex cover al Record
void push(Record *r, int *a){
    int i;
    if(r->length < r->capacity){
        r->data[r->length] = (int*) malloc(r->datalen * sizeof(int));
        for(i = 0; i < r->datalen; ++i)
            r->data[r->length][i] = a[i];
        ++r->length;
    }
    else{
        r->capacity *= 2;
        r->data = (int**) realloc(r->data, r->capacity * sizeof(int**));
        r->data[r->length] = (int*) malloc(r->datalen * sizeof(int));
        for(i = 0; i < r->datalen; ++i)
            r->data[r->length][i] = a[i];
        ++r->length;
    }
}

// Controlla se una cover e' gia presenta nel Record
int search(Record *r, int *a){
    int i, j, flag;

    for(i = 0; i < r->length; ++i){
        flag = 0;
        for(j = 0; j < r->datalen && !flag; ++j)
            if(r->data[i][j] != a[j])
                flag = 1;
        if(!flag)
            return 1;
    }
    return 0;
}

// Stampa il Record su file (stdout per stampa a video)
void print(Record *r, FILE *f){
    int i, j;
    for(i = 0; i < r->length; ++i){
        for(j = 0; j < r->datalen; ++j)
            if(r->data[i][j] == 1)
                fprintf(f, "%d ", j);
        fprintf(f, "\n");
    }
    fprintf(f, "\n");
}


#endif /* RECORD_H */
