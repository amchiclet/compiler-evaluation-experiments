#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int j;
extern int  grid_points[3] ;
extern int k;
extern double fac1;
extern double  lhs[15][64 / 2 * 2 + 1][64 / 2 * 2 + 1][64 / 2 * 2 + 1] ;
extern int n;
extern int i;
extern int m;
extern double  rhs[5][64 / 2 * 2 + 1][64 / 2 * 2 + 1][64 / 2 * 2 + 1] ;
extern int i1;
extern double fac2;

void loop()
{
#pragma scop

    for(j = 1; j <= grid_points[1] - 2; j++)
    {
        for(k = 1; k <= grid_points[2] - 2; k++)
        {
            fac1 = 1.0 / lhs[n + 2][i][j][k];
            lhs[n + 3][i][j][k] = fac1 * lhs[n + 3][i][j][k];
            lhs[n + 4][i][j][k] = fac1 * lhs[n + 4][i][j][k];
            for(m = 0; m < 3; m++)
            {
                rhs[m][i][j][k] = fac1 * rhs[m][i][j][k];
            }
            lhs[n + 2][i1][j][k] = lhs[n + 2][i1][j][k] - lhs[n + 1][i1][j][k] * lhs[n + 3][i][j][k];
            lhs[n + 3][i1][j][k] = lhs[n + 3][i1][j][k] - lhs[n + 1][i1][j][k] * lhs[n + 4][i][j][k];
            for(m = 0; m < 3; m++)
            {
                rhs[m][i1][j][k] = rhs[m][i1][j][k] - lhs[n + 1][i1][j][k] * rhs[m][i][j][k];
            }
            fac2 = 1.0 / lhs[n + 2][i1][j][k];
            for(m = 0; m < 3; m++)
            {
                rhs[m][i1][j][k] = fac2 * rhs[m][i1][j][k];
            }
        }
    }

#pragma endscop
}
