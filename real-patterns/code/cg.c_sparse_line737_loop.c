#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int nza;
extern int nnza;
extern int j;
extern int* restrict arow;
extern int firstrow;
extern int k;
extern int* restrict rowstr;
extern double* restrict a;
extern double* restrict aelt;
extern int* restrict colidx;
extern int* restrict acol;

void loop()
{
#pragma scop

    for(nza = 1; nza <= nnza; nza++)
    {
        j = arow[nza] - firstrow + 1;
        k = rowstr[j];
        a[k] = aelt[nza];
        colidx[k] = acol[nza];
        rowstr[j] = rowstr[j] + 1;
    }

#pragma endscop
}
