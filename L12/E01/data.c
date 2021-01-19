#include "data.h"

int data_fscan(FILE *fp, Data *d){
    return fscanf(fp, "%d/%d/%d %d:%d", &d->aa, &d->mm, &d->gg, &d->hh, &d->pp);
}

void data_fprint(FILE *fp, Data d){
    fprintf(fp, "%d/%d/%d %d:%d", d.aa, d.mm, d.gg, d.hh, d.pp);
}

//  1 => d1 >  d2
//  0 => d1 == d2
// -1 => d1 <  d2
int data_cmp(Data d1, Data d2){
    if(d1.aa > d2.aa) return 1;
    if(d1.aa < d2.aa) return -1;
    if(d1.mm > d2.mm) return 1;
    if(d1.mm < d2.mm) return -1;
    if(d1.gg > d2.gg) return 1;
    if(d1.gg < d2.gg) return -1;
    /*if(d1.hh > d2.hh) return 1;
    if(d1.hh < d2.hh) return -1;
    if(d1.pp > d2.pp) return 1;
    if(d1.pp < d2.pp) return -1;*/
    return 0;
}

Data data_getMin(){
    Data tmp;
    tmp.aa = tmp.mm = tmp.gg = tmp.hh = tmp.pp = INT_MIN;
    return tmp;
}

Data data_getMax(){
    Data tmp;
    tmp.aa = tmp.mm = tmp.gg = tmp.hh = tmp.pp = INT_MAX;
    return tmp;
}


