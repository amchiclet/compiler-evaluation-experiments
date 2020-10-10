#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern long k;
extern long Inner_loops;
extern double  X[1001] ;
extern double  U[1001] ;
extern double  Xtra[40] ;
extern double  Z[1001] ;
extern double  Y[1001] ;

void loop()
{
#pragma scop

    for(k = 0; k < Inner_loops; k++)
    {
        X[k] = U[k] + Xtra[30] *(Z[k] + Xtra[30] * Y[k]) + Xtra[36] *(U[k + 3] + Xtra[30] *(U[k + 2] + Xtra[30] * U[k + 1]) + Xtra[36] *(U[k + 6] + Xtra[28] *(U[k + 5] + Xtra[28] * U[k + 4])));
    }

#pragma endscop
}
