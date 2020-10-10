#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int k;
typedef struct
{
    int row_dim;
    int col_dim;
    double *data;
    double **cols;
} matrix;
typedef matrix * Matrix;
extern Matrix restrict vi;
extern Matrix restrict ims;
extern int i;
extern Matrix restrict optVals;
extern double sum_i;
extern Matrix restrict vj;
extern int j;
extern double sum_j;

void loop()
{
#pragma scop

    for(k = 0; k < vi -> row_dim; k++)
    {
        vi -> cols[0][k] = ims -> cols[i][k] * optVals -> cols[0][k];
        sum_i += vi -> cols[0][k] * vi -> cols[0][k];
        vj -> cols[0][k] = ims -> cols[j][k] * optVals -> cols[0][k];
        sum_j += vj -> cols[0][k] * vj -> cols[0][k];
    }

#pragma endscop
}
