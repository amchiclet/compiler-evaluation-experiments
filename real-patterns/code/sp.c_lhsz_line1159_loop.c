#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int  grid_points[3] ;
extern int j;
extern int k;
extern double  lhs[15][64 / 2 * 2 + 1][64 / 2 * 2 + 1][64 / 2 * 2 + 1] ;
extern double dttz2;
extern double  speed[64 / 2 * 2 + 1][64 / 2 * 2 + 1][64 / 2 * 2 + 1] ;

void loop()
{
#pragma scop

    for(i = 1; i <= grid_points[0] - 2; i++)
    {
        for(j = 1; j <= grid_points[1] - 2; j++)
        {
            for(k = 1; k <= grid_points[2] - 2; k++)
            {
                lhs[0 + 5][i][j][k] = lhs[0][i][j][k];
                lhs[1 + 5][i][j][k] = lhs[1][i][j][k] - dttz2 * speed[i][j][k - 1];
                lhs[2 + 5][i][j][k] = lhs[2][i][j][k];
                lhs[3 + 5][i][j][k] = lhs[3][i][j][k] + dttz2 * speed[i][j][k + 1];
                lhs[4 + 5][i][j][k] = lhs[4][i][j][k];
                lhs[0 + '\n'][i][j][k] = lhs[0][i][j][k];
                lhs[1 + '\n'][i][j][k] = lhs[1][i][j][k] + dttz2 * speed[i][j][k - 1];
                lhs[2 + '\n'][i][j][k] = lhs[2][i][j][k];
                lhs[3 + '\n'][i][j][k] = lhs[3][i][j][k] - dttz2 * speed[i][j][k + 1];
                lhs[4 + '\n'][i][j][k] = lhs[4][i][j][k];
            }
        }
    }

#pragma endscop
}
