#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int j;
extern int  grid_points[3] ;
extern int k;
extern double  lhs[15][64 / 2 * 2 + 1][64 / 2 * 2 + 1][64 / 2 * 2 + 1] ;
extern int i;
extern double comz5;
extern double comz4;
extern double comz1;
extern double comz6;

void loop()
{
#pragma scop

    for(j = 1; j <= grid_points[1] - 2; j++)
    {
        for(k = 1; k <= grid_points[2] - 2; k++)
        {
            lhs[2][i][j][k] = lhs[2][i][j][k] + comz5;
            lhs[3][i][j][k] = lhs[3][i][j][k] - comz4;
            lhs[4][i][j][k] = lhs[4][i][j][k] + comz1;
            lhs[1][i + 1][j][k] = lhs[1][i + 1][j][k] - comz4;
            lhs[2][i + 1][j][k] = lhs[2][i + 1][j][k] + comz6;
            lhs[3][i + 1][j][k] = lhs[3][i + 1][j][k] - comz4;
            lhs[4][i + 1][j][k] = lhs[4][i + 1][j][k] + comz1;
        }
    }

#pragma endscop
}
