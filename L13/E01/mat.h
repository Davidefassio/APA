#ifndef MAT_H_INCLUDED
#define MAT_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>

struct mat{
    int **data;
    long int rows;
    int cols;
};

typedef struct mat* Mat;

Mat M_init(long int, int);
void M_print(Mat);
void M_free(Mat);


#endif // MAT_H_INCLUDED
