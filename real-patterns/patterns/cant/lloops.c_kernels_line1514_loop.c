#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern long k;
extern long Inner_loops;
extern double  X[1001] ;
extern long M24;

void loop()
{
#pragma scop

    for(k = 1; k < Inner_loops; k++)
    {
        if(X[k] < X[M24]) M24 = k;
    }

#pragma endscop
}
