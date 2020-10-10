#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern double * restrict Y;
extern double  A[4 * 4][4 * 4] ;
extern int j;

void loop()
{
#pragma scop

    for(i = 0; i < 4 * 4; i++)
    {
        Y[i] = Y[i] / A[i][i];
        for(j = 0; j < 4 * 4; j++) if(i != j) A[i][j] =((double )A[i][j]) /((double )A[i][i]);
    }

#pragma endscop
}
