#ifndef STOCK_H_INCLUDED
#define STOCK_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>

typedef struct stock* Stock;

Stock Stock_init();
char* Stock_getCode(Stock);
int Stock_cmp_cod(Stock, Stock);
int Stock_fscan(FILE*, Stock);
Stock Stock_ItemSetVoid();
void Stock_free(Stock);

#endif // STOCK_H_INCLUDED
