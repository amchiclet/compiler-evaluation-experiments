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
extern Matrix restrict sourceImages;
extern Matrix restrict extraImages;
extern int nExtrapersonal;
extern int probeIdx;
extern int galleryIdx;

void loop()
{
#pragma scop

    for(i = 0; i < sourceImages -> row_dim; i++) extraImages -> cols[nExtrapersonal][i] = sourceImages -> cols[probeIdx][i] - sourceImages -> cols[galleryIdx][i];

#pragma endscop
}
