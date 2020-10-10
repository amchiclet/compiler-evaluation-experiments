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
extern double  frct[64][64 / 2 * 2 + 1][64 / 2 * 2 + 1][5] ;

void loop()
{
#pragma scop

    for(i = 0; i < nx; i++)
    {
        for(j = 0; j < ny; j++)
        {
            for(k = 0; k < nz; k++)
            {
                for(m = 0; m < 5; m++)
                {
                    frct[i][j][k][m] = 0.0;
                }
            }
        }
    }

#pragma endscop
}
