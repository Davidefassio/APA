#include "grafo.h"

#define MAXL 31

typedef struct{
    int u;
    int v;
}edge;

struct grf{
    Lista *ladj;  // Lista delle adiacenze
    Lista *ladjt; // Lista delle adiacenze trasposta
    int nnodi;    // Numero di nodi
    int narchi;   // Numero di archi
    edge *varchi; // Vettore degli archi ((u1, v1),(u2, v2),...)
    TS ts;        // Tabella di simboli (nome <==> indice)
};

Grafo GRF_init(FILE *fp){
    int i, j, k;
    char str1[MAXL], str2[MAXL];

    // Alloco grafo
    Grafo tmp = (Grafo) malloc(sizeof(struct grf));

    fscanf(fp, "%d", &tmp->nnodi);
    tmp->narchi = 0;

    // Inizializzo vettore di archi (sovrallocato)
    tmp->varchi = (edge*) malloc(tmp->nnodi * (tmp->nnodi - 1) * sizeof(edge));

    // Inizializzo liste delle adiacenze
    tmp->ladj = (Lista*) malloc(tmp->nnodi * sizeof(Lista));
    tmp->ladjt = (Lista*) malloc(tmp->nnodi * sizeof(Lista));
    for(i = 0; i < tmp->nnodi; ++i){
        tmp->ladj[i] = L_init();
        tmp->ladjt[i] = L_init();
    }

    // Alloco tabella di simboli
    tmp->ts = TS_init(tmp->nnodi, MAXL);

    // Inizializzo tabella di simboli
    for(i = 0; i < tmp->nnodi; ++i){
        fscanf(fp, "%s", str1);
        TS_insert(tmp->ts, str1);
    }

    // Inizializzo liste delle adiacenze
    while(fscanf(fp, "%s %s %d", str1, str2, &k) == 3){
        // Trovo l'indice dei nodi
        i = TS_getIndexByName(tmp->ts, str1);
        j = TS_getIndexByName(tmp->ts, str2);

        // Aggiunggo l'arco alle liste di adiacenza
        L_push(tmp->ladj[i], j, k);
        L_push(tmp->ladjt[j], i, k);

        // Aggiugno l'arco al vettore di archi
        tmp->varchi[tmp->narchi].u = i;
        tmp->varchi[tmp->narchi].v = j;

        // Incremento il numero di archi
        ++(tmp->narchi);
    }

    // Libero memoria in eccesso al vettore di archi
    tmp->varchi = realloc(tmp->varchi, tmp->narchi * sizeof(edge));

    return tmp;
}

void GRF_free(Grafo grf){
    int i;

    // Libero liste di adiacenza
    for(i = 0; i < grf->nnodi; ++i){
        L_free(grf->ladj[i]);
        L_free(grf->ladjt[i]);
    }
    free(grf->ladj);
    free(grf->ladjt);

    // Libero vettore di archi
    free(grf->varchi);

    // Libero tabella di simboli
    TS_free(grf->ts);

    // Libero grafo
    free(grf);
}
