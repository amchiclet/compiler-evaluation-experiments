#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int  grid_points[3] ;
extern int j;
extern int k;
extern double uijk;
extern double  us[64 / 2 * 2 + 1][64 / 2 * 2 + 1][64 / 2 * 2 + 1] ;
extern double up1;
extern double um1;
extern double  rhs[64 / 2 * 2 + 1][64 / 2 * 2 + 1][64 / 2 * 2 + 1][5] ;
extern double dx1tx1;
extern double  u[(64 + 1) / 2 * 2 + 1][(64 + 1) / 2 * 2 + 1][(64 + 1) / 2 * 2 + 1][5] ;
extern double tx2;
extern double dx2tx1;
extern double xxcon2;
extern double con43;
extern double  square[64 / 2 * 2 + 1][64 / 2 * 2 + 1][64 / 2 * 2 + 1] ;
extern double c2;
extern double dx3tx1;
extern double  vs[64 / 2 * 2 + 1][64 / 2 * 2 + 1][64 / 2 * 2 + 1] ;
extern double dx4tx1;
extern double  ws[64 / 2 * 2 + 1][64 / 2 * 2 + 1][64 / 2 * 2 + 1] ;
extern double dx5tx1;
extern double xxcon3;
extern double  qs[64 / 2 * 2 + 1][64 / 2 * 2 + 1][64 / 2 * 2 + 1] ;
extern double xxcon4;
extern double xxcon5;
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
                uijk = us[i][j][k];
                up1 = us[i + 1][j][k];
                um1 = us[i - 1][j][k];
                rhs[i][j][k][0] = rhs[i][j][k][0] + dx1tx1 *(u[i + 1][j][k][0] - 2.0 * u[i][j][k][0] + u[i - 1][j][k][0]) - tx2 *(u[i + 1][j][k][1] - u[i - 1][j][k][1]);
                rhs[i][j][k][1] = rhs[i][j][k][1] + dx2tx1 *(u[i + 1][j][k][1] - 2.0 * u[i][j][k][1] + u[i - 1][j][k][1]) + xxcon2 * con43 *(up1 - 2.0 * uijk + um1) - tx2 *(u[i + 1][j][k][1] * up1 - u[i - 1][j][k][1] * um1 +(u[i + 1][j][k][4] - square[i + 1][j][k] - u[i - 1][j][k][4] + square[i - 1][j][k]) * c2);
                rhs[i][j][k][2] = rhs[i][j][k][2] + dx3tx1 *(u[i + 1][j][k][2] - 2.0 * u[i][j][k][2] + u[i - 1][j][k][2]) + xxcon2 *(vs[i + 1][j][k] - 2.0 * vs[i][j][k] + vs[i - 1][j][k]) - tx2 *(u[i + 1][j][k][2] * up1 - u[i - 1][j][k][2] * um1);
                rhs[i][j][k][3] = rhs[i][j][k][3] + dx4tx1 *(u[i + 1][j][k][3] - 2.0 * u[i][j][k][3] + u[i - 1][j][k][3]) + xxcon2 *(ws[i + 1][j][k] - 2.0 * ws[i][j][k] + ws[i - 1][j][k]) - tx2 *(u[i + 1][j][k][3] * up1 - u[i - 1][j][k][3] * um1);
                rhs[i][j][k][4] = rhs[i][j][k][4] + dx5tx1 *(u[i + 1][j][k][4] - 2.0 * u[i][j][k][4] + u[i - 1][j][k][4]) + xxcon3 *(qs[i + 1][j][k] - 2.0 * qs[i][j][k] + qs[i - 1][j][k]) + xxcon4 *(up1 * up1 - 2.0 * uijk * uijk + um1 * um1) + xxcon5 *(u[i + 1][j][k][4] * rho_i[i + 1][j][k] - 2.0 * u[i][j][k][4] * rho_i[i][j][k] + u[i - 1][j][k][4] * rho_i[i - 1][j][k]) - tx2 *((c1 * u[i + 1][j][k][4] - c2 * square[i + 1][j][k]) * up1 -(c1 * u[i - 1][j][k][4] - c2 * square[i - 1][j][k]) * um1);
            }
        }
    }

#pragma endscop
}
