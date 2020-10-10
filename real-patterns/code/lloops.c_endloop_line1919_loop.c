#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern long i;
extern long Inner_loops;
extern long j;
extern double  Px[101][25] ;
extern double  Px0[101][25] ;

void loop()
{
#pragma scop

    for(i = 0; i < Inner_loops; i++)
    {
        for(j = 4; j < 13; j++)
        {
            Px[i][j] = Px0[i][j];
        }
    }

#pragma endscop
}
