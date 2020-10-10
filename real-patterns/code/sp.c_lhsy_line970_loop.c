#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int  grid_points[3] ;
extern int k;
extern int j;
extern double ru1;
extern double c3c4;
extern double  rho_i[64 / 2 * 2 + 1][64 / 2 * 2 + 1][64 / 2 * 2 + 1] ;
extern double  cv[64] ;
extern double  vs[64 / 2 * 2 + 1][64 / 2 * 2 + 1][64 / 2 * 2 + 1] ;
extern double  rhoq[64] ;
extern double dy3;
extern double con43;
extern double dy5;
extern double c1c5;
extern double dymax;
extern double dy1;
extern double  lhs[15][64 / 2 * 2 + 1][64 / 2 * 2 + 1][64 / 2 * 2 + 1] ;
extern double dtty2;
extern double dtty1;
extern double c2dtty1;

void loop()
{
#pragma scop

    for(i = 1; i <= grid_points[0] - 2; i++)
    {
        for(k = 1; k <= grid_points[2] - 2; k++)
        {
            for(j = 0; j <= grid_points[1] - 1; j++)
            {
                ru1 = c3c4 * rho_i[i][j][k];
                cv[j] = vs[i][j][k];
                rhoq[j] =(dy3 + con43 * ru1 >((dy5 + c1c5 * ru1 >((dymax + ru1 > dy1?dymax + ru1 : dy1))?dy5 + c1c5 * ru1 :((dymax + ru1 > dy1?dymax + ru1 : dy1))))?dy3 + con43 * ru1 :((dy5 + c1c5 * ru1 >((dymax + ru1 > dy1?dymax + ru1 : dy1))?dy5 + c1c5 * ru1 :((dymax + ru1 > dy1?dymax + ru1 : dy1)))));
            }
            for(j = 1; j <= grid_points[1] - 2; j++)
            {
                lhs[0][i][j][k] = 0.0;
                lhs[1][i][j][k] = -dtty2 * cv[j - 1] - dtty1 * rhoq[j - 1];
                lhs[2][i][j][k] = 1.0 + c2dtty1 * rhoq[j];
                lhs[3][i][j][k] = dtty2 * cv[j + 1] - dtty1 * rhoq[j + 1];
                lhs[4][i][j][k] = 0.0;
            }
        }
    }

#pragma endscop
}
