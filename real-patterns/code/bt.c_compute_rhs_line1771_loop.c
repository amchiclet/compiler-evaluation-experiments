#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int  grid_points[3] ;
extern int j;
extern int k;
extern double rho_inv;
extern double  u[(64 + 1) / 2 * 2 + 1][(64 + 1) / 2 * 2 + 1][(64 + 1) / 2 * 2 + 1][5] ;
extern double  rho_i[64 / 2 * 2 + 1][64 / 2 * 2 + 1][64 / 2 * 2 + 1] ;
extern double  us[64 / 2 * 2 + 1][64 / 2 * 2 + 1][64 / 2 * 2 + 1] ;
extern double  vs[64 / 2 * 2 + 1][64 / 2 * 2 + 1][64 / 2 * 2 + 1] ;
extern double  ws[64 / 2 * 2 + 1][64 / 2 * 2 + 1][64 / 2 * 2 + 1] ;
extern double  square[64 / 2 * 2 + 1][64 / 2 * 2 + 1][64 / 2 * 2 + 1] ;
extern double  qs[64 / 2 * 2 + 1][64 / 2 * 2 + 1][64 / 2 * 2 + 1] ;

void loop()
{
#pragma scop

    for(i = 0; i < grid_points[0]; i++)
    {
        for(j = 0; j < grid_points[1]; j++)
        {
            for(k = 0; k < grid_points[2]; k++)
            {
                rho_inv = 1.0 / u[i][j][k][0];
                rho_i[i][j][k] = rho_inv;
                us[i][j][k] = u[i][j][k][1] * rho_inv;
                vs[i][j][k] = u[i][j][k][2] * rho_inv;
                ws[i][j][k] = u[i][j][k][3] * rho_inv;
                square[i][j][k] = 0.5 *(u[i][j][k][1] * u[i][j][k][1] + u[i][j][k][2] * u[i][j][k][2] + u[i][j][k][3] * u[i][j][k][3]) * rho_inv;
                qs[i][j][k] = square[i][j][k] * rho_inv;
            }
        }
    }

#pragma endscop
}
