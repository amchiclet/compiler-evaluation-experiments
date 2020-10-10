#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern long k;
extern long i;
extern long j;
extern long Inner_loops;
extern double  Px[101][25] ;
extern double  Vy[25][101] ;
extern double  Cx[101][25] ;

void loop()
{
#pragma scop

    for(k = 0; k < 25; k++)
    {
        for(i = 0; i < 25; i++)
        {
            for(j = 0; j < Inner_loops; j++)
            {
                Px[j][i] += Vy[k][i] * Cx[j][k];
            }
        }
    }

#pragma endscop
}
