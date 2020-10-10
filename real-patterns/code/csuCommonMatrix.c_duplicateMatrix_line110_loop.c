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
extern Matrix restrict mat;
extern int j;
extern Matrix restrict dup;

void loop()
{
#pragma scop

    for(i = 0; i < mat -> row_dim; i++)
    {
        for(j = 0; j < mat -> col_dim; j++)
        {
            dup -> cols[j][i] = mat -> cols[j][i];
        }
    }

#pragma endscop
}
