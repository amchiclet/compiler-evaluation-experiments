#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int j;
extern int k;
extern double  u[5][64 / 2 * 2 + 1][64 / 2 * 2 + 1][64 / 2 * 2 + 1] ;

void loop()
{
#pragma scop

    for(i = 0; i <= 64 - 1; i++)
    {
        for(j = 0; j <= 64 - 1; j++)
        {
            for(k = 0; k <= 64 - 1; k++)
            {
                u[0][i][j][k] = 1.0;
                u[1][i][j][k] = 0.0;
                u[2][i][j][k] = 0.0;
                u[3][i][j][k] = 0.0;
                u[4][i][j][k] = 1.0;
            }
        }
    }

#pragma endscop
}
