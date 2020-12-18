#include "inv.h"

static int max(int a, int b){
    return (a > b) ? a : b;
}

int stat_read(FILE *fp, stat_t *statp){
    if(fscanf(fp, "%d %d %d %d %d %d", &statp->hp, &statp->mp, &statp->atk, &statp->def, &statp->mag, &statp->spr) == 0)
        return 0;
    return 1;
}

void stat_print(FILE *fp, stat_t *statp, int soglia){
    fprintf(fp, "%d %d %d %d %d %d", max(statp->hp, soglia), max(statp->mp, soglia), max(statp->atk, soglia), max(statp->def, soglia), max(statp->mag, soglia), max(statp->spr, soglia));
}

int inv_read(FILE *fp, inv_t *invp){
    if(fscanf(fp, "%s %s", invp->nome, invp->tipo) == 0)
        return 0;
    if(stat_read(fp, &invp->stat) == 0)
        return 0;
    return 1;
}

void inv_print(FILE *fp, inv_t *invp){
    fprintf(fp, "%s %s ", invp->nome, invp->tipo);
    stat_print(fp, &invp->stat, 1);
}


stat_t inv_getStat(inv_t *invp){
    return invp->stat;
}
