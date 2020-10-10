#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int  grid_points[3] ;
extern int j;
extern double fac1;
extern double  lhs[15][64 / 2 * 2 + 1][64 / 2 * 2 + 1][64 / 2 * 2 + 1] ;
extern int n;
extern int k;
extern int m;
extern double  rhs[5][64 / 2 * 2 + 1][64 / 2 * 2 + 1][64 / 2 * 2 + 1] ;
extern int k1;
extern double fac2;

void loop()
{
#pragma scop

    for(i = 1; i <= grid_points[0] - 2; i++)
    {
        for(j = 1; j <= grid_points[1] - 2; j++)
        {
            fac1 = 1.0 / lhs[n + 2][i][j][k];
            lhs[n + 3][i][j][k] = fac1 * lhs[n + 3][i][j][k];
            lhs[n + 4][i][j][k] = fac1 * lhs[n + 4][i][j][k];
            for(m = 0; m < 3; m++)
            {
                rhs[m][i][j][k] = fac1 * rhs[m][i][j][k];
            }
            lhs[n + 2][i][j][k1] = lhs[n + 2][i][j][k1] - lhs[n + 1][i][j][k1] * lhs[n + 3][i][j][k];
            lhs[n + 3][i][j][k1] = lhs[n + 3][i][j][k1] - lhs[n + 1][i][j][k1] * lhs[n + 4][i][j][k];
            for(m = 0; m < 3; m++)
            {
                rhs[m][i][j][k1] = rhs[m][i][j][k1] - lhs[n + 1][i][j][k1] * rhs[m][i][j][k];
            }
            fac2 = 1.0 / lhs[n + 2][i][j][k1];
            for(m = 0; m < 3; m++)
            {
                rhs[m][i][j][k1] = fac2 * rhs[m][i][j][k1];
            }
        }
    }

#pragma endscop
}
