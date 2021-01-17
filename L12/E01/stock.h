#ifndef STOCK_H_INCLUDED
#define STOCK_H_INCLUDED

typedef struct stock* Stock;

Stock Stock_init();
char* Stock_getCode(Stock);
int Stock_cmp_cod(Stock, Stock);
Stock Stock_ItemVoid();
void Stock_free(Stock);

#endif // STOCK_H_INCLUDED
