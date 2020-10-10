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
extern Matrix restrict mean;
extern int j;
extern int classStart;
extern int classEnd;

void loop()
{
#pragma scop

    for(i = 0; i < classmatrix -> row_dim; i++)
    {
        mean -> cols[0][i] = 0.0;
        for(j = classStart; j <= classEnd; j++) mean -> cols[0][i] += classmatrix -> cols[j][i];
        mean -> cols[0][i] = mean -> cols[0][i] /(classEnd - classStart + 1);
    }

#pragma endscop
}
