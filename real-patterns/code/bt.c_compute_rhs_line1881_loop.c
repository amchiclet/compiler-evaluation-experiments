#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int j;
extern int  grid_points[3] ;
extern int k;
extern int m;
extern double  rhs[64 / 2 * 2 + 1][64 / 2 * 2 + 1][64 / 2 * 2 + 1][5] ;
extern int i;
extern double dssp;
extern double  u[(64 + 1) / 2 * 2 + 1][(64 + 1) / 2 * 2 + 1][(64 + 1) / 2 * 2 + 1][5] ;

void loop()
{
#pragma scop

    for(j = 1; j < grid_points[1] - 1; j++)
    {
        for(k = 1; k < grid_points[2] - 1; k++)
        {
            for(m = 0; m < 5; m++)
            {
                rhs[i][j][k][m] = rhs[i][j][k][m] - dssp *(- 4.0 * u[i - 1][j][k][m] + 6.0 * u[i][j][k][m] - 4.0 * u[i + 1][j][k][m] + u[i + 2][j][k][m]);
            }
        }
    }

#pragma endscop
}
