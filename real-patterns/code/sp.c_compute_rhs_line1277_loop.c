#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int  grid_points[3] ;
extern int j;
extern int k;
extern double  u[5][64 / 2 * 2 + 1][64 / 2 * 2 + 1][64 / 2 * 2 + 1] ;
extern double rho_inv;
extern double  rho_i[64 / 2 * 2 + 1][64 / 2 * 2 + 1][64 / 2 * 2 + 1] ;
extern double  us[64 / 2 * 2 + 1][64 / 2 * 2 + 1][64 / 2 * 2 + 1] ;
extern double  vs[64 / 2 * 2 + 1][64 / 2 * 2 + 1][64 / 2 * 2 + 1] ;
extern double  ws[64 / 2 * 2 + 1][64 / 2 * 2 + 1][64 / 2 * 2 + 1] ;
extern double  square[64 / 2 * 2 + 1][64 / 2 * 2 + 1][64 / 2 * 2 + 1] ;
extern double  qs[64 / 2 * 2 + 1][64 / 2 * 2 + 1][64 / 2 * 2 + 1] ;
extern double aux;
extern double c1c2;
extern double  speed[64 / 2 * 2 + 1][64 / 2 * 2 + 1][64 / 2 * 2 + 1] ;
extern double  ainv[64 / 2 * 2 + 1][64 / 2 * 2 + 1][64 / 2 * 2 + 1] ;

void loop()
{
#pragma scop

    for(i = 0; i <= grid_points[0] - 1; i++)
    {
        for(j = 0; j <= grid_points[1] - 1; j++)
        {
            for(k = 0; k <= grid_points[2] - 1; k++)
            {
                double square_ijk;
                double u_1ijk = u[1][i][j][k];
                double u_2ijk = u[2][i][j][k];
                double u_3ijk = u[3][i][j][k];
                rho_inv = 1.0 / u[0][i][j][k];
                rho_i[i][j][k] = rho_inv;
                us[i][j][k] = u_1ijk * rho_inv;
                vs[i][j][k] = u_2ijk * rho_inv;
                ws[i][j][k] = u_3ijk * rho_inv;
                square_ijk = 0.5 *(u_1ijk * u_1ijk + u_2ijk * u_2ijk + u_3ijk * u_3ijk) * rho_inv;
                square[i][j][k] = square_ijk;
                qs[i][j][k] = square_ijk * rho_inv;
                aux = c1c2 * rho_inv *(u[4][i][j][k] - square_ijk);
                aux = sqrt(aux);
                speed[i][j][k] = aux;
                ainv[i][j][k] = 1.0 / aux;
            }
        }
    }

#pragma endscop
}
