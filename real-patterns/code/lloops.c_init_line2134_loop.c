#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern long i;
extern long j;
extern double  H0[64][64] ;
extern double  H[64][64] ;

void loop()
{
#pragma scop

    for(i = 0; i < 64; i++)
    {
        for(j = 0; j < 64; j++)
        {
            H0[i][j] = H[i][j];
        }
    }

#pragma endscop
}
