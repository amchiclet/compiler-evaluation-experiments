#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int j;
extern int k;
extern int m;
extern double  u[(64 + 1) / 2 * 2 + 1][(64 + 1) / 2 * 2 + 1][(64 + 1) / 2 * 2 + 1][5] ;

void loop()
{
#pragma scop

    for(i = 0; i < 64; i++)
    {
        for(j = 0; j < 64; j++)
        {
            for(k = 0; k < 64; k++)
            {
                for(m = 0; m < 5; m++)
                {
                    u[i][j][k][m] = 1.0;
                }
            }
        }
    }

#pragma endscop
}
