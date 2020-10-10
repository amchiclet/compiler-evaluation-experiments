#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int m;
extern int i;
extern int  grid_points[3] ;
extern int k;
extern double  rhs[5][64 / 2 * 2 + 1][64 / 2 * 2 + 1][64 / 2 * 2 + 1] ;
extern int j;
extern double dssp;
extern double  u[5][64 / 2 * 2 + 1][64 / 2 * 2 + 1][64 / 2 * 2 + 1] ;

void loop()
{
#pragma scop

    for(m = 0; m < 5; m++)
    {
        for(i = 1; i <= grid_points[0] - 2; i++)
        {
            for(k = 1; k <= grid_points[2] - 2; k++)
            {
                rhs[m][i][j][k] = rhs[m][i][j][k] - dssp *(- 4.0 * u[m][i][j - 1][k] + 6.0 * u[m][i][j][k] - 4.0 * u[m][i][j + 1][k] + u[m][i][j + 2][k]);
            }
        }
    }

#pragma endscop
}
