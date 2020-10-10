#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern float  X[32000] ;
extern float  Y[32000] ;

void loop()
{
#pragma scop

    for(int i = 0; i < 32000; i++)
    {
        X[i] = Y[i] + 1;
    }

#pragma endscop
}
