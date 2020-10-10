#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int  grid_points[3] ;
extern int j;
extern int k;
extern int m;
extern double  forcing[64 / 2 * 2 + 1][64 / 2 * 2 + 1][64 / 2 * 2 + 1][5 + 1] ;

void loop()
{
#pragma scop

    for(i = 1; i < grid_points[0] - 1; i++)
    {
        for(j = 1; j < grid_points[1] - 1; j++)
        {
            for(k = 1; k < grid_points[2] - 1; k++)
            {
                for(m = 0; m < 5; m++)
                {
                    forcing[i][j][k][m] = - 1.0 * forcing[i][j][k][m];
                }
            }
        }
    }

#pragma endscop
}
