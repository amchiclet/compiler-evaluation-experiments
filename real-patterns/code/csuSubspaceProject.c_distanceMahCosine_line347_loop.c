#include <inttypes.h>
#include <math.h>
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
extern Matrix restrict optVals;
extern Matrix restrict values;

void loop()
{
#pragma scop

    for(k = 0; k < optVals -> row_dim; k++)
    {
        optVals -> cols[0][k] = 1.0 / sqrt(values -> cols[0][k]);
    }

#pragma endscop
}
