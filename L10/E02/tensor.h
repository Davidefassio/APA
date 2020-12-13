#ifndef TENSOR_H_INCLUDED
#define TENSOR_H_INCLUDED

#include <stdlib.h>

typedef struct{
    int *****ten;
    int *dim;
}Tensor5d;

Tensor5d TensorInit(int d1, int d2, int d3, int d4, int d5){
    int a, b, c, d;

    Tensor5d tmp;

    tmp.dim = (int*) malloc(5 * sizeof(int));
    tmp.dim[0] = d1;
    tmp.dim[1] = d2;
    tmp.dim[2] = d3;
    tmp.dim[3] = d4;
    tmp.dim[4] = d5;

    tmp.ten = (int*****) malloc(d1 * sizeof(int****));
    for(a = 0; a < d1; ++a){
        tmp.ten[a] = (int****) malloc(d2 * sizeof(int***));
        for(b = 0; b < d2; ++b){
            tmp.ten[a][b] = (int***) malloc(d3 * sizeof(int**));
            for(c = 0; c < d3; ++c){
                tmp.ten[a][b][c] = (int**) malloc(d4 * sizeof(int*));
                for(d = 0; d < d4; ++d){
                    tmp.ten[a][b][c][d] = (int*) malloc(d5 * sizeof(int));
                }
            }
        }
    }

    return tmp;
}

void TensorRealloc(Tensor5d t, int d1, int d2, int d3, int d4, int d5){
    int a, b, c, d;

    t.dim[0] = d1;
    t.dim[1] = d2;
    t.dim[2] = d3;
    t.dim[3] = d4;
    t.dim[4] = d5;

    t.ten = (int*****) realloc(t.ten, d1 * sizeof(int****));
    for(a = 0; a < d1; ++a){
        t.ten[a] = (int****) realloc(t.ten[a], d2 * sizeof(int***));
        for(b = 0; b < d2; ++b){
            t.ten[a][b] = (int***) realloc(t.ten[a][b], d3 * sizeof(int**));
            for(c = 0; c < d3; ++c){
                t.ten[a][b][c] = (int**) realloc(t.ten[a][b][c], d4 * sizeof(int*));
                for(d = 0; d < d4; ++d){
                    t.ten[a][b][c][d] = (int*) realloc(t.ten[a][b][c][d], d5 * sizeof(int));
                }
            }
        }
    }
}

void TensorSet(Tensor5d t, int a, int b, int c, int d, int e, int val){
    t.ten[a][b][c][d][e] = val;
}

int TensorGet(Tensor5d t, int a, int b, int c, int d, int e){
    return t.ten[a][b][c][d][e];
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
