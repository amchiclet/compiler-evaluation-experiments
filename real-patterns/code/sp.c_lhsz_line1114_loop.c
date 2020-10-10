#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int  grid_points[3] ;
extern int j;
extern double  lhs[15][64 / 2 * 2 + 1][64 / 2 * 2 + 1][64 / 2 * 2 + 1] ;
extern int k;
extern double comz5;
extern double comz4;
extern double comz1;
extern double comz6;

void loop()
{
#pragma scop

    for(i = 1; i <= grid_points[0] - 2; i++)
    {
        for(j = 1; j <= grid_points[1] - 2; j++)
        {
            lhs[2][i][j][k] = lhs[2][i][j][k] + comz5;
            lhs[3][i][j][k] = lhs[3][i][j][k] - comz4;
            lhs[4][i][j][k] = lhs[4][i][j][k] + comz1;
            lhs[1][i][j][k + 1] = lhs[1][i][j][k + 1] - comz4;
            lhs[2][i][j][k + 1] = lhs[2][i][j][k + 1] + comz6;
            lhs[3][i][j][k + 1] = lhs[3][i][j][k + 1] - comz4;
            lhs[4][i][j][k + 1] = lhs[4][i][j][k + 1] + comz1;
        }
    }

#pragma endscop
}
