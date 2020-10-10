#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int  grid_points[3] ;
extern int j;
extern int k;
extern double r1;
extern double  rhs[5][64 / 2 * 2 + 1][64 / 2 * 2 + 1][64 / 2 * 2 + 1] ;
extern double r2;
extern double r3;
extern double r4;
extern double r5;
extern double t1;
extern double bt;
extern double t2;

void loop()
{
#pragma scop

    for(i = 1; i <= grid_points[0] - 2; i++)
    {
        for(j = 1; j <= grid_points[1] - 2; j++)
        {
            for(k = 1; k <= grid_points[2] - 2; k++)
            {
                r1 = rhs[0][i][j][k];
                r2 = rhs[1][i][j][k];
                r3 = rhs[2][i][j][k];
                r4 = rhs[3][i][j][k];
                r5 = rhs[4][i][j][k];
                t1 = bt * r3;
                t2 = 0.5 *(r4 + r5);
                rhs[0][i][j][k] = -r2;
                rhs[1][i][j][k] = r1;
                rhs[2][i][j][k] = bt *(r4 - r5);
                rhs[3][i][j][k] = -t1 + t2;
                rhs[4][i][j][k] = t1 + t2;
            }
        }
    }

#pragma endscop
}
