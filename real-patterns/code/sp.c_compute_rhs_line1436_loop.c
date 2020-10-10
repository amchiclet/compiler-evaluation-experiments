#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int m;
extern int j;
extern int  grid_points[3] ;
extern int k;
extern double  rhs[5][64 / 2 * 2 + 1][64 / 2 * 2 + 1][64 / 2 * 2 + 1] ;
extern int i;
extern double dssp;
extern double  u[5][64 / 2 * 2 + 1][64 / 2 * 2 + 1][64 / 2 * 2 + 1] ;

void loop()
{
#pragma scop

    for(m = 0; m < 5; m++)
    {
        for(j = 1; j <= grid_points[1] - 2; j++)
        {
            for(k = 1; k <= grid_points[2] - 2; k++)
            {
                rhs[m][i][j][k] = rhs[m][i][j][k] - dssp *(u[m][i - 2][j][k] - 4.0 * u[m][i - 1][j][k] + 5.0 * u[m][i][j][k]);
            }
        }
    }

#pragma endscop
}
