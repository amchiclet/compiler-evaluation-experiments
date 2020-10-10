#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int  grid_points[3] ;
extern double xi;
extern double dnxm1;
extern int j;
extern double eta;
extern double dnym1;
extern int k;
extern double zeta;
extern double dnzm1;
extern int ix;
extern double  Pface[2][3][5] ;
extern double  ce[5][13] ;
extern int iy;
extern int iz;
extern double Pxi;
extern double Peta;
extern double Pzeta;
extern double  u[(64 + 1) / 2 * 2 + 1][(64 + 1) / 2 * 2 + 1][(64 + 1) / 2 * 2 + 1][5] ;

void loop()
{
#pragma scop

    for(i = 0; i < grid_points[0]; i++)
    {
        xi =((double )i) * dnxm1;
        for(j = 0; j < grid_points[1]; j++)
        {
            eta =((double )j) * dnym1;
            for(k = 0; k < grid_points[2]; k++)
            {
                zeta =((double )k) * dnzm1;
                for(ix = 0; ix < 2; ix++)
                {
                    {
                        int m;
                        for(m = 0; m < 5; m++)
                        {
                            Pface[ix][0][m] = ce[m][0] +((double )ix) *(ce[m][1] +((double )ix) *(ce[m][4] +((double )ix) *(ce[m][7] +((double )ix) * ce[m]['\n']))) + eta *(ce[m][2] + eta *(ce[m][5] + eta *(ce[m][8] + eta * ce[m][11]))) + zeta *(ce[m][3] + zeta *(ce[m][6] + zeta *(ce[m][9] + zeta * ce[m][12])));
                        }
                    };
                }
                for(iy = 0; iy < 2; iy++)
                {
                    {
                        int m;
                        for(m = 0; m < 5; m++)
                        {
                            Pface[iy][1][m] = ce[m][0] + xi *(ce[m][1] + xi *(ce[m][4] + xi *(ce[m][7] + xi * ce[m]['\n']))) +((double )iy) *(ce[m][2] +((double )iy) *(ce[m][5] +((double )iy) *(ce[m][8] +((double )iy) * ce[m][11]))) + zeta *(ce[m][3] + zeta *(ce[m][6] + zeta *(ce[m][9] + zeta * ce[m][12])));
                        }
                    };
                }
                int m;
                for(iz = 0; iz < 2; iz++)
                {
                    {
                        for(m = 0; m < 5; m++)
                        {
                            Pface[iz][2][m] = ce[m][0] + xi *(ce[m][1] + xi *(ce[m][4] + xi *(ce[m][7] + xi * ce[m]['\n']))) + eta *(ce[m][2] + eta *(ce[m][5] + eta *(ce[m][8] + eta * ce[m][11]))) +((double )iz) *(ce[m][3] +((double )iz) *(ce[m][6] +((double )iz) *(ce[m][9] +((double )iz) * ce[m][12])));
                        }
                    };
                }
                for(m = 0; m < 5; m++)
                {
                    Pxi = xi * Pface[1][0][m] +(1.0 - xi) * Pface[0][0][m];
                    Peta = eta * Pface[1][1][m] +(1.0 - eta) * Pface[0][1][m];
                    Pzeta = zeta * Pface[1][2][m] +(1.0 - zeta) * Pface[0][2][m];
                    u[i][j][k][m] = Pxi + Peta + Pzeta - Pxi * Peta - Pxi * Pzeta - Peta * Pzeta + Pxi * Peta * Pzeta;
                }
            }
        }
    }

#pragma endscop
}
