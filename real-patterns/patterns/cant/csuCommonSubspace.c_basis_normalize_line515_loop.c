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
extern Matrix restrict eigenvectors;
extern double sumsqr;
extern int j;
extern double inv_len;

void loop()
{
#pragma scop

    for(i = 0; i < eigenvectors -> col_dim; i++)
    {
        sumsqr = 0.0;
        for(j = 0; j < eigenvectors -> row_dim; j++) sumsqr += eigenvectors -> cols[i][j] * eigenvectors -> cols[i][j];
        if(sumsqr != 0) inv_len = 1.0 / sqrt(sumsqr);
        else inv_len = 0;
        for(j = 0; j < eigenvectors -> row_dim; j++) eigenvectors -> cols[i][j] *= inv_len;
    }

#pragma endscop
}
