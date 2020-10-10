#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int k;
extern int iz;
extern int j;
extern int i;
extern double  r[5][5][5] ;
extern double  u[5][5][5] ;
extern double  wdtdr[5][5] ;

void loop()
{
#pragma scop

    for(k = 0; k < 5; k++)
    {
        for(iz = 0; iz < 5; iz++)
        {
            for(j = 0; j < 5; j++)
            {
                for(i = 0; i < 5; i++)
                {
                    r[iz][j][i] = r[iz][j][i] + u[k][j][i] * wdtdr[iz][k];
                }
            }
        }
    }

#pragma endscop
}
