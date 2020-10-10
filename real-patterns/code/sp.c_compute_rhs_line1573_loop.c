#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int  grid_points[3] ;
extern int j;
extern int k;
extern double wijk;
extern double  ws[64 / 2 * 2 + 1][64 / 2 * 2 + 1][64 / 2 * 2 + 1] ;
extern double wp1;
extern double wm1;
extern double  rhs[5][64 / 2 * 2 + 1][64 / 2 * 2 + 1][64 / 2 * 2 + 1] ;
extern double dz1tz1;
extern double  u[5][64 / 2 * 2 + 1][64 / 2 * 2 + 1][64 / 2 * 2 + 1] ;
extern double tz2;
extern double dz2tz1;
extern double zzcon2;
extern double  us[64 / 2 * 2 + 1][64 / 2 * 2 + 1][64 / 2 * 2 + 1] ;
extern double dz3tz1;
extern double  vs[64 / 2 * 2 + 1][64 / 2 * 2 + 1][64 / 2 * 2 + 1] ;
extern double dz4tz1;
extern double con43;
extern double  square[64 / 2 * 2 + 1][64 / 2 * 2 + 1][64 / 2 * 2 + 1] ;
extern double c2;
extern double dz5tz1;
extern double zzcon3;
extern double  qs[64 / 2 * 2 + 1][64 / 2 * 2 + 1][64 / 2 * 2 + 1] ;
extern double zzcon4;
extern double zzcon5;
extern double  rho_i[64 / 2 * 2 + 1][64 / 2 * 2 + 1][64 / 2 * 2 + 1] ;
extern double c1;

void loop()
{
#pragma scop

    for(i = 1; i <= grid_points[0] - 2; i++)
    {
        for(j = 1; j <= grid_points[1] - 2; j++)
        {
            for(k = 1; k <= grid_points[2] - 2; k++)
            {
                wijk = ws[i][j][k];
                wp1 = ws[i][j][k + 1];
                wm1 = ws[i][j][k - 1];
                rhs[0][i][j][k] = rhs[0][i][j][k] + dz1tz1 *(u[0][i][j][k + 1] - 2.0 * u[0][i][j][k] + u[0][i][j][k - 1]) - tz2 *(u[3][i][j][k + 1] - u[3][i][j][k - 1]);
                rhs[1][i][j][k] = rhs[1][i][j][k] + dz2tz1 *(u[1][i][j][k + 1] - 2.0 * u[1][i][j][k] + u[1][i][j][k - 1]) + zzcon2 *(us[i][j][k + 1] - 2.0 * us[i][j][k] + us[i][j][k - 1]) - tz2 *(u[1][i][j][k + 1] * wp1 - u[1][i][j][k - 1] * wm1);
                rhs[2][i][j][k] = rhs[2][i][j][k] + dz3tz1 *(u[2][i][j][k + 1] - 2.0 * u[2][i][j][k] + u[2][i][j][k - 1]) + zzcon2 *(vs[i][j][k + 1] - 2.0 * vs[i][j][k] + vs[i][j][k - 1]) - tz2 *(u[2][i][j][k + 1] * wp1 - u[2][i][j][k - 1] * wm1);
                rhs[3][i][j][k] = rhs[3][i][j][k] + dz4tz1 *(u[3][i][j][k + 1] - 2.0 * u[3][i][j][k] + u[3][i][j][k - 1]) + zzcon2 * con43 *(wp1 - 2.0 * wijk + wm1) - tz2 *(u[3][i][j][k + 1] * wp1 - u[3][i][j][k - 1] * wm1 +(u[4][i][j][k + 1] - square[i][j][k + 1] - u[4][i][j][k - 1] + square[i][j][k - 1]) * c2);
                rhs[4][i][j][k] = rhs[4][i][j][k] + dz5tz1 *(u[4][i][j][k + 1] - 2.0 * u[4][i][j][k] + u[4][i][j][k - 1]) + zzcon3 *(qs[i][j][k + 1] - 2.0 * qs[i][j][k] + qs[i][j][k - 1]) + zzcon4 *(wp1 * wp1 - 2.0 * wijk * wijk + wm1 * wm1) + zzcon5 *(u[4][i][j][k + 1] * rho_i[i][j][k + 1] - 2.0 * u[4][i][j][k] * rho_i[i][j][k] + u[4][i][j][k - 1] * rho_i[i][j][k - 1]) - tz2 *((c1 * u[4][i][j][k + 1] - c2 * square[i][j][k + 1]) * wp1 -(c1 * u[4][i][j][k - 1] - c2 * square[i][j][k - 1]) * wm1);
            }
        }
    }

#pragma endscop
}
