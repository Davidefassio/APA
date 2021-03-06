#ifndef STOCK_H_INCLUDED
#define STOCK_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "dailyquotBST.h"

#define MAXL 21

typedef struct stock* Stock;

Stock Stock_init();
char* Stock_getCode(Stock);
BST Stock_getBST(Stock);
int Stock_cmp_cod(Stock, Stock);
int Stock_fscan(FILE*, Stock);
void Stock_fprint(FILE*, Stock);
void Stock_free(Stock);

#endif // STOCK_H_INCLUDED
