#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int  grid_points[3] ;
extern int j;
extern int k;
extern int m;
extern double  lhs[64 / 2 * 2 + 1][64 / 2 * 2 + 1][64 / 2 * 2 + 1][3][5][5] ;

void loop()
{
#pragma scop

    for(i = 0; i < grid_points[0]; i++)
    {
        for(j = 0; j < grid_points[1]; j++)
        {
            for(k = 0; k < grid_points[2]; k++)
            {
                for(m = 0; m < 5; m++)
                {
                    lhs[i][j][k][1][m][m] = 1.0;
                }
            }
        }
    }

#pragma endscop
}
