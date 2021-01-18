#ifndef DATA_H_INCLUDED
#define DATA_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

typedef struct{
    int pp; // Primi = minuti
    int hh; // Ore
    int gg; // Giorni
    int mm; // Mesi
    int aa; // Anni
}Data;

// Prototipi
int data_fscan(FILE*, Data*); // Acquisisci data da file
void data_fprint(FILE*, Data); // Stampa data su file
int data_cmp(Data, Data);
Data data_getMin();
Data data_getMax();

#endif // DATA_H_INCLUDED
