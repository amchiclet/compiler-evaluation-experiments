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
extern Matrix restrict smallVector;
extern Matrix restrict images;
extern int i;

void loop()
{
#pragma scop

    for(j = 0; j < smallVector -> row_dim; j++)
    {
        images -> cols[i][j] = smallVector -> cols[0][j];
    }

#pragma endscop
}
