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
        for(i = 1; i <= grid_points[0] - 2; i++)
        {
            for(j = 1; j <= grid_points[1] - 2; j++)
            {
                for(k = 1; k <= grid_points[2] - 2; k++)
                {
                    forcing[m][i][j][k] = - 1.0 * forcing[m][i][j][k];
                }
            }
        }
    }

#pragma endscop
}
