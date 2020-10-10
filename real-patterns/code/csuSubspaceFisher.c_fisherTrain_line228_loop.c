#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
typedef struct
{
    int row_dim;
    int col_dim;
    double *data;
    double **cols;
} matrix;
typedef matrix * Matrix;
extern Matrix restrict Ev;
extern Matrix restrict Siw;

void loop()
{
#pragma scop

    for(i = 0; i < Ev -> row_dim; i++) Siw -> cols[i][i] =(Ev -> cols[0][i] <= 0.0?0.0 : 1 / sqrt(Ev -> cols[0][i]));

#pragma endscop
}
