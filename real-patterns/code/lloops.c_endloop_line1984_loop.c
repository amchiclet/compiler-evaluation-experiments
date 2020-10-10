#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern long i;
extern long j;
extern long Inner_loops;
extern double  Za[7][101] ;
extern double  Za0[101][25] ;

void loop()
{
#pragma scop

    for(i = 1; i < 6; i++)
    {
        for(j = 1; j < Inner_loops; j++)
        {
            Za[i][j] = Za0[i][j];
        }
    }

#pragma endscop
}
