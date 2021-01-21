#ifndef TAB_SIMB_H_INCLUDED
#define TAB_SIMB_H_INCLUDED

#include <stdlib.h>
#include <string.h>

typedef struct tab* TS;

TS TS_init(int, int);
int TS_insert(TS, char*);
char* TS_getNameByIndex(TS, int);
int TS_getIndexByName(TS, char*);
void TS_free(TS);

#endif // TAB_SIMB_H_INCLUDED
