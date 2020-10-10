#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int k;
extern double  phi1[64 + 2][64 + 2] ;
extern double  phi2[64 + 2][64 + 2] ;

void loop()
{
#pragma scop

    for(i = 0; i <= 64 + 1; i++)
    {
        for(k = 0; k <= 64 + 1; k++)
        {
            phi1[i][k] = 0.0;
            phi2[i][k] = 0.0;
        }
    }

#pragma endscop
}
