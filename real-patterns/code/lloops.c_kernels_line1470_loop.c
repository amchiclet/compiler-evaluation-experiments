#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
extern long k;
extern long Inner_loops;
extern double  Y[1001] ;
extern double  U[1001] ;
extern double  V[1001] ;
extern double  W[1001] ;
extern double  X[1001] ;

void loop()
{
#pragma scop

    for(k = 0; k < Inner_loops; k++)
    {
        Y[k] = U[k] / V[k];
        W[k] = X[k] /(exp(Y[k]) - 1.0);
    }

#pragma endscop
}
