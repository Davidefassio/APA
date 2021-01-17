#ifndef DATA_H_INCLUDED
#define DATA_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>

typedef struct{
    int pp; // Primi = minuti
    int hh; // Ore
    int gg; // Giorni
    int mm; // Mesi
    int aa; // Anni
}Data;

// Prototipi
int fscan_data(FILE*, Data*); // Acquisisci data da file
void fprint_data(FILE*, Data); // Stampa data su file
int cmp_data(Data, Data);
int cmp_void_data(const void*, const void*); // Per il qsort

#endif // DATA_H_INCLUDED
