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
        tmp->varchi[tmp->narchi].p = k;

        // Incremento il numero di archi
        ++(tmp->narchi);
    }

    // Libero memoria in eccesso al vettore di archi
    tmp->varchi = realloc(tmp->varchi, tmp->narchi * sizeof(edge));

    return tmp;
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
        // printf("Row: %d, Pos: %d, Num: %d\n", *r, i, c);
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

static void dfsR(){ // Depth first search
    // TODO
}

static int isDAG(Grafo grf){ // Implementazione dell'agoritmo di Kosaraju
    // TODO
    dfsR();
    return 0;
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

        M_print(comb); // DEBUG

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
            printf("%d) ", i+1);
            sum = 0;
            for(k = 0; k < comb->cols; ++k){
                printf("(%s, %s) ", TS_getNameByIndex(grf->ts, grf->varchi[comb->data[valid[i]][k]].u), TS_getNameByIndex(grf->ts, grf->varchi[comb->data[valid[i]][k]].v));
                sum += grf->varchi[comb->data[valid[i]][k]].p;
            }
            printf(". Peso = %d\n", sum);

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

/// ==========================================================================

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
