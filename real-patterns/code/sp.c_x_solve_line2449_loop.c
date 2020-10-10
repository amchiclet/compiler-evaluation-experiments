#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int m;
extern int j;
extern int  grid_points[3] ;
extern int k;
extern double  rhs[5][64 / 2 * 2 + 1][64 / 2 * 2 + 1][64 / 2 * 2 + 1] ;
extern int i;
extern double  lhs[15][64 / 2 * 2 + 1][64 / 2 * 2 + 1][64 / 2 * 2 + 1] ;
extern int n;
extern int i1;

void loop()
{
#pragma scop

    for(m = 0; m < 3; m++)
    {
        for(j = 1; j <= grid_points[1] - 2; j++)
        {
            for(k = 1; k <= grid_points[2] - 2; k++)
            {
                rhs[m][i][j][k] = rhs[m][i][j][k] - lhs[n + 3][i][j][k] * rhs[m][i1][j][k];
            }
        }
    }

#pragma endscop
}
