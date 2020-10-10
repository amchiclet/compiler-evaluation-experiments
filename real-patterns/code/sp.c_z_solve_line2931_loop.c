#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int m;
extern int i;
extern int  grid_points[3] ;
extern int j;
extern int k;
extern double  rhs[5][64 / 2 * 2 + 1][64 / 2 * 2 + 1][64 / 2 * 2 + 1] ;
extern double  lhs[15][64 / 2 * 2 + 1][64 / 2 * 2 + 1][64 / 2 * 2 + 1] ;
extern int n;

void loop()
{
#pragma scop

    for(m = 0; m < 3; m++)
    {
        for(i = 1; i <= grid_points[0] - 2; i++)
        {
            for(j = 1; j <= grid_points[1] - 2; j++)
            {
                k = grid_points[2] - 3;
                double rhs_kup1 = rhs[m][i][j][k + 1];
                double rhs_kup2 = rhs[m][i][j][k + 2];
                double rhs_mijk;
                for(k = k; k >= 0; k--)
                {
                    rhs_mijk = rhs[m][i][j][k] - lhs[n + 3][i][j][k] * rhs_kup1 - lhs[n + 4][i][j][k] * rhs_kup2;
                    rhs[m][i][j][k] = rhs_mijk;
                    rhs_kup2 = rhs_kup1;
                    rhs_kup1 = rhs_mijk;
                }
            }
        }
    }

#pragma endscop
}
