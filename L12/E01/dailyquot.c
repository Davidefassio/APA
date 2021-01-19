#include "dailyquot.h"

int Trans_fscan(FILE *fp, Trans *t){
    return data_fscan(fp, &t->day) + fscanf(fp, "%f %d", &t->value, &t->numb);
}

void DQ_fprint(FILE *fp, DailyQuot dq){
    data_fprint(fp, dq.day);
    fprintf(fp, "Media: %f, #transazioni: %d\n", dq.avg, dq.ntrans);
}

void DQ_addTrans(DailyQuot *dq, Trans t){
    if(data_cmp(dq->day, t.day) != 0) return; // Date diverse
    dq->avg = ((dq->avg * dq->ntrans) + (t.value * t.numb)) / (dq->ntrans + t.numb);
    dq->ntrans += t.numb;
}

DailyQuot* DQ_ItemSetVoid(){
    DailyQuot *dq = (DailyQuot*) malloc(sizeof(DailyQuot));
    dq->avg = 0.0;
    dq->ntrans = dq->day.aa = dq->day.mm = dq->day.gg = dq->day.hh = dq->day.pp = 0;
    return dq;
}
