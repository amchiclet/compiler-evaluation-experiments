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
extern Matrix restrict classmatrix;
extern int j;
extern int classStart;
extern int classEnd;
extern Matrix restrict mean;

void loop()
{
#pragma scop

    for(i = 0; i < classmatrix -> row_dim; i++)
    {
        for(j = classStart; j <= classEnd; j++)
        {
            classmatrix -> cols[j][i] -= mean -> cols[0][i];
        }
    }

#pragma endscop
}
