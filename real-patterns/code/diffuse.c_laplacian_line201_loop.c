#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int iz;
extern int k;
extern int j;
extern int i;
extern double  tm2[5][5][5] ;
extern double  u[5][5][5] ;
extern double  wdtdr[5][5] ;

void loop()
{
#pragma scop

    for(iz = 0; iz < 5; iz++)
    {
        for(k = 0; k < 5; k++)
        {
            for(j = 0; j < 5; j++)
            {
                for(i = 0; i < 5; i++)
                {
                    tm2[iz][j][i] = tm2[iz][j][i] + u[iz][k][i] * wdtdr[j][k];
                }
            }
        }
    }

#pragma endscop
}
