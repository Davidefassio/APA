#include "stock.h"

struct stock{
    char codice[MAXL];
    BST dailyquot;
};


Stock Stock_init(char *str){
    Stock tmp = (Stock) malloc(sizeof(struct stock));
    str[MAXL-1] = '\0';
    strncpy(tmp->codice, str, MAXL);
    tmp->dailyquot = BST_init();
    return tmp;
}

char* Stock_getCode(Stock s){
    return s->codice;
}

BST Stock_getBST(Stock s){
    return s->dailyquot;
}

int Stock_cmp_cod(Stock s1, Stock s2){
    return strcmp(s1->codice, s2->codice);
}

int Stock_fscan(FILE *fp, Stock s){
    if(fp == NULL) return 0;

    Trans *t = NULL;
    DailyQuot *dq = NULL;
    int n, i, tot = 0;

    tot += fscanf(fp, "%d", &n);

    for(i = 0; i < n; ++i){
        tot += Trans_fscan(fp, t);
        dq = BST_search(s->dailyquot, t->day);

        if(dq->ntrans == 0){ // Inserisci
            dq->day = t->day;
            DQ_addTrans(dq, *t);
            BST_insert(s->dailyquot, *dq);
        }
        else{
            DQ_addTrans(dq, *t);
        }
    }

    return tot;
}

void Stock_fprint(FILE *fp, Stock s){
    fprintf(fp, "Codice: %s", s->codice);
    BST_fprint(fp, s->dailyquot);
}

Stock Stock_ItemSetVoid(){
    Stock tmp = (Stock) malloc(sizeof(struct stock));
    tmp->codice[0] = '\0';
    tmp->dailyquot = NULL;
    return tmp;
}

void Stock_free(Stock s){
    BST_free(s->dailyquot);
    free(s);
}
