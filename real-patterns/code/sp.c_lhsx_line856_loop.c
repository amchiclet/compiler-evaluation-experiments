#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int j;
extern int  grid_points[3] ;
extern int k;
extern int i;
extern double ru1;
extern double c3c4;
extern double  rho_i[64 / 2 * 2 + 1][64 / 2 * 2 + 1][64 / 2 * 2 + 1] ;
extern double  cv[64] ;
extern double  us[64 / 2 * 2 + 1][64 / 2 * 2 + 1][64 / 2 * 2 + 1] ;
extern double  rhon[64] ;
extern double dx2;
extern double con43;
extern double dx5;
extern double c1c5;
extern double dxmax;
extern double dx1;
extern double  lhs[15][64 / 2 * 2 + 1][64 / 2 * 2 + 1][64 / 2 * 2 + 1] ;
extern double dttx2;
extern double dttx1;
extern double c2dttx1;

void loop()
{
#pragma scop

    for(j = 1; j <= grid_points[1] - 2; j++)
    {
        for(k = 1; k <= grid_points[2] - 2; k++)
        {
            for(i = 0; i <= grid_points[0] - 1; i++)
            {
                ru1 = c3c4 * rho_i[i][j][k];
                cv[i] = us[i][j][k];
                rhon[i] =(dx2 + con43 * ru1 >((dx5 + c1c5 * ru1 >((dxmax + ru1 > dx1?dxmax + ru1 : dx1))?dx5 + c1c5 * ru1 :((dxmax + ru1 > dx1?dxmax + ru1 : dx1))))?dx2 + con43 * ru1 :((dx5 + c1c5 * ru1 >((dxmax + ru1 > dx1?dxmax + ru1 : dx1))?dx5 + c1c5 * ru1 :((dxmax + ru1 > dx1?dxmax + ru1 : dx1)))));
            }
            for(i = 1; i <= grid_points[0] - 2; i++)
            {
                lhs[0][i][j][k] = 0.0;
                lhs[1][i][j][k] = -dttx2 * cv[i - 1] - dttx1 * rhon[i - 1];
                lhs[2][i][j][k] = 1.0 + c2dttx1 * rhon[i];
                lhs[3][i][j][k] = dttx2 * cv[i + 1] - dttx1 * rhon[i + 1];
                lhs[4][i][j][k] = 0.0;
            }
        }
    }

#pragma endscop
}
