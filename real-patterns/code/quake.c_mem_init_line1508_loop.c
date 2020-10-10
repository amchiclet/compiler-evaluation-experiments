#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int ARCHmatrixlen;
extern int j;
extern int k;
extern double *** restrict K;

void loop()
{
#pragma scop

    for(i = 0; i < ARCHmatrixlen; i++)
    {
        for(j = 0; j < 3; j++)
        {
            for(k = 0; k < 3; k++)
            {
                K[i][j][k] = 0.0;
            }
        }
    }

#pragma endscop
}
