#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern float  X[32000] ;
extern float  Y[32000] ;
extern float  Z[32000] ;
extern float  U[32000] ;
extern float  V[32000] ;

void loop()
{
#pragma scop

    for(int i = 0; i < 32000; i++)
    {
        X[i] =(1 + i);
        Y[i] =(2 + i);
        Z[i] =(3 + i);
        U[i] =(4 + i);
        V[i] =(5 + i);
    }

#pragma endscop
}
