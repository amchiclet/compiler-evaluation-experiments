#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int nr;
extern int j;
extern int nq;
extern int k;
extern int np;
extern double  A[150 + 0][140 + 0][160 + 0] ;

void loop()
{
#pragma scop

    for(i = 0; i < nr; i++) for(j = 0; j < nq; j++) for(k = 0; k < np; k++) A[i][j][k] =((double )((i * j + k) % np)) / np;

#pragma endscop
}
