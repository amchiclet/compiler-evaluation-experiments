#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int col_dim;
typedef struct
{
    int row_dim;
    int col_dim;
    double *data;
    double **cols;
} matrix;
typedef matrix * Matrix;
extern Matrix restrict A;
extern int row_dim;

void loop()
{
#pragma scop

    for(i = 0; i < col_dim; i++)
    {
        A -> cols[i] = A -> data + i * row_dim;
    }

#pragma endscop
}
