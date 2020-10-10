#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int nx;
extern int j;
extern int ny;
extern int k;
extern int nz;
extern int m;
extern double  rsd[64][64 / 2 * 2 + 1][64 / 2 * 2 + 1][5] ;
extern double  frct[64][64 / 2 * 2 + 1][64 / 2 * 2 + 1][5] ;

void loop()
{
#pragma scop

    for(i = 0; i <= nx - 1; i++)
    {
        for(j = 0; j <= ny - 1; j++)
        {
            for(k = 0; k <= nz - 1; k++)
            {
                for(m = 0; m < 5; m++)
                {
                    rsd[i][j][k][m] = -frct[i][j][k][m];
                }
            }
        }
    }

#pragma endscop
}
