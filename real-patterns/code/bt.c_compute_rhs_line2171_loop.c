#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int j;
extern int  grid_points[3] ;
extern int k;
extern int m;
extern int i;
extern double  rhs[64 / 2 * 2 + 1][64 / 2 * 2 + 1][64 / 2 * 2 + 1][5] ;
extern double dt;

void loop()
{
#pragma scop

    for(j = 1; j < grid_points[1] - 1; j++)
    {
        for(k = 1; k < grid_points[2] - 1; k++)
        {
            for(m = 0; m < 5; m++)
            {
                for(i = 1; i < grid_points[0] - 1; i++)
                {
                    rhs[i][j][k][m] = rhs[i][j][k][m] * dt;
                }
            }
        }
    }

#pragma endscop
}
