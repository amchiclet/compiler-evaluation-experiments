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
extern double  rhs[64 / 2 * 2 + 1][64 / 2 * 2 + 1][64 / 2 * 2 + 1][5] ;
extern double dz1tz1;
extern double  u[(64 + 1) / 2 * 2 + 1][(64 + 1) / 2 * 2 + 1][(64 + 1) / 2 * 2 + 1][5] ;
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

    for(i = 1; i < grid_points[0] - 1; i++)
    {
        for(j = 1; j < grid_points[1] - 1; j++)
        {
            for(k = 1; k < grid_points[2] - 1; k++)
            {
                wijk = ws[i][j][k];
                wp1 = ws[i][j][k + 1];
                wm1 = ws[i][j][k - 1];
                rhs[i][j][k][0] = rhs[i][j][k][0] + dz1tz1 *(u[i][j][k + 1][0] - 2.0 * u[i][j][k][0] + u[i][j][k - 1][0]) - tz2 *(u[i][j][k + 1][3] - u[i][j][k - 1][3]);
                rhs[i][j][k][1] = rhs[i][j][k][1] + dz2tz1 *(u[i][j][k + 1][1] - 2.0 * u[i][j][k][1] + u[i][j][k - 1][1]) + zzcon2 *(us[i][j][k + 1] - 2.0 * us[i][j][k] + us[i][j][k - 1]) - tz2 *(u[i][j][k + 1][1] * wp1 - u[i][j][k - 1][1] * wm1);
                rhs[i][j][k][2] = rhs[i][j][k][2] + dz3tz1 *(u[i][j][k + 1][2] - 2.0 * u[i][j][k][2] + u[i][j][k - 1][2]) + zzcon2 *(vs[i][j][k + 1] - 2.0 * vs[i][j][k] + vs[i][j][k - 1]) - tz2 *(u[i][j][k + 1][2] * wp1 - u[i][j][k - 1][2] * wm1);
                rhs[i][j][k][3] = rhs[i][j][k][3] + dz4tz1 *(u[i][j][k + 1][3] - 2.0 * u[i][j][k][3] + u[i][j][k - 1][3]) + zzcon2 * con43 *(wp1 - 2.0 * wijk + wm1) - tz2 *(u[i][j][k + 1][3] * wp1 - u[i][j][k - 1][3] * wm1 +(u[i][j][k + 1][4] - square[i][j][k + 1] - u[i][j][k - 1][4] + square[i][j][k - 1]) * c2);
                rhs[i][j][k][4] = rhs[i][j][k][4] + dz5tz1 *(u[i][j][k + 1][4] - 2.0 * u[i][j][k][4] + u[i][j][k - 1][4]) + zzcon3 *(qs[i][j][k + 1] - 2.0 * qs[i][j][k] + qs[i][j][k - 1]) + zzcon4 *(wp1 * wp1 - 2.0 * wijk * wijk + wm1 * wm1) + zzcon5 *(u[i][j][k + 1][4] * rho_i[i][j][k + 1] - 2.0 * u[i][j][k][4] * rho_i[i][j][k] + u[i][j][k - 1][4] * rho_i[i][j][k - 1]) - tz2 *((c1 * u[i][j][k + 1][4] - c2 * square[i][j][k + 1]) * wp1 -(c1 * u[i][j][k - 1][4] - c2 * square[i][j][k - 1]) * wm1);
            }
        }
    }

#pragma endscop
}
