#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int m;
extern int i;
extern int  grid_points[3] ;
extern int j;
extern int k;
extern double  forcing[5][64 / 2 * 2 + 1][64 / 2 * 2 + 1][64 / 2 * 2 + 1] ;

void loop()
{
#pragma scop

    for(m = 0; m < 5; m++)
    {
        for(i = 0; i <= grid_points[0] - 1; i++)
        {
            for(j = 0; j <= grid_points[1] - 1; j++)
            {
                for(k = 0; k <= grid_points[2] - 1; k++)
                {
                    forcing[m][i][j][k] = 0.0;
                }
            }
        }
    }

#pragma endscop
}
