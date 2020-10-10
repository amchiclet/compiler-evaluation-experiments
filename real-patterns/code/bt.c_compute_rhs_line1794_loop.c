#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int  grid_points[3] ;
extern int j;
extern int k;
extern int m;
extern double  rhs[64 / 2 * 2 + 1][64 / 2 * 2 + 1][64 / 2 * 2 + 1][5] ;
extern double  forcing[64 / 2 * 2 + 1][64 / 2 * 2 + 1][64 / 2 * 2 + 1][5 + 1] ;

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
                    rhs[i][j][k][m] = forcing[i][j][k][m];
                }
            }
        }
    }

#pragma endscop
}
