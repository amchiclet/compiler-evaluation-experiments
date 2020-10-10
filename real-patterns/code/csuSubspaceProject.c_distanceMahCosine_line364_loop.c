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
extern double sum;
extern Matrix restrict vj;

void loop()
{
#pragma scop

    for(k = 0; k < vi -> row_dim; k++)
    {
        sum += vi -> cols[0][k] * vj -> cols[0][k];
    }

#pragma endscop
}
