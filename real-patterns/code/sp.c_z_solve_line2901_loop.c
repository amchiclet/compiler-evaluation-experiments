#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int m;
extern int i;
extern int  grid_points[3] ;
extern int j;
extern double  rhs[5][64 / 2 * 2 + 1][64 / 2 * 2 + 1][64 / 2 * 2 + 1] ;
extern int k;
extern double  lhs[15][64 / 2 * 2 + 1][64 / 2 * 2 + 1][64 / 2 * 2 + 1] ;
extern int n;
extern int k1;

void loop()
{
#pragma scop

    for(m = 0; m < 3; m++)
    {
        for(i = 1; i <= grid_points[0] - 2; i++)
        {
            for(j = 1; j <= grid_points[1] - 2; j++)
            {
                rhs[m][i][j][k] = rhs[m][i][j][k] - lhs[n + 3][i][j][k] * rhs[m][i][j][k1];
            }
        }
    }

#pragma endscop
}
