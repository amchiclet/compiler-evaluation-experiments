#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int ist;
extern int iend;
extern int iglob;
extern int j;
extern int jst;
extern int jend;
extern int jglob;
extern int k;
extern int nz;
extern int nx0;
extern int ny0;
extern double  u000ijk[5] ;
extern double  ce[5][13] ;
extern double tmp;
extern double  u[64][64 / 2 * 2 + 1][64 / 2 * 2 + 1][5] ;
extern double  errnm[5] ;

void loop()
{
#pragma scop

    for(i = ist; i <= iend; i++)
    {
        iglob = i;
        for(j = jst; j <= jend; j++)
        {
            jglob = j;
            for(k = 1; k <= nz - 2; k++)
            {
                    int m;
                    double xi;
                    double eta;
                    double zeta;
                    xi =((double )iglob) /(nx0 - 1);
                    eta =((double )jglob) /(ny0 - 1);
                    zeta =((double )k) /(nz - 1);
                    for(m = 0; m < 5; m++)
                    {
                        u000ijk[m] = ce[m][0] + ce[m][1] * xi + ce[m][2] * eta + ce[m][3] * zeta + ce[m][4] * xi * xi + ce[m][5] * eta * eta + ce[m][6] * zeta * zeta + ce[m][7] * xi * xi * xi + ce[m][8] * eta * eta * eta + ce[m][9] * zeta * zeta * zeta + ce[m][10] * xi * xi * xi * xi + ce[m][11] * eta * eta * eta * eta + ce[m][12] * zeta * zeta * zeta * zeta;
                    }
                for(m = 0; m < 5; m++)
                {
                    tmp = u000ijk[m] - u[i][j][k][m];
                    errnm[m] = errnm[m] + tmp * tmp;
                }
            }
        }
    }

#pragma endscop
}
