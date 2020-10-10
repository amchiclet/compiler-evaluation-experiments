#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int ist;
extern int iend;
extern int j;
extern int jst;
extern int jend;
extern int k;
extern int nz;
extern int m;
extern double  u[64][64 / 2 * 2 + 1][64 / 2 * 2 + 1][5] ;
extern double tmp;
extern double  rsd[64][64 / 2 * 2 + 1][64 / 2 * 2 + 1][5] ;

void loop()
{
#pragma scop

    for(i = ist; i <= iend; i++)
    {
        for(j = jst; j <= jend; j++)
        {
            for(k = 1; k <= nz - 2; k++)
            {
                for(m = 0; m < 5; m++)
                {
                    u[i][j][k][m] = u[i][j][k][m] + tmp * rsd[i][j][k][m];
                }
            }
        }
    }

#pragma endscop
}
