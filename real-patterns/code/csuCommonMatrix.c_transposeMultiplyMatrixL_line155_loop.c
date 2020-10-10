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
extern Matrix restrict P;

void loop()
{
#pragma scop

    for(j = 0; j < B -> col_dim; j++)
    {
        for(i = 0; i < A -> col_dim; i++)
        {
            P -> cols[j][i] = 0;
        }
    }

#pragma endscop
}
