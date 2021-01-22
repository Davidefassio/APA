#include "mat.h"

Mat M_init(long int r, int c){
    long int i;

    Mat tmp = (Mat) malloc(sizeof(struct mat));

    tmp->rows = r;
    tmp->cols = c;

    tmp->data = (int**) malloc(tmp->rows * sizeof(int*));
    for(i = 0; i < tmp->rows; ++i)
        tmp->data[i] = (int*) calloc(tmp->cols, sizeof(int));

    return tmp;
}

void M_print(Mat m){
    long int i, j;
    printf("###############\n"); // Da rimuovere
    printf("%ld %d\n", m->rows, m->cols);
    for(i = 0; i < m->rows; ++i){
        for(j = 0; j < m->cols; ++j){
            printf("%d ", m->data[i][j]);
        }
        printf("\n");
    }
    printf("###############\n"); // Da rimuovere
    printf("\n");
}

void M_free(Mat m){
    long int i;
    for(i = 0; i < m->rows; ++i)
        free(m->data[i]);
    free(m->data);
    free(m);
}
