#include "grafo.h"

#define MAXL 31

struct grf{
    int **mat;      // Matrice delle adiacenze
    listArray *adj; // Lista delle adiacenze
    TS *tab;        // Tabella di simboli
    int nnodi;      // Numero di nodi
};

TS *glob_ts; // Tabella di simboli globale

Grafo GRF_initFromFile(FILE *fp){
    Grafo tmp = (Grafo) malloc(sizeof(struct grf)); // Alloca mem
    tmp->adj = NULL; // Partono non allocate
    tmp->tab = TS_init();

    int i, j, value;
    char nome1[MAXL], rete1[MAXL], nome2[MAXL], rete2[MAXL];

    while(fscanf(fp, "%s %s %s %s %d", nome1, rete1, nome2, rete2, &value) == 5){
        TS_push(tmp->tab, nome1);
        TS_push(tmp->tab, nome2);
    }
    tmp->nnodi = tmp->tab->len;

    tmp->mat = (int**) malloc(tmp->nnodi * sizeof(int*));
    for(i = 0; i < tmp->nnodi; ++i){
        tmp->mat[i] = (int*) malloc(tmp->nnodi * sizeof(int));
        for(j = 0; j < tmp->nnodi; ++j)
            tmp->mat[i][j] = -1;
    }

    rewind(fp);

    while(fscanf(fp, "%s %s %s %s %d", nome1, rete1, nome2, rete2, &value) == 5){
        i = TS_getIndexByName(tmp->tab, nome1);
        j = TS_getIndexByName(tmp->tab, nome2);
        tmp->mat[i][j] = value;
        tmp->mat[j][i] = value;
    }

    return tmp;
}

static int cmp_string(const void* a, const void* b){
    return strcmp(TS_getNameByIndex(glob_ts, *((int*) a)), TS_getNameByIndex(glob_ts, *((int*) b)));
}

void enumVertexes(Grafo grf){
    // Assegna la tabella di simboli di grf a glob_ts
    while(glob_ts != NULL); // Mutex
    glob_ts = grf->tab;

    int i, j, cnt;

    int *tmp2 = (int*) malloc(grf->nnodi * sizeof(int));
    int *tmp1 = (int*) malloc(grf->nnodi * sizeof(int));
    for(i = 0; i < grf->nnodi; ++i)
        tmp1[i] = i;
    qsort(tmp1, grf->nnodi, sizeof(int), cmp_string);

    for(i = 0; i < grf->nnodi; ++i){
        cnt = 0;
        for(j = 0; j < grf->nnodi; ++j){
            if(grf->mat[tmp1[i]][j] != -1){
                tmp2[cnt++] = j;
            }
        }
        qsort(tmp2, cnt, sizeof(int), cmp_string);

        printf("%s:\n", TS_getNameByIndex(glob_ts, tmp1[i]));
        for(j = 0; j < cnt; ++j)
            printf("\t%s (%d)\n", TS_getNameByIndex(glob_ts, tmp2[j]), grf->mat[tmp1[i]][tmp2[j]]);
    }

    glob_ts = NULL; // Release

    free(tmp1);
    free(tmp2);
}

// flag = 0 => matrice
// flag = 1 => lista
void checkAdj(Grafo grf, int flag){
    char nome[MAXL];
    int a, b, c;
    a = b = c = -1;

    // Acquisizione dati da tastiera
    while(a == -1){
        printf("Inserire nome del primo vertice: ");
        scanf("%s", nome);
        a = TS_getIndexByName(grf->tab, nome);
    }

    while(b == -1){
        printf("Inserire nome del secondo vertice: ");
        scanf("%s", nome);
        b = TS_getIndexByName(grf->tab, nome);
    }

    while(c == -1){
        printf("Inserire nome del terzo vertice: ");
        scanf("%s", nome);
        c = TS_getIndexByName(grf->tab, nome);
    }

    if(flag == 0){ // Matrice
        if(grf->mat[a][b] > 0 && grf->mat[a][c] > 0 && grf->mat[b][c] > 0)
            printf("Sono adiacenti a coppie.\n");
        else
            printf("Non sono adiacenti a coppie.\n");
    }
    else{ // Lista
        // In caso non siano ancora state generate genera le liste di adiacenza
        generateAdjList(grf);

        if(LA_searchById(grf->adj, a, b) > 0 && LA_searchById(grf->adj, a, c) > 0 && LA_searchById(grf->adj, b, c) > 0)
            printf("Sono adiacenti a coppie.\n");
        else
            printf("Non sono adiacenti a coppie.\n");
    }
}


void generateAdjList(Grafo grf){
    if(grf->adj != NULL) return; // Gia generate

    grf->adj = LA_init(grf->nnodi);

    int i, j;
    for(i = 0; i < grf->nnodi; ++i)
        for(j = 0; j < grf->nnodi; ++j)
            LA_push(grf->adj, i, j, grf->mat[i][j]);
}

void GRF_free(Grafo grf){
    int i;
    for(i = 0; i < grf->nnodi; ++i)
        free(grf->mat[i]);
    free(grf->mat);
    LA_free(grf->adj);
    TS_free(grf->tab);
    free(grf);
}
