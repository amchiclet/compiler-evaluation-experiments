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
extern Matrix restrict images;
extern int j;
extern Matrix restrict mean;

void loop()
{
#pragma scop

    for(i = 0; i < images -> row_dim; i++)
    {
        for(j = 0; j < images -> col_dim; j++)
        {
            images -> cols[j][i] -= mean -> cols[0][i];
        }
    }

#pragma endscop
}
