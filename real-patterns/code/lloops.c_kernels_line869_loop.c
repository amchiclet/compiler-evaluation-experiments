#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern long i;
extern long Inner_loops;
extern double  X[1001] ;
extern double  Z[1001] ;
extern double  Y[1001] ;

void loop()
{
#pragma scop

    for(i = 1; i < Inner_loops; i++)
    {
        X[i] = Z[i] *(Y[i] - X[i - 1]);
    }

#pragma endscop
}
