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

    for(k = 1; k < Inner_loops; k++)
    {
        X[k] = X[k - 1] + Y[k];
    }

#pragma endscop
}
