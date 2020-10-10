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
extern double  rhs[5][64 / 2 * 2 + 1][64 / 2 * 2 + 1][64 / 2 * 2 + 1] ;
extern double dx1tx1;
extern double  u[5][64 / 2 * 2 + 1][64 / 2 * 2 + 1][64 / 2 * 2 + 1] ;
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

    for(i = 1; i <= grid_points[0] - 2; i++)
    {
        for(j = 1; j <= grid_points[1] - 2; j++)
        {
            for(k = 1; k <= grid_points[2] - 2; k++)
            {
                uijk = us[i][j][k];
                up1 = us[i + 1][j][k];
                um1 = us[i - 1][j][k];
                rhs[0][i][j][k] = rhs[0][i][j][k] + dx1tx1 *(u[0][i + 1][j][k] - 2.0 * u[0][i][j][k] + u[0][i - 1][j][k]) - tx2 *(u[1][i + 1][j][k] - u[1][i - 1][j][k]);
                rhs[1][i][j][k] = rhs[1][i][j][k] + dx2tx1 *(u[1][i + 1][j][k] - 2.0 * u[1][i][j][k] + u[1][i - 1][j][k]) + xxcon2 * con43 *(up1 - 2.0 * uijk + um1) - tx2 *(u[1][i + 1][j][k] * up1 - u[1][i - 1][j][k] * um1 +(u[4][i + 1][j][k] - square[i + 1][j][k] - u[4][i - 1][j][k] + square[i - 1][j][k]) * c2);
                rhs[2][i][j][k] = rhs[2][i][j][k] + dx3tx1 *(u[2][i + 1][j][k] - 2.0 * u[2][i][j][k] + u[2][i - 1][j][k]) + xxcon2 *(vs[i + 1][j][k] - 2.0 * vs[i][j][k] + vs[i - 1][j][k]) - tx2 *(u[2][i + 1][j][k] * up1 - u[2][i - 1][j][k] * um1);
                rhs[3][i][j][k] = rhs[3][i][j][k] + dx4tx1 *(u[3][i + 1][j][k] - 2.0 * u[3][i][j][k] + u[3][i - 1][j][k]) + xxcon2 *(ws[i + 1][j][k] - 2.0 * ws[i][j][k] + ws[i - 1][j][k]) - tx2 *(u[3][i + 1][j][k] * up1 - u[3][i - 1][j][k] * um1);
                rhs[4][i][j][k] = rhs[4][i][j][k] + dx5tx1 *(u[4][i + 1][j][k] - 2.0 * u[4][i][j][k] + u[4][i - 1][j][k]) + xxcon3 *(qs[i + 1][j][k] - 2.0 * qs[i][j][k] + qs[i - 1][j][k]) + xxcon4 *(up1 * up1 - 2.0 * uijk * uijk + um1 * um1) + xxcon5 *(u[4][i + 1][j][k] * rho_i[i + 1][j][k] - 2.0 * u[4][i][j][k] * rho_i[i][j][k] + u[4][i - 1][j][k] * rho_i[i - 1][j][k]) - tx2 *((c1 * u[4][i + 1][j][k] - c2 * square[i + 1][j][k]) * up1 -(c1 * u[4][i - 1][j][k] - c2 * square[i - 1][j][k]) * um1);
            }
        }
    }

#pragma endscop
}
