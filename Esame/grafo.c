#include "grafo.h"

struct grf{
    Lista *ladj; // Vettore di liste
    int nnodi;  // Numero di nodi nel grafo
    int **vert; // Matrice [nnodi * 3] in cui per ogni nodo salvo (profondita, tesoro, oro)
    TS ts;      // Tabella di simboli
};

Graph GRAPHload(FILE *fp){
    int i, k;
    char str[MAXL], str2[MAXL];

    Graph g = malloc(sizeof(struct grf));

    // Acquisisco numero di nodi
    fscanf(fp, "%d", &g->nnodi);

    // Inizializzo liste delle adiacenze
    g->ladj = (Lista*) malloc(g->nnodi * sizeof(Lista));
    for(i = 0; i < g->nnodi; ++i)
        g->ladj[i] = Lista_init();

    // Inizializzo vettore dei nodi
    g->vert = (int**) malloc(g->nnodi * sizeof(int*));
    for(i = 0; i < g->nnodi; ++i)
        g->vert[i] = (int*) malloc(3 * sizeof(int));

    // Inizializzo e riempo tabella di simboli
    g->ts = TS_init(g->nnodi, MAXL);
    for(i = 0; i < g->nnodi; ++i){
        fscanf(fp, "%s %d %d %d", str, &g->vert[i][0], &g->vert[i][1], &g->vert[i][2]);
        TS_push(g->ts, str);
    }

    // Riempo liste delle adiacenze, grafo non orientato
    while(fscanf(fp,"%s %s %d", str, str2, &k) == 3){
        Lista_push(g->ladj[TS_getIndex(g->ts, str)], TS_getIndex(g->ts, str2), -1*k);
        Lista_push(g->ladj[TS_getIndex(g->ts, str2)], TS_getIndex(g->ts, str), -1*k);
    }

    return g;
}

PATH GRAPHpathLoad(Graph g, FILE *fp){
    int i;
    char str[MAXL];

    PATH p = (PATH) malloc(sizeof(struct path));

    fscanf(fp, "%d", &p->len); // Il file mi da la lunghezza del path

    printf("%d\n", p->len);

    p->vert = (int*) malloc(p->len * sizeof(int));

    i = 0;
    while(fscanf(fp, "%s", str) == 1)
        p->vert[i++] = TS_getIndex(g->ts, str);

    return p;
}

int GRAPHpathCheck(Graph g, PATH p, int M, int PF){
    if(p->vert[0] != 0) return 0; // DEVE entrare nel labirinto!
    if(p->len > M) return 0; // Non puo fare piu passi di M

    int i, u, v, val = 0, maxtes = -1;
    int *oro = (int*) calloc(g->nnodi, sizeof(int));

    for(i = 1; i < p->len; ++i){
        if(PF == 0) return 0; // Sei morto non puoi continuare

        u = p->vert[i-1];
        v = p->vert[i];

        if(Lista_search(g->ladj[u], v) == 0) // Ricerca fallita
            return 0;

        PF += Lista_getVal(g->ladj[u], v); // -1 se c'è una trappola, 0 altrimenti

        if(maxtes < g->vert[v][1])
            maxtes = g->vert[v][1];

        if(oro[v] == 0){
            val += g->vert[v][2];
            oro[v] = 1;
        }
    }

    if(p->len != M && PF != 0 && p->vert[i-1] != 0) return 0;

    p->pf = PF;
    p->val = val;
    p->prstes = 0;

    if(maxtes != -1){
        p->prstes = 1;
        p->val += maxtes;
    }

    free(oro);

    return 1;
}

static PATH GRAPHpathBestR(Graph g, int M, int PF, PATH sol, PATH tmp, int *oro, int i, int tes){
    if((i > 1 && tmp->vert[i-1] == 0) || tmp->pf <= 0 || i >= M){
        if(g->vert[tmp->vert[i]][0] == 1)
            tmp->val *= 2/3;
        if(g->vert[tmp->vert[i]][0] == 2)
            tmp->val *= 1/2;
        if(g->vert[tmp->vert[i]][0] > 2)
            tmp->val = 0;

        if(tes == -1){
            tmp->prstes = 0;
        }
        else{
            tmp->prstes = 1;
            tmp->val += tes;
        }

        if(tmp->val > sol->val){
            sol->val = tmp->val;
            sol->len = tmp->len;
            sol->prstes = tmp->prstes;
            sol->pf = tmp->pf;
            memcpy(sol->vert, tmp->vert, tmp->len * sizeof(int));
        }

        return sol;
    }

    int u, c, k, flag;

    // Traverso la lista dei nodi adiacenti
    link ptr = Lista_getHead(g->ladj[tmp->vert[i]]);
    for(; ptr != NULL; ptr = Node_getNext(ptr)){
        u = Node_getId(ptr);
        c = Node_getVal(ptr);
        flag = 0;

        // Modifico i valori
        tmp->vert[i+1] = u;
        tmp->pf += c;
        (tmp->len)++;
        if(oro[u] == 0){
            flag = 1;
            tmp->val += g->vert[u][2];
        }
        if(tes < g->vert[u][1])
            k = g->vert[i][1];
        else
            k = tes;

        // Ricorro
        GRAPHpathBestR(g, M, PF, sol, tmp, oro, i+1, k);

        // Backtrack
        if(flag == 1)
            oro[u] = 0;
        --(tmp->len);
        tmp->pf -= c;
        tmp->vert[i+1] = 0;
    }

    return sol;
}

PATH GRAPHpathBest(Graph g, int M, int PF){
    PATH sol = (PATH) malloc(sizeof(struct path));
    PATH tmp = (PATH) malloc(sizeof(struct path));
    sol->vert = (int*) malloc(M * sizeof(int));
    tmp->vert = (int*) malloc(M * sizeof(int));

    sol->len = 0;
    sol->val = -1;

    tmp->vert[0] = 0;
    tmp->len = 0;
    tmp->val = 0;
    tmp->pf = PF;

    int *oro = (int*) calloc(g->nnodi, sizeof(int));

    GRAPHpathBestR(g, M, PF, sol, tmp, oro, 0, -1);

    PATH_free(tmp);
    free(oro);

    return sol;
}

void GRAPH_free(Graph g){
    int i;
    for(i = 0; i < g->nnodi; ++i){
        Lista_free(g->ladj[i]);
        free(g->vert[i]);
    }
    free(g->ladj);
    free(g->vert);
    TS_free(g->ts);
    free(g);
}

void PATH_free(PATH p){
    free(p->vert);
    free(p);
}



