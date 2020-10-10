#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern long k;
extern long Inner_loops;
extern double  X[1001] ;
extern double  Xtra[40] ;
extern double  Y[1001] ;
extern double  Z[1001] ;

void loop()
{
#pragma scop

    for(k = 0; k < Inner_loops; k++)
    {
        X[k] = Xtra[28] + Y[k] *(Xtra[30] * Z[k + 10] + Xtra[36] * Z[k + 11]);
    }

#pragma endscop
}
