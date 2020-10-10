#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int dim;
extern int j;
typedef struct
{
    int row_dim;
    int col_dim;
    double *data;
    double **cols;
} matrix;
typedef matrix * Matrix;
extern Matrix restrict I;

void loop()
{
#pragma scop

    for(i = 0; i < dim; i++)
    {
        for(j = 0; j < dim; j++)
        {
            I -> cols[j][i] =(i == j);
        }
    }

#pragma endscop
}
