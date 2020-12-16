#ifndef TENSOR_H_INCLUDED
#define TENSOR_H_INCLUDED

#include <stdlib.h>
#include <assert.h>

typedef struct{
    int *****ten;
    int *dim;
}Tensor5d;

Tensor5d TensorInit(int d1, int d2, int d3, int d4, int d5){
    int a, b, c, d, e;

    Tensor5d tmp;
    
    tmp.dim = (int*) malloc(5 * sizeof(int));
    tmp.dim[0] = d1;
    tmp.dim[1] = d2+1;
    tmp.dim[2] = d3+1;
    tmp.dim[3] = d4+1;
    tmp.dim[4] = d5+1;

    tmp.ten = (int*****) malloc(tmp.dim[0] * sizeof(int****));
    for(a = 0; a < tmp.dim[0]; ++a){
        tmp.ten[a] = (int****) malloc(tmp.dim[1] * sizeof(int***));
        for(b = 0; b < tmp.dim[1]; ++b){
            tmp.ten[a][b] = (int***) malloc(tmp.dim[2] * sizeof(int**));
            for(c = 0; c < tmp.dim[2]; ++c){
                tmp.ten[a][b][c] = (int**) malloc(tmp.dim[3] * sizeof(int*));
                for(d = 0; d < tmp.dim[3]; ++d){
                    tmp.ten[a][b][c][d] = (int*) malloc(tmp.dim[4] * sizeof(int));
                    for(e = 0; e < tmp.dim[4]; ++e){
                        tmp.ten[a][b][c][d][e] = -1; // Inizializzazione
                    }
                }
            }
        }
    }

    return tmp;
}

void TensorFree(Tensor5d t){
    int a, b, c, d;

    for(a = 0; a < t.dim[0]; ++a){
        for(b = 0; b < t.dim[1]; ++b){
            for(c = 0; c < t.dim[2]; ++c){
                for(d = 0; d < t.dim[3]; ++d){
                    free(t.ten[a][b][c][d]);
                }
                free(t.ten[a][b][c]);
            }
            free(t.ten[a][b]);
        }
        free(t.ten[a]);
    }
    free(t.ten);
    free(t.dim);
}

#endif // TENSOR_H_INCLUDED
