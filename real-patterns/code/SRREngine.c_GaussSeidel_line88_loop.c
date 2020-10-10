#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern double * restrict X;
extern double * restrict Y;
extern int j;
extern double  A[4 * 4][4 * 4] ;

void loop()
{
#pragma scop

    for(i = 0; i < 4 * 4; i++)
    {
        X[i] = Y[i];
        for(j = 0; j < 4 * 4; j++) if(j != i) X[i] = X[i] - A[i][j] * X[j];
    }

#pragma endscop
}
