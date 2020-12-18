#include "pg.h"

int pg_read(FILE *fp, pg_t *pgp){
    if(fscanf(fp, "%s %s %s", pgp->cod, pgp->nome, pgp->classe) != 3)
        return 0;
    if(stat_read(fp, &pgp->b_stat) == 0) return 0;
    pgp->equip = equipArray_init();
    pgp->eq_stat.hp = pgp->eq_stat.mp = pgp->eq_stat.atk = pgp->eq_stat.def = pgp->eq_stat.mag = pgp->eq_stat.spr = 0;
    return 1;
}

void pg_clean(pg_t *pgp){
    equipArray_free(pgp->equip);
}

void pg_print(FILE *fp, pg_t *pgp, invArray_t invArray){
    stat_t tmp = {pgp->b_stat.hp + pgp->eq_stat.hp, pgp->b_stat.mp + pgp->eq_stat.mp, pgp->b_stat.atk + pgp->eq_stat.atk, pgp->b_stat.def + pgp->eq_stat.def, pgp->b_stat.mag + pgp->eq_stat.mag, pgp->b_stat.spr + pgp->eq_stat.spr};
    
    fprintf(fp, "%s %s %s ", pgp->cod, pgp->nome, pgp->classe);
    stat_print(fp, &tmp, 1);
    fprintf(fp, "\n");
}

void pg_updateEquip(pg_t *pgp, invArray_t invArray){
    stat_t tmp = equipArray_update(pgp->equip, invArray);
    
    pgp->eq_stat.hp += tmp.hp; pgp->eq_stat.mp += tmp.mp;
    pgp->eq_stat.atk += tmp.atk; pgp->eq_stat.def += tmp.def;
    pgp->eq_stat.mag += tmp.mag; pgp->eq_stat.spr += tmp.spr;
}
