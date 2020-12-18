#include "invArray.h"

struct invArray_s{
    inv_t *vettInv;
    int nInv; // Lunghezza
    int maxInv; // Capacita
};

invArray_t invArray_init(){
    invArray_t tmp = (invArray_t) malloc(sizeof(struct invArray_s));
    if(tmp == NULL) exit(EXIT_FAILURE);
    tmp->nInv = 0;
    tmp->maxInv = 1;
    tmp->vettInv = (inv_t*) malloc(sizeof(inv_t));
    if(tmp->vettInv == NULL) exit(EXIT_FAILURE);
    return tmp;
}

void invArray_free(invArray_t invArray){
    free(invArray->vettInv);
    free(invArray);
}

void invArray_read(FILE *fp, invArray_t invArray){
    if(feof(fp)) return;
    
    int n;
    fscanf(fp, "%d", &n);
    
    inv_t tmp;
    int i;
    for(i = 0; i < n; ++i){
        if(inv_read(fp, &tmp) == 0)
            break;
        if(i >= invArray->maxInv){
            invArray->maxInv *= 2;
            invArray->vettInv = (inv_t*) realloc(invArray->vettInv, invArray->maxInv * sizeof(inv_t));
            if(invArray->vettInv == NULL) exit(EXIT_FAILURE);
        }
        invArray->vettInv[(invArray->nInv)++] = tmp;
    }
    // Libero la memoria in eccesso
    invArray->maxInv = n;
    invArray->vettInv = (inv_t*) realloc(invArray->vettInv, invArray->maxInv * sizeof(inv_t));
}

void invArray_print(FILE *fp, invArray_t invArray){
    int i;
    for(i = 0; i < invArray->nInv; ++i){
        inv_print(fp, &invArray->vettInv[i]);
        fprintf(fp, "\n");
    }
}

void invArray_printByIndex(FILE *fp, invArray_t invArray, int index){
    inv_print(fp, &invArray->vettInv[index]);
}

inv_t *invArray_getByIndex(invArray_t invArray, int index){
    return &invArray->vettInv[index];
}

int invArray_searchByName(invArray_t invArray, char *name){
    int i;
    for(i = 0; i < invArray->nInv; ++i)
        if(strcmp(invArray->vettInv[i].nome, name) == 0)
            return i;
    return -1;
}

