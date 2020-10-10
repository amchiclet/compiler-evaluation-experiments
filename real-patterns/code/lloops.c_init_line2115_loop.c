#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern long i;
extern double  X0[1001] ;
extern double  X[1001] ;
extern double  W0[1001] ;
extern double  W[1001] ;

void loop()
{
#pragma scop

    for(i = 0; i < 1001; i++)
    {
        X0[i] = X[i];
        W0[i] = W[i];
    }

#pragma endscop
}
