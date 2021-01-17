#ifndef STOCKLIST_H_INCLUDED
#define STOCKLIST_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "stock.h"

typedef struct stockList* StockList;

StockList SL_init();
void SL_insert(StockList, Stock);
void SL_insertFromFile(StockList, FILE*); // TODO
Stock SL_search(StockList, char*);
void SL_delete(StockList, char*);
void SL_free(StockList);

#endif // STOCKLIST_H_INCLUDED
