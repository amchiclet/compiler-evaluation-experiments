#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int  grid_points[3] ;
extern int j;
extern int k;
extern double vijk;
extern double  vs[64 / 2 * 2 + 1][64 / 2 * 2 + 1][64 / 2 * 2 + 1] ;
extern double vp1;
extern double vm1;
extern double  rhs[5][64 / 2 * 2 + 1][64 / 2 * 2 + 1][64 / 2 * 2 + 1] ;
extern double dy1ty1;
extern double  u[5][64 / 2 * 2 + 1][64 / 2 * 2 + 1][64 / 2 * 2 + 1] ;
extern double ty2;
extern double dy2ty1;
extern double yycon2;
extern double  us[64 / 2 * 2 + 1][64 / 2 * 2 + 1][64 / 2 * 2 + 1] ;
extern double dy3ty1;
extern double con43;
extern double  square[64 / 2 * 2 + 1][64 / 2 * 2 + 1][64 / 2 * 2 + 1] ;
extern double c2;
extern double dy4ty1;
extern double  ws[64 / 2 * 2 + 1][64 / 2 * 2 + 1][64 / 2 * 2 + 1] ;
extern double dy5ty1;
extern double yycon3;
extern double  qs[64 / 2 * 2 + 1][64 / 2 * 2 + 1][64 / 2 * 2 + 1] ;
extern double yycon4;
extern double yycon5;
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
                vijk = vs[i][j][k];
                vp1 = vs[i][j + 1][k];
                vm1 = vs[i][j - 1][k];
                rhs[0][i][j][k] = rhs[0][i][j][k] + dy1ty1 *(u[0][i][j + 1][k] - 2.0 * u[0][i][j][k] + u[0][i][j - 1][k]) - ty2 *(u[2][i][j + 1][k] - u[2][i][j - 1][k]);
                rhs[1][i][j][k] = rhs[1][i][j][k] + dy2ty1 *(u[1][i][j + 1][k] - 2.0 * u[1][i][j][k] + u[1][i][j - 1][k]) + yycon2 *(us[i][j + 1][k] - 2.0 * us[i][j][k] + us[i][j - 1][k]) - ty2 *(u[1][i][j + 1][k] * vp1 - u[1][i][j - 1][k] * vm1);
                rhs[2][i][j][k] = rhs[2][i][j][k] + dy3ty1 *(u[2][i][j + 1][k] - 2.0 * u[2][i][j][k] + u[2][i][j - 1][k]) + yycon2 * con43 *(vp1 - 2.0 * vijk + vm1) - ty2 *(u[2][i][j + 1][k] * vp1 - u[2][i][j - 1][k] * vm1 +(u[4][i][j + 1][k] - square[i][j + 1][k] - u[4][i][j - 1][k] + square[i][j - 1][k]) * c2);
                rhs[3][i][j][k] = rhs[3][i][j][k] + dy4ty1 *(u[3][i][j + 1][k] - 2.0 * u[3][i][j][k] + u[3][i][j - 1][k]) + yycon2 *(ws[i][j + 1][k] - 2.0 * ws[i][j][k] + ws[i][j - 1][k]) - ty2 *(u[3][i][j + 1][k] * vp1 - u[3][i][j - 1][k] * vm1);
                rhs[4][i][j][k] = rhs[4][i][j][k] + dy5ty1 *(u[4][i][j + 1][k] - 2.0 * u[4][i][j][k] + u[4][i][j - 1][k]) + yycon3 *(qs[i][j + 1][k] - 2.0 * qs[i][j][k] + qs[i][j - 1][k]) + yycon4 *(vp1 * vp1 - 2.0 * vijk * vijk + vm1 * vm1) + yycon5 *(u[4][i][j + 1][k] * rho_i[i][j + 1][k] - 2.0 * u[4][i][j][k] * rho_i[i][j][k] + u[4][i][j - 1][k] * rho_i[i][j - 1][k]) - ty2 *((c1 * u[4][i][j + 1][k] - c2 * square[i][j + 1][k]) * vp1 -(c1 * u[4][i][j - 1][k] - c2 * square[i][j - 1][k]) * vm1);
            }
        }
    }

#pragma endscop
}
