/*
    Libreria per una tabella di simboli rappresentata come quasi-ADT.
*/

#ifndef TABELLA_SIMBOLI_H_INCLUDED
#define TABELLA_SIMBOLI_H_INCLUDED

// Definisco struttura dati
typedef struct{
    char **data;
    int len;
    int cap;
}TS;

// Prototipi funzioni
TS* TS_init();
void TS_push(TS*, char*);
int TS_deleteByIndex(TS*, int);
int TS_deleteByName(TS*, char*);
char* TS_getNameByIndex(TS*, int);
int TS_getIndexByName(TS*, char*);
void TS_shrinkToFit(TS*);
void TS_free(TS*);

#endif // TABELLA_SIMBOLI_H_INCLUDED
