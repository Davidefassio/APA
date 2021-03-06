#include "grafo.h"

#define MAXL 31

typedef struct{
    int u; // Nodo di partenza
    int v; // Nodo di arrivo
    int p; // Peso
}edge;

struct grf{
    Lista *ladj;  // Lista delle adiacenze
    Lista *ladjt; // Lista delle adiacenze trasposta
    int nnodi;    // Numero di nodi
    int narchi;   // Numero di archi
    edge *varchi; // Vettore degli archi ((u1, v1),(u2, v2),...)
    int *ordtop;  // Ordinamento topologico
    TS ts;        // Tabella di simboli (nome <==> indice)
};

Grafo GRF_init(FILE *fp){
    int i, j, k;
    char str1[MAXL], str2[MAXL];

    // Alloco grafo
    Grafo tmp = (Grafo) malloc(sizeof(struct grf));

    tmp->ordtop = NULL; // Non e' un DAG

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
        tmp->varchi[tmp->narchi].p = k;

        // Incremento il numero di archi
        ++(tmp->narchi);
    }

    // Libero memoria in eccesso al vettore di archi
    tmp->varchi = realloc(tmp->varchi, tmp->narchi * sizeof(edge));

    return tmp;
}

int GRF_getNumVert(Grafo grf){
    return grf->nnodi;
}

/// DAGify ===================================================================

static long int compBinCoeff(int n, int k){
    if(k > n) return -1;
    if(k == n) return 1;

    long int i;
    double sol = 1.0;
    k = (n - k < k) ? n - k : k;

    for(i = 1; i <= k; ++i){
        sol *= ((n+1-i)/((double) i));
    }
    return (long int) sol;
}

// m = matrice in cui salvare le soluzioni
// r = riga della matrice
// sol = soluzione
// k = lunghezza della soluzione
// n = numeri nel range [0, n)
// i = indice
static void genCombR(Mat m, long int *r, int *sol, int k, int n, int i){
    if(i == k){
        memcpy(m->data[(*r)++], sol, k * sizeof(int));
        return;
    }

    int c, p = (i == 0) ? -1 : sol[i-1];

    for(c = p+1; c <= n - k + i; ++c){
        sol[i] = c;
        genCombR(m, r, sol, k, n, i+1);
    }
}

static Mat genComb(int n, int k){
    Mat tmp = M_init(compBinCoeff(n, k), k);
    long int *r = (long int*) calloc(1, sizeof(long int));
    int *s = (int*) calloc(k, sizeof(int));

    genCombR(tmp, r, s, k, n, 0);

    free(s);
    free(r);
    return tmp;
}

static int argmax(int *arr, int n){
    int i, max = INT_MIN, imax = -1;
    for(i = 0; i < n; ++i){
        if(arr[i] > max){
            max = arr[i];
            imax = i;
        }
    }
    return imax;
}

static int *glob_prio = NULL;
static int cmp_int(const void *p1, const void *p2){
    return glob_prio[*((int*)p1)] - glob_prio[*((int*)p2)];
}

static void dfsR(Mat pp, Grafo grf, int *prio, int *time, int id){ // Depth first search con priorita
    glob_prio = prio;

    link t;
    int *tmp = (int*) malloc(grf->nnodi * sizeof(int));
    int cnt = 0, i;

    pp->data[0][id] = (*time)++;

    for(t = L_getHead(grf->ladj[id]); t != NULL; t = Node_getNext(t)){
        if(pp->data[0][Node_getId(t)] == -1){
            tmp[cnt++] = Node_getId(t);
        }
    }

    qsort(tmp, cnt, sizeof(int), cmp_int);

    for(i = 0; i < cnt; ++i)
        if(pp->data[0][tmp[i]] == -1)
            dfsR(pp, grf, prio, time, tmp[i]);

    free(tmp);

    pp->data[1][id] = (*time)++;
}

static void dfsRT(Mat pp, Grafo grf, int *time, int id){ // Depth first search sul grafo trasposto
    link t;

    pp->data[0][id] = (*time)++;

    for(t = L_getHead(grf->ladjt[id]); t != NULL; t = Node_getNext(t))
        if(pp->data[0][Node_getId(t)] == -1)
            dfsRT(pp, grf, time, Node_getId(t));

    pp->data[1][id] = (*time)++;
}

static int isDAG(Grafo grf){ // Implementazione dell'agoritmo di Kosaraju
    int i, j;
    Mat m1, m2;
    m1 = M_init(2, grf->nnodi);
    m2 = M_init(2, grf->nnodi);

    for(i = 0; i < 2; ++i)
        for(j = 0; j < m1->cols; ++j)
            m1->data[i][j] = m2->data[i][j] = -1;

    int *tmp = (int*) malloc(grf->nnodi * sizeof(int));
    int t = 0;

    for(i = 0; i < grf->nnodi; ++i)
        if(m1->data[0][i] == -1)
            dfsRT(m1, grf, &t, i); // DFS sul grafo trasposto

    memcpy(tmp, m1->data[1], grf->nnodi * sizeof(int));
    t = 0;

    for(j = 0; j < grf->nnodi; ++j){
        i = argmax(tmp, grf->nnodi); // Trovo il vertice con valore post massimo
        tmp[i] = -1;

        if(m2->data[0][i] == -1)
            dfsR(m2, grf, m1->data[1], &t, i); // DFS sul grafo seguendo la priorita m1->data[1]
    }

    free(tmp);
    M_free(m1);

    // Se il grafo e' un DAG allora:
    // per ogni nodo vale post[n] - pre[n] == 1
    for(i = 0; i < m2->cols; ++i){
        if(m2->data[1][i] - m2->data[0][i] != 1){
            M_free(m2);
            return 0; // NON e' un DAG
        }
    }

    M_free(m2);

    return 1; // E' un DAG
}

void GRF_DAGify(Grafo grf){
    long int j;
    int i, k, flag = 0, max, imax, sum;
    int marchi = grf->narchi - grf->nnodi + 1; // Numero massimo di archi toglibili
    int *valid = NULL, nvalid = 0;
    Mat comb;
    link *nodeArr = NULL, *nodeArrT = NULL, node;

    // Applico kosaraju
    if(isDAG(grf) == 1){
        printf("E' gia un DAG.\n");
        return;
    }

    // Ciclo le combinazioni (tolgo i archi)
    for(i = 1; i <= marchi && flag == 0; ++i){
        comb = genComb(grf->narchi, i);

        // Applico kosaraju togliendo gli archi
        nodeArr = (link*) realloc(nodeArr, i * sizeof(link));
        nodeArrT = (link*) realloc(nodeArrT, i * sizeof(link));

        // Per ogni combinazione
        for(j = 0; j < comb->rows; ++j){
            // Tolgo gli archi
            for(k = 0; k < comb->cols; ++k){
                nodeArr[k] = L_extract(grf->ladj[grf->varchi[comb->data[j][k]].u], grf->varchi[comb->data[j][k]].v);
                nodeArrT[k] = L_extract(grf->ladjt[grf->varchi[comb->data[j][k]].v], grf->varchi[comb->data[j][k]].u);
            }

            // E' un DAG
            if(isDAG(grf) == 1){
                if(valid == NULL)
                    valid = (int*) calloc(comb->rows, sizeof(int));

                valid[nvalid++] = j;
                flag = 1;
            }

            // Rimetto gli archi
            for(k = 0; k < comb->cols; ++k){
                L_pushNode(grf->ladj[grf->varchi[comb->data[j][k]].u], nodeArr[k]);
                L_pushNode(grf->ladjt[grf->varchi[comb->data[j][k]].v], nodeArrT[k]);
            }
        }

        if(flag == 0)
            M_free(comb);
    }

    if(flag == 1){
        // Stampo le combinazioni valide e calcolo il peso massimo
        printf("Insiemi di archi da togliere per rendere il grafo un DAG:\n");

        max = INT_MIN;
        imax = -1;
        for(i = 0; i < nvalid; ++i){
            printf("%d) {", i+1);
            sum = 0;
            for(k = 0; k < comb->cols; ++k){
                printf("(%s, %s)", TS_getNameByIndex(grf->ts, grf->varchi[comb->data[valid[i]][k]].u), TS_getNameByIndex(grf->ts, grf->varchi[comb->data[valid[i]][k]].v));
                sum += grf->varchi[comb->data[valid[i]][k]].p;
            }
            printf("} Peso = %d\n", sum);

            if(sum > max){
                max = sum;
                imax = i;
            }
        }

        // Rimuovo la combinazione piu pesante
        printf("Rimuovo l'insieme %d.\n", imax+1);
        for(k = 0; k < comb->cols; ++k){ // Rimuovo gli archi dalle liste di adiacenza e libero la memoria
            node = L_extract(grf->ladj[grf->varchi[comb->data[valid[imax]][k]].u], grf->varchi[comb->data[valid[imax]][k]].v);
            Node_free(node);
            node = L_extract(grf->ladjt[grf->varchi[comb->data[valid[imax]][k]].v], grf->varchi[comb->data[valid[imax]][k]].u);
            Node_free(node);
        }
        for(k = 0; k < comb->cols; ++k){ // Rimuovo gli archi dal vettore di archi e decremento il numero di archi
            for(i = comb->data[valid[imax]][k]; i < grf->narchi; ++i){
                grf->varchi[i] = grf->varchi[i+1];
            }
            --(grf->narchi);
        }
    }

    // Libero cio che ho allocato
    free(nodeArr);
    free(nodeArrT);
    if(valid != NULL){
        free(valid);
        M_free(comb);
    }
}

/// Longest path =============================================================
// Presuppone che il grafo sia gia un DAG
void GRF_printLongestPath(Grafo grf, int id){
    int i, j, v, w, index;
    link ptr;

    // Calcolo l'ordinamento topologico
    if(grf->ordtop == NULL){
        grf->ordtop = (int*) malloc(grf->nnodi * sizeof(int));
        int *prio = (int*) calloc(grf->nnodi, sizeof(int));
        int t = 0, index;
        Mat pp = M_init(2, grf->nnodi);

        for(i = 0; i < 2; ++i)
            for(j = 0; j < grf->nnodi; ++j)
                pp->data[i][j] = -1;

        for(i = 0; i < grf->nnodi; ++i)
            if(pp->data[0][i] == -1)
                dfsR(pp, grf, prio, &t, i);

        for(i = 0; i < grf->nnodi; ++i){
            index = argmax(pp->data[1], pp->cols);
            grf->ordtop[i] = index;
            pp->data[1][index] = -1;
        }

        // Free
        M_free(pp);
        free(prio);
    }

    // Moltiplico per -1 i pesi degli archi
    for(i = 0; i < grf->nnodi; ++i)
        L_invertVal(grf->ladj[i]);

    // Applico l'algoritmo dei cammini minimi
    int *dist = (int*) malloc(grf->nnodi * sizeof(int));
    for(i = 0; i < grf->nnodi; ++i)
        dist[i] = INT_MAX;

    for(j = 0; j < grf->nnodi; ++j) // Trovo la j da cui partire
        if(id == grf->ordtop[j])
            break;

    dist[j] = 0;

    for(i = j; i < grf->nnodi; ++i){
        index = grf->ordtop[i];
        if(dist[i] == INT_MAX)
            continue;

        for(ptr = L_getHead(grf->ladj[index]); ptr != NULL; ptr = Node_getNext(ptr)){
            v = Node_getId(ptr);
            w = Node_getVal(ptr);
            if(dist[grf->ordtop[v]] > dist[i] + w)
                dist[grf->ordtop[v]] = dist[i] + w;
        }
    }

    // Stampo i risultati
    printf("\nCammini massimi partendo da %s:\n", TS_getNameByIndex(grf->ts, id));
    for(i = 0; i < grf->nnodi; ++i){
        printf("%s) ", TS_getNameByIndex(grf->ts, grf->ordtop[i]));

        if(dist[i] == INT_MAX)
            printf("Vertice non raggiungibile\n");
        else
            printf("%d\n", -1*dist[i]);
    }

    // Rimetto i valori a posto
    for(i = 0; i < grf->nnodi; ++i)
        L_invertVal(grf->ladj[i]);

    free(dist);
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
    
    // Libero ordinamento topologico se allocato
    if(grf->ordtop != NULL)
        free(grf->ordtop);

    // Libero tabella di simboli
    TS_free(grf->ts);

    // Libero grafo
    free(grf);

}
