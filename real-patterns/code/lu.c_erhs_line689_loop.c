#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int nx;
extern int iglob;
extern double xi;
extern int nx0;
extern int j;
extern int ny;
extern int jglob;
extern double eta;
extern int ny0;
extern int k;
extern int nz;
extern double zeta;
extern int m;
extern double  rsd[64][64 / 2 * 2 + 1][64 / 2 * 2 + 1][5] ;
extern double  ce[5][13] ;

void loop()
{
#pragma scop

    for(i = 0; i < nx; i++)
    {
        iglob = i;
        xi =((double )iglob) /(nx0 - 1);
        for(j = 0; j < ny; j++)
        {
            jglob = j;
            eta =((double )jglob) /(ny0 - 1);
            for(k = 0; k < nz; k++)
            {
                zeta =((double )k) /(nz - 1);
                for(m = 0; m < 5; m++)
                {
                    rsd[i][j][k][m] = ce[m][0] + ce[m][1] * xi + ce[m][2] * eta + ce[m][3] * zeta + ce[m][4] * xi * xi + ce[m][5] * eta * eta + ce[m][6] * zeta * zeta + ce[m][7] * xi * xi * xi + ce[m][8] * eta * eta * eta + ce[m][9] * zeta * zeta * zeta + ce[m][10] * xi * xi * xi * xi + ce[m][11] * eta * eta * eta * eta + ce[m][12] * zeta * zeta * zeta * zeta;
                }
            }
        }
    }

#pragma endscop
}
