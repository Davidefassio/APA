#include "tab_simb.h"

struct tab{
    char **data;
    int cap;
    int n;
    int len;
};

TS TS_init(int cap, int len){
    int i;

    TS tmp = (TS) malloc(sizeof(struct tab));
    tmp->cap = cap;
    tmp->n = 0;
    tmp->len = len;
    tmp->data = (char**) malloc(tmp->cap * sizeof(char*));
    for(i = 0; i < tmp->cap; ++i){
        tmp->data[i] = (char*) malloc(tmp->len * sizeof(char));
        tmp->data[i][0] = '\0';
    }
    return tmp;
}

int TS_insert(TS ts, char *str){
    int i;
    for(i = 0; i < ts->n; ++i)
        if(strncmp(ts->data[i], str, ts->len) == 0)
            return 1; // Elemento gia presente

    if(ts->n < ts->cap){
        strncpy(ts->data[(ts->n)++], str, ts->len);
        return 0; // Successo
    }
    return -1; // Tabella piena
}

char* TS_getNameByIndex(TS ts, int id){
    return ts->data[id];
}

int TS_getIndexByName(TS ts, char *str){
    int i;
    for(i = 0; i < ts->n; ++i)
        if(strncmp(ts->data[i], str, ts->len) == 0)
            return i; // Trovato
    return -1; // NON trovato
}

void TS_free(TS ts){
    int i;
    for(i = 0; i < ts->cap; ++i)
        free(ts->data[i]);
    free(ts->data);
    free(ts);
}
