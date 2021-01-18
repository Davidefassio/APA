#ifndef DAILYQUOT_H_INCLUDED
#define DAILYQUOT_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include "data.h"

typedef struct{
    Data day;
    float value;
    int numb;
}Trans;

typedef struct{
    Data day;
    float avg;
    int ntrans;
}DailyQuot;

int Trans_fscan(FILE*, Trans*);
void DQ_addTrans(DailyQuot*, Trans);
DailyQuot DQ_ItemSetVoid();

#endif // DAILYQUOT_H_INCLUDED
