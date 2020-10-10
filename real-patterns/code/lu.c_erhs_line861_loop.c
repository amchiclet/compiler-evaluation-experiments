#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int ist;
extern int iend;
extern int j;
extern int L1;
extern int L2;
extern int k;
extern int nz;
extern double  flux[64][64 / 2 * 2 + 1][64 / 2 * 2 + 1][5] ;
extern double  rsd[64][64 / 2 * 2 + 1][64 / 2 * 2 + 1][5] ;
extern double u31;
extern double q;

void loop()
{
#pragma scop

    for(i = ist; i <= iend; i++)
    {
        for(j = L1; j <= L2; j++)
        {
            for(k = 1; k <= nz - 2; k++)
            {
                flux[i][j][k][0] = rsd[i][j][k][2];
                u31 = rsd[i][j][k][2] / rsd[i][j][k][0];
                q = 0.50 *(rsd[i][j][k][1] * rsd[i][j][k][1] + rsd[i][j][k][2] * rsd[i][j][k][2] + rsd[i][j][k][3] * rsd[i][j][k][3]) / rsd[i][j][k][0];
                flux[i][j][k][1] = rsd[i][j][k][1] * u31;
                flux[i][j][k][2] = rsd[i][j][k][2] * u31 + 0.40e+00 *(rsd[i][j][k][4] - q);
                flux[i][j][k][3] = rsd[i][j][k][3] * u31;
                flux[i][j][k][4] =(1.40e+00 * rsd[i][j][k][4] - 0.40e+00 * q) * u31;
            }
        }
    }

#pragma endscop
}
