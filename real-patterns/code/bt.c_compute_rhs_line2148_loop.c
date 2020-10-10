#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int  grid_points[3] ;
extern int j;
extern int m;
extern double  rhs[64 / 2 * 2 + 1][64 / 2 * 2 + 1][64 / 2 * 2 + 1][5] ;
extern int k;
extern double dssp;
extern double  u[(64 + 1) / 2 * 2 + 1][(64 + 1) / 2 * 2 + 1][(64 + 1) / 2 * 2 + 1][5] ;

void loop()
{
#pragma scop

    for(i = 1; i < grid_points[0] - 1; i++)
    {
        for(j = 1; j < grid_points[1] - 1; j++)
        {
            for(m = 0; m < 5; m++)
            {
                rhs[i][j][k][m] = rhs[i][j][k][m] - dssp *(u[i][j][k - 2][m] - 4.0 * u[i][j][k - 1][m] + 6.0 * u[i][j][k][m] - 4.0 * u[i][j][k + 1][m]);
            }
        }
    }

#pragma endscop
}
