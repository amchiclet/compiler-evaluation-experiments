#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int col1;
extern int col2;
extern int j;
typedef struct
{
    int row_dim;
    int col_dim;
    double *data;
    double **cols;
} matrix;
typedef matrix * Matrix;
extern Matrix restrict mat;
extern Matrix restrict cols;

void loop()
{
#pragma scop

    for(i = col1; i <= col2; i++)
    {
        for(j = 0; j < mat -> row_dim; j++)
        {
            cols -> cols[i - col1][j] = mat -> cols[i][j];
        }
    }

#pragma endscop
}
