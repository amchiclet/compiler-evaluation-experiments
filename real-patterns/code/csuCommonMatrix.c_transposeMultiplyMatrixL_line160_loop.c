#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int j;
typedef struct
{
    int row_dim;
    int col_dim;
    double *data;
    double **cols;
} matrix;
typedef matrix * Matrix;
extern Matrix restrict B;
extern int i;
extern Matrix restrict A;
extern int k;
extern Matrix restrict P;

void loop()
{
#pragma scop

    for(j = 0; j < B -> col_dim; j++)
    {
        for(i = 0; i < A -> col_dim; i++)
        {
            for(k = 0; k < A -> row_dim; k++)
            {
                P -> cols[j][i] += A -> cols[i][k] * B -> cols[j][k];
            }
        }
    }

#pragma endscop
}
