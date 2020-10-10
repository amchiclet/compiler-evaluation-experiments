#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int  grid_points[3] ;
extern int j;
extern int k;
extern int m;
extern double add;
extern double  rhs[5][64 / 2 * 2 + 1][64 / 2 * 2 + 1][64 / 2 * 2 + 1] ;
extern double  rms[5] ;

void loop()
{
#pragma scop

    for(i = 0; i <= grid_points[0] - 2; i++)
    {
        for(j = 0; j <= grid_points[1] - 2; j++)
        {
            for(k = 0; k <= grid_points[2] - 2; k++)
            {
                for(m = 0; m < 5; m++)
                {
                    add = rhs[m][i][j][k];
                    rms[m] = rms[m] + add * add;
                }
            }
        }
    }

#pragma endscop
}
