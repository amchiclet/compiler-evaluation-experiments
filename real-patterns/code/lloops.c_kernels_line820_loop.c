#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern long k;
extern long Inner_loops;
extern double  Xtra[40] ;
extern double  Z[1001] ;
extern double  X[1001] ;

void loop()
{
#pragma scop

    for(k = 0; k < Inner_loops; k++)
    {
        Xtra[28] += Z[k] * X[k];
    }

#pragma endscop
}
