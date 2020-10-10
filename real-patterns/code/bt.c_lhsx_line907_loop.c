#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int j;
extern int  grid_points[3] ;
extern int k;
extern int i;
extern double  u[(64 + 1) / 2 * 2 + 1][(64 + 1) / 2 * 2 + 1][(64 + 1) / 2 * 2 + 1][5] ;
extern double  fjac[64 / 2 * 2 + 1][64 / 2 * 2 + 1][64 - 1 + 1][5][5] ;
extern double c2;
extern double c1;
extern double  njac[64 / 2 * 2 + 1][64 / 2 * 2 + 1][64 - 1 + 1][5][5] ;
extern double con43;
extern double c3c4;
extern double c1345;
extern double dt;
extern double tx1;
extern double tx2;
extern double  lhs[64 / 2 * 2 + 1][64 / 2 * 2 + 1][64 / 2 * 2 + 1][3][5][5] ;
extern double dx1;
extern double dx2;
extern double dx3;
extern double dx4;
extern double dx5;

void loop()
{
#pragma scop

    for(j = 1; j < grid_points[1] - 1; j++)
    {
        for(k = 1; k < grid_points[2] - 1; k++)
        {
            for(i = 0; i < grid_points[0]; i++)
            {
                double tmp1 = 1.0 / u[i][j][k][0];
                double tmp2 = tmp1 * tmp1;
                double tmp3 = tmp1 * tmp2;
                fjac[i][j][k][0][0] = 0.0;
                fjac[i][j][k][0][1] = 1.0;
                fjac[i][j][k][0][2] = 0.0;
                fjac[i][j][k][0][3] = 0.0;
                fjac[i][j][k][0][4] = 0.0;
                fjac[i][j][k][1][0] = -(u[i][j][k][1] * tmp2 * u[i][j][k][1]) + c2 * 0.5 *(u[i][j][k][1] * u[i][j][k][1] + u[i][j][k][2] * u[i][j][k][2] + u[i][j][k][3] * u[i][j][k][3]) * tmp2;
                fjac[i][j][k][1][1] =(2.0 - c2) *(u[i][j][k][1] / u[i][j][k][0]);
                fjac[i][j][k][1][2] = -c2 *(u[i][j][k][2] * tmp1);
                fjac[i][j][k][1][3] = -c2 *(u[i][j][k][3] * tmp1);
                fjac[i][j][k][1][4] = c2;
                fjac[i][j][k][2][0] = -(u[i][j][k][1] * u[i][j][k][2]) * tmp2;
                fjac[i][j][k][2][1] = u[i][j][k][2] * tmp1;
                fjac[i][j][k][2][2] = u[i][j][k][1] * tmp1;
                fjac[i][j][k][2][3] = 0.0;
                fjac[i][j][k][2][4] = 0.0;
                fjac[i][j][k][3][0] = -(u[i][j][k][1] * u[i][j][k][3]) * tmp2;
                fjac[i][j][k][3][1] = u[i][j][k][3] * tmp1;
                fjac[i][j][k][3][2] = 0.0;
                fjac[i][j][k][3][3] = u[i][j][k][1] * tmp1;
                fjac[i][j][k][3][4] = 0.0;
                fjac[i][j][k][4][0] =(c2 *(u[i][j][k][1] * u[i][j][k][1] + u[i][j][k][2] * u[i][j][k][2] + u[i][j][k][3] * u[i][j][k][3]) * tmp2 - c1 *(u[i][j][k][4] * tmp1)) *(u[i][j][k][1] * tmp1);
                fjac[i][j][k][4][1] = c1 * u[i][j][k][4] * tmp1 - 0.5 * c2 *(3.0 * u[i][j][k][1] * u[i][j][k][1] + u[i][j][k][2] * u[i][j][k][2] + u[i][j][k][3] * u[i][j][k][3]) * tmp2;
                fjac[i][j][k][4][2] = -c2 *(u[i][j][k][2] * u[i][j][k][1]) * tmp2;
                fjac[i][j][k][4][3] = -c2 *(u[i][j][k][3] * u[i][j][k][1]) * tmp2;
                fjac[i][j][k][4][4] = c1 *(u[i][j][k][1] * tmp1);
                njac[i][j][k][0][0] = 0.0;
                njac[i][j][k][0][1] = 0.0;
                njac[i][j][k][0][2] = 0.0;
                njac[i][j][k][0][3] = 0.0;
                njac[i][j][k][0][4] = 0.0;
                njac[i][j][k][1][0] = -con43 * c3c4 * tmp2 * u[i][j][k][1];
                njac[i][j][k][1][1] = con43 * c3c4 * tmp1;
                njac[i][j][k][1][2] = 0.0;
                njac[i][j][k][1][3] = 0.0;
                njac[i][j][k][1][4] = 0.0;
                njac[i][j][k][2][0] = -c3c4 * tmp2 * u[i][j][k][2];
                njac[i][j][k][2][1] = 0.0;
                njac[i][j][k][2][2] = c3c4 * tmp1;
                njac[i][j][k][2][3] = 0.0;
                njac[i][j][k][2][4] = 0.0;
                njac[i][j][k][3][0] = -c3c4 * tmp2 * u[i][j][k][3];
                njac[i][j][k][3][1] = 0.0;
                njac[i][j][k][3][2] = 0.0;
                njac[i][j][k][3][3] = c3c4 * tmp1;
                njac[i][j][k][3][4] = 0.0;
                njac[i][j][k][4][0] = -(con43 * c3c4 - c1345) * tmp3 *(u[i][j][k][1] * u[i][j][k][1]) -(c3c4 - c1345) * tmp3 *(u[i][j][k][2] * u[i][j][k][2]) -(c3c4 - c1345) * tmp3 *(u[i][j][k][3] * u[i][j][k][3]) - c1345 * tmp2 * u[i][j][k][4];
                njac[i][j][k][4][1] =(con43 * c3c4 - c1345) * tmp2 * u[i][j][k][1];
                njac[i][j][k][4][2] =(c3c4 - c1345) * tmp2 * u[i][j][k][2];
                njac[i][j][k][4][3] =(c3c4 - c1345) * tmp2 * u[i][j][k][3];
                njac[i][j][k][4][4] = c1345 * tmp1;
            }
            for(i = 1; i < grid_points[0] - 1; i++)
            {
                double tmp1 = dt * tx1;
                double tmp2 = dt * tx2;
                lhs[i][j][k][0][0][0] = -tmp2 * fjac[i - 1][j][k][0][0] - tmp1 * njac[i - 1][j][k][0][0] - tmp1 * dx1;
                lhs[i][j][k][0][0][1] = -tmp2 * fjac[i - 1][j][k][0][1] - tmp1 * njac[i - 1][j][k][0][1];
                lhs[i][j][k][0][0][2] = -tmp2 * fjac[i - 1][j][k][0][2] - tmp1 * njac[i - 1][j][k][0][2];
                lhs[i][j][k][0][0][3] = -tmp2 * fjac[i - 1][j][k][0][3] - tmp1 * njac[i - 1][j][k][0][3];
                lhs[i][j][k][0][0][4] = -tmp2 * fjac[i - 1][j][k][0][4] - tmp1 * njac[i - 1][j][k][0][4];
                lhs[i][j][k][0][1][0] = -tmp2 * fjac[i - 1][j][k][1][0] - tmp1 * njac[i - 1][j][k][1][0];
                lhs[i][j][k][0][1][1] = -tmp2 * fjac[i - 1][j][k][1][1] - tmp1 * njac[i - 1][j][k][1][1] - tmp1 * dx2;
                lhs[i][j][k][0][1][2] = -tmp2 * fjac[i - 1][j][k][1][2] - tmp1 * njac[i - 1][j][k][1][2];
                lhs[i][j][k][0][1][3] = -tmp2 * fjac[i - 1][j][k][1][3] - tmp1 * njac[i - 1][j][k][1][3];
                lhs[i][j][k][0][1][4] = -tmp2 * fjac[i - 1][j][k][1][4] - tmp1 * njac[i - 1][j][k][1][4];
                lhs[i][j][k][0][2][0] = -tmp2 * fjac[i - 1][j][k][2][0] - tmp1 * njac[i - 1][j][k][2][0];
                lhs[i][j][k][0][2][1] = -tmp2 * fjac[i - 1][j][k][2][1] - tmp1 * njac[i - 1][j][k][2][1];
                lhs[i][j][k][0][2][2] = -tmp2 * fjac[i - 1][j][k][2][2] - tmp1 * njac[i - 1][j][k][2][2] - tmp1 * dx3;
                lhs[i][j][k][0][2][3] = -tmp2 * fjac[i - 1][j][k][2][3] - tmp1 * njac[i - 1][j][k][2][3];
                lhs[i][j][k][0][2][4] = -tmp2 * fjac[i - 1][j][k][2][4] - tmp1 * njac[i - 1][j][k][2][4];
                lhs[i][j][k][0][3][0] = -tmp2 * fjac[i - 1][j][k][3][0] - tmp1 * njac[i - 1][j][k][3][0];
                lhs[i][j][k][0][3][1] = -tmp2 * fjac[i - 1][j][k][3][1] - tmp1 * njac[i - 1][j][k][3][1];
                lhs[i][j][k][0][3][2] = -tmp2 * fjac[i - 1][j][k][3][2] - tmp1 * njac[i - 1][j][k][3][2];
                lhs[i][j][k][0][3][3] = -tmp2 * fjac[i - 1][j][k][3][3] - tmp1 * njac[i - 1][j][k][3][3] - tmp1 * dx4;
                lhs[i][j][k][0][3][4] = -tmp2 * fjac[i - 1][j][k][3][4] - tmp1 * njac[i - 1][j][k][3][4];
                lhs[i][j][k][0][4][0] = -tmp2 * fjac[i - 1][j][k][4][0] - tmp1 * njac[i - 1][j][k][4][0];
                lhs[i][j][k][0][4][1] = -tmp2 * fjac[i - 1][j][k][4][1] - tmp1 * njac[i - 1][j][k][4][1];
                lhs[i][j][k][0][4][2] = -tmp2 * fjac[i - 1][j][k][4][2] - tmp1 * njac[i - 1][j][k][4][2];
                lhs[i][j][k][0][4][3] = -tmp2 * fjac[i - 1][j][k][4][3] - tmp1 * njac[i - 1][j][k][4][3];
                lhs[i][j][k][0][4][4] = -tmp2 * fjac[i - 1][j][k][4][4] - tmp1 * njac[i - 1][j][k][4][4] - tmp1 * dx5;
                lhs[i][j][k][1][0][0] = 1.0 + tmp1 * 2.0 * njac[i][j][k][0][0] + tmp1 * 2.0 * dx1;
                lhs[i][j][k][1][0][1] = tmp1 * 2.0 * njac[i][j][k][0][1];
                lhs[i][j][k][1][0][2] = tmp1 * 2.0 * njac[i][j][k][0][2];
                lhs[i][j][k][1][0][3] = tmp1 * 2.0 * njac[i][j][k][0][3];
                lhs[i][j][k][1][0][4] = tmp1 * 2.0 * njac[i][j][k][0][4];
                lhs[i][j][k][1][1][0] = tmp1 * 2.0 * njac[i][j][k][1][0];
                lhs[i][j][k][1][1][1] = 1.0 + tmp1 * 2.0 * njac[i][j][k][1][1] + tmp1 * 2.0 * dx2;
                lhs[i][j][k][1][1][2] = tmp1 * 2.0 * njac[i][j][k][1][2];
                lhs[i][j][k][1][1][3] = tmp1 * 2.0 * njac[i][j][k][1][3];
                lhs[i][j][k][1][1][4] = tmp1 * 2.0 * njac[i][j][k][1][4];
                lhs[i][j][k][1][2][0] = tmp1 * 2.0 * njac[i][j][k][2][0];
                lhs[i][j][k][1][2][1] = tmp1 * 2.0 * njac[i][j][k][2][1];
                lhs[i][j][k][1][2][2] = 1.0 + tmp1 * 2.0 * njac[i][j][k][2][2] + tmp1 * 2.0 * dx3;
                lhs[i][j][k][1][2][3] = tmp1 * 2.0 * njac[i][j][k][2][3];
                lhs[i][j][k][1][2][4] = tmp1 * 2.0 * njac[i][j][k][2][4];
                lhs[i][j][k][1][3][0] = tmp1 * 2.0 * njac[i][j][k][3][0];
                lhs[i][j][k][1][3][1] = tmp1 * 2.0 * njac[i][j][k][3][1];
                lhs[i][j][k][1][3][2] = tmp1 * 2.0 * njac[i][j][k][3][2];
                lhs[i][j][k][1][3][3] = 1.0 + tmp1 * 2.0 * njac[i][j][k][3][3] + tmp1 * 2.0 * dx4;
                lhs[i][j][k][1][3][4] = tmp1 * 2.0 * njac[i][j][k][3][4];
                lhs[i][j][k][1][4][0] = tmp1 * 2.0 * njac[i][j][k][4][0];
                lhs[i][j][k][1][4][1] = tmp1 * 2.0 * njac[i][j][k][4][1];
                lhs[i][j][k][1][4][2] = tmp1 * 2.0 * njac[i][j][k][4][2];
                lhs[i][j][k][1][4][3] = tmp1 * 2.0 * njac[i][j][k][4][3];
                lhs[i][j][k][1][4][4] = 1.0 + tmp1 * 2.0 * njac[i][j][k][4][4] + tmp1 * 2.0 * dx5;
                lhs[i][j][k][2][0][0] = tmp2 * fjac[i + 1][j][k][0][0] - tmp1 * njac[i + 1][j][k][0][0] - tmp1 * dx1;
                lhs[i][j][k][2][0][1] = tmp2 * fjac[i + 1][j][k][0][1] - tmp1 * njac[i + 1][j][k][0][1];
                lhs[i][j][k][2][0][2] = tmp2 * fjac[i + 1][j][k][0][2] - tmp1 * njac[i + 1][j][k][0][2];
                lhs[i][j][k][2][0][3] = tmp2 * fjac[i + 1][j][k][0][3] - tmp1 * njac[i + 1][j][k][0][3];
                lhs[i][j][k][2][0][4] = tmp2 * fjac[i + 1][j][k][0][4] - tmp1 * njac[i + 1][j][k][0][4];
                lhs[i][j][k][2][1][0] = tmp2 * fjac[i + 1][j][k][1][0] - tmp1 * njac[i + 1][j][k][1][0];
                lhs[i][j][k][2][1][1] = tmp2 * fjac[i + 1][j][k][1][1] - tmp1 * njac[i + 1][j][k][1][1] - tmp1 * dx2;
                lhs[i][j][k][2][1][2] = tmp2 * fjac[i + 1][j][k][1][2] - tmp1 * njac[i + 1][j][k][1][2];
                lhs[i][j][k][2][1][3] = tmp2 * fjac[i + 1][j][k][1][3] - tmp1 * njac[i + 1][j][k][1][3];
                lhs[i][j][k][2][1][4] = tmp2 * fjac[i + 1][j][k][1][4] - tmp1 * njac[i + 1][j][k][1][4];
                lhs[i][j][k][2][2][0] = tmp2 * fjac[i + 1][j][k][2][0] - tmp1 * njac[i + 1][j][k][2][0];
                lhs[i][j][k][2][2][1] = tmp2 * fjac[i + 1][j][k][2][1] - tmp1 * njac[i + 1][j][k][2][1];
                lhs[i][j][k][2][2][2] = tmp2 * fjac[i + 1][j][k][2][2] - tmp1 * njac[i + 1][j][k][2][2] - tmp1 * dx3;
                lhs[i][j][k][2][2][3] = tmp2 * fjac[i + 1][j][k][2][3] - tmp1 * njac[i + 1][j][k][2][3];
                lhs[i][j][k][2][2][4] = tmp2 * fjac[i + 1][j][k][2][4] - tmp1 * njac[i + 1][j][k][2][4];
                lhs[i][j][k][2][3][0] = tmp2 * fjac[i + 1][j][k][3][0] - tmp1 * njac[i + 1][j][k][3][0];
                lhs[i][j][k][2][3][1] = tmp2 * fjac[i + 1][j][k][3][1] - tmp1 * njac[i + 1][j][k][3][1];
                lhs[i][j][k][2][3][2] = tmp2 * fjac[i + 1][j][k][3][2] - tmp1 * njac[i + 1][j][k][3][2];
                lhs[i][j][k][2][3][3] = tmp2 * fjac[i + 1][j][k][3][3] - tmp1 * njac[i + 1][j][k][3][3] - tmp1 * dx4;
                lhs[i][j][k][2][3][4] = tmp2 * fjac[i + 1][j][k][3][4] - tmp1 * njac[i + 1][j][k][3][4];
                lhs[i][j][k][2][4][0] = tmp2 * fjac[i + 1][j][k][4][0] - tmp1 * njac[i + 1][j][k][4][0];
                lhs[i][j][k][2][4][1] = tmp2 * fjac[i + 1][j][k][4][1] - tmp1 * njac[i + 1][j][k][4][1];
                lhs[i][j][k][2][4][2] = tmp2 * fjac[i + 1][j][k][4][2] - tmp1 * njac[i + 1][j][k][4][2];
                lhs[i][j][k][2][4][3] = tmp2 * fjac[i + 1][j][k][4][3] - tmp1 * njac[i + 1][j][k][4][3];
                lhs[i][j][k][2][4][4] = tmp2 * fjac[i + 1][j][k][4][4] - tmp1 * njac[i + 1][j][k][4][4] - tmp1 * dx5;
            }
        }
    }

#pragma endscop
}
