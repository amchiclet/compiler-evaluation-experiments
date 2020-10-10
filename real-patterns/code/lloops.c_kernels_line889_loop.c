#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern long i;
extern long Inner_loops;
extern double  W[1001] ;
extern long k;
extern double  B[64][64] ;

void loop()
{
#pragma scop

    for(i = 1; i < Inner_loops; i++)
    {
        W[i] = 0.01;
        for(k = 0; k < i; k++)
        {
            W[i] += B[k][i] * W[i - k - 1];
        }
    }

#pragma endscop
}
