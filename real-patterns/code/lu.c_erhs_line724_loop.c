#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int L1;
extern int L2;
extern int j;
extern int jst;
extern int jend;
extern int k;
extern int nz;
extern double  flux[64][64 / 2 * 2 + 1][64 / 2 * 2 + 1][5] ;
extern double  rsd[64][64 / 2 * 2 + 1][64 / 2 * 2 + 1][5] ;
extern double u21;
extern double q;

void loop()
{
#pragma scop

    for(i = L1; i <= L2; i++)
    {
        for(j = jst; j <= jend; j++)
        {
            for(k = 1; k < nz - 1; k++)
            {
                flux[i][j][k][0] = rsd[i][j][k][1];
                u21 = rsd[i][j][k][1] / rsd[i][j][k][0];
                q = 0.50 *(rsd[i][j][k][1] * rsd[i][j][k][1] + rsd[i][j][k][2] * rsd[i][j][k][2] + rsd[i][j][k][3] * rsd[i][j][k][3]) / rsd[i][j][k][0];
                flux[i][j][k][1] = rsd[i][j][k][1] * u21 + 0.40e+00 *(rsd[i][j][k][4] - q);
                flux[i][j][k][2] = rsd[i][j][k][2] * u21;
                flux[i][j][k][3] = rsd[i][j][k][3] * u21;
                flux[i][j][k][4] =(1.40e+00 * rsd[i][j][k][4] - 0.40e+00 * q) * u21;
            }
        }
    }

#pragma endscop
}
