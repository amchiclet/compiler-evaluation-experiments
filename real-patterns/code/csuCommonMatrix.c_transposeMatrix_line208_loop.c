#include <inttypes.h>
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
extern Matrix restrict A;
extern int j;
extern Matrix restrict T;

void loop()
{
#pragma scop

    for(i = 0; i < A -> row_dim; i++)
    {
        for(j = 0; j < A -> col_dim; j++)
        {
            T -> cols[i][j] = A -> cols[j][i];
        }
    }

#pragma endscop
}
