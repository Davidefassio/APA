#ifndef DAILYQUOTBST_H_INCLUDED
#define DAILYQUOTBST_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <float.h>
#include "dailyquot.h"

typedef struct dqBST* BST;

BST BST_init();
void BST_fprint(FILE*, BST);
void BST_insert(BST, DailyQuot);
DailyQuot* BST_search(BST, Data);
void BST_minmaxInterval(BST, Data, Data);
void BST_minmaxAll(BST);
void BST_balance(BST, int);
void BST_free(BST);

#endif // DAILYQUOTBST_H_INCLUDED
