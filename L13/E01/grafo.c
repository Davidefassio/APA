#include "grafo.h"

struct grf{
    int **madj; // Matrice delle adiacenze
    int nnodi;  // Numero di nodi
    int narchi; // Numero di archi
    id *ts;     // Tabella di simboli (nome <==> indice)
};

Grafo GRF_init(FILE *fp){
    int i, j, k;
    id str1, str2;

    Grafo tmp = (Grafo) malloc(sizeof(struct grf));

    fscanf(fp, "%d", &tmp->nnodi);
    tmp->narchi = 0;

    // Alloco matrice e inizializzo a -1
    tmp->madj = (int**) malloc(tmp->nnodi * sizeof(int*));
    for(i = 0; i < tmp->nnodi; ++i){
        tmp->madj[i] = (int*) malloc(tmp->nnodi * sizeof(int));
        for(j = 0; j < tmp->nnodi; ++j){
            tmp->madj[i][j] = -1;
        }
    }

    // Alloco tabella di simboli
    tmp->ts = (id*) malloc(tmp->nnodi * sizeof(id));

    // Inizializzo tabella di simboli
    for(i = 0; i < tmp->nnodi; ++i){
        fscanf(fp, "%s", tmp->ts[i]);
    }

    // Inizializzo matrice delle adiacenze
    while(fscanf(fp, "%s %s %d", str1, str2, &k) == 3){
        i = GRF_getNodeIndex(tmp, str1);
        j = GRF_getNodeIndex(tmp, str2);
        tmp->madj[i][j] = k;
        ++(tmp->narchi);
    }

    return tmp;
}

int GRF_getNodeIndex(Grafo grf, id str){
    int i;
    for(i = 0; i < grf->nnodi; ++i)
        if(strcmp(str, grf->ts[i]) == 0)
            return i;
    return -1;
}

void GRF_free(Grafo grf){
    int i;
    for(i = 0; i < grf->nnodi; ++i)
        free(grf->madj[i]);
    free(grf->madj);
    free(grf->ts);
    free(grf);
}
