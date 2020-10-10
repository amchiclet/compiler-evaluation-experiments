#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int m;
extern int i;
extern int  grid_points[3] ;
extern int k;
extern int n;
extern double  rhs[5][64 / 2 * 2 + 1][64 / 2 * 2 + 1][64 / 2 * 2 + 1] ;
extern int j;
extern double  lhs[15][64 / 2 * 2 + 1][64 / 2 * 2 + 1][64 / 2 * 2 + 1] ;
extern int j1;

void loop()
{
#pragma scop

    for(m = 3; m < 5; m++)
    {
        for(i = 1; i <= grid_points[0] - 2; i++)
        {
            for(k = 1; k <= grid_points[2] - 2; k++)
            {
                n =(m - 3 + 1) * 5;
                rhs[m][i][j][k] = rhs[m][i][j][k] - lhs[n + 3][i][j][k] * rhs[m][i][j1][k];
            }
        }
    }

#pragma endscop
}
