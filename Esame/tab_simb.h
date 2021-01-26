#ifndef TAB_SIMB_H_INCLUDED
#define TAB_SIMB_H_INCLUDED

#include <stdlib.h>
#include <string.h>

typedef struct tab* TS;

TS TS_init(int, int);
int TS_push(TS, char*);
char* TS_getName(TS, int);
int TS_getIndex(TS, char*);
void TS_free(TS);

#endif // TAB_SIMB_H_INCLUDED
