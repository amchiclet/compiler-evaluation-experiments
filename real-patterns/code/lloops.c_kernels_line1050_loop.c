#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern long k;
extern long Inner_loops;
extern double  X[1001] ;
extern double  Y[1001] ;

void loop()
{
#pragma scop

    for(k = 0; k < Inner_loops; k++)
    {
        X[k] = Y[k + 1] - Y[k];
    }

#pragma endscop
}
