#include "data.h"

int fscan_data(FILE *fp, Data *d){
    return fscanf(fp, "%d/%d/%d %d:%d", &d->aa, &d->mm, &d->gg, &d->hh, &d->pp);
}

void fprint_data(FILE *fp, Data d){
    fprintf(fp, "%d/%d/%d %d:%d", d.aa, d.mm, d.gg, d.hh, d.pp);
}

//  1 => d1 >  d2
//  0 => d1 == d2
// -1 => d1 <  d2
int cmp_data(Data d1, Data d2){
    if(d1.aa > d2.aa) return 1;
    if(d1.aa < d2.aa) return -1;
    if(d1.mm > d2.mm) return 1;
    if(d1.mm < d2.mm) return -1;
    if(d1.gg > d2.gg) return 1;
    if(d1.gg < d2.gg) return -1;
    if(d1.hh > d2.hh) return 1;
    if(d1.hh < d2.hh) return -1;
    if(d1.pp > d2.pp) return 1;
    if(d1.pp < d2.pp) return -1;
    return 0;
}

int cmp_void_data(const void* a, const void* b){
    return cmp_data(*((Data*)a), *((Data*)b));
}


