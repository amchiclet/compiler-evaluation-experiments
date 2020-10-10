#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern long i;
extern long Inner_loops;
extern long j;
extern double  P[512][4] ;
extern double  P0[512][4] ;

void loop()
{
#pragma scop

    for(i = 0; i < Inner_loops; i++)
    {
        for(j = 0; j < 4; j++)
        {
            P[i][j] = P0[i][j];
        }
    }

#pragma endscop
}
