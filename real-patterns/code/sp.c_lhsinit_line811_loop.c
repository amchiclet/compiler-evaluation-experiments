#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int n;
extern int i;
extern int  grid_points[3] ;
extern int j;
extern int k;
extern double  lhs[15][64 / 2 * 2 + 1][64 / 2 * 2 + 1][64 / 2 * 2 + 1] ;

void loop()
{
#pragma scop

    for(n = 0; n < 15; n++)
    {
        for(i = 0; i < grid_points[0]; i++)
        {
            for(j = 0; j < grid_points[1]; j++)
            {
                for(k = 0; k < grid_points[2]; k++)
                {
                    lhs[n][i][j][k] = 0.0;
                }
            }
        }
    }

#pragma endscop
}
