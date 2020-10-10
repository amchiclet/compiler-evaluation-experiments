#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int  grid_points[3] ;
extern int j;
extern int k;
extern int m;
extern double  rhs[64 / 2 * 2 + 1][64 / 2 * 2 + 1][64 / 2 * 2 + 1][5] ;
extern double dssp;
extern double  u[(64 + 1) / 2 * 2 + 1][(64 + 1) / 2 * 2 + 1][(64 + 1) / 2 * 2 + 1][5] ;

void loop()
{
#pragma scop

    for(i = 1; i < grid_points[0] - 1; i++)
    {
        for(j = 3; j < grid_points[1] - 3; j++)
        {
            for(k = 1; k < grid_points[2] - 1; k++)
            {
                for(m = 0; m < 5; m++)
                {
                    rhs[i][j][k][m] = rhs[i][j][k][m] - dssp *(u[i][j - 2][k][m] - 4.0 * u[i][j - 1][k][m] + 6.0 * u[i][j][k][m] - 4.0 * u[i][j + 1][k][m] + u[i][j + 2][k][m]);
                }
            }
        }
    }

#pragma endscop
}
