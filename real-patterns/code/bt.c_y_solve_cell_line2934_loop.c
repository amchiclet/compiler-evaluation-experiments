#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int  grid_points[3] ;
extern int k;
extern double  rhs[64 / 2 * 2 + 1][64 / 2 * 2 + 1][64 / 2 * 2 + 1][5] ;
extern int jsize;
extern double  lhs[64 / 2 * 2 + 1][64 / 2 * 2 + 1][64 / 2 * 2 + 1][3][5][5] ;

void loop()
{
#pragma scop

    for(i = 1; i < grid_points[0] - 1; i++)
    {
        for(k = 1; k < grid_points[2] - 1; k++)
        {
            {
                int l;
                for(l = 0; l < 5; l++)
                {
                    rhs[i][jsize][k][l] = rhs[i][jsize][k][l] - lhs[i][jsize][k][0][l][0] * rhs[i][jsize - 1][k][0] - lhs[i][jsize][k][0][l][1] * rhs[i][jsize - 1][k][1] - lhs[i][jsize][k][0][l][2] * rhs[i][jsize - 1][k][2] - lhs[i][jsize][k][0][l][3] * rhs[i][jsize - 1][k][3] - lhs[i][jsize][k][0][l][4] * rhs[i][jsize - 1][k][4];
                }
            };
            {
                int l;
                for(l = 0; l < 5; l++)
                {
                    lhs[i][jsize][k][1][0][l] = lhs[i][jsize][k][1][0][l] - lhs[i][jsize][k][0][0][0] * lhs[i][jsize - 1][k][2][0][l] - lhs[i][jsize][k][0][0][1] * lhs[i][jsize - 1][k][2][1][l] - lhs[i][jsize][k][0][0][2] * lhs[i][jsize - 1][k][2][2][l] - lhs[i][jsize][k][0][0][3] * lhs[i][jsize - 1][k][2][3][l] - lhs[i][jsize][k][0][0][4] * lhs[i][jsize - 1][k][2][4][l];
                    lhs[i][jsize][k][1][1][l] = lhs[i][jsize][k][1][1][l] - lhs[i][jsize][k][0][1][0] * lhs[i][jsize - 1][k][2][0][l] - lhs[i][jsize][k][0][1][1] * lhs[i][jsize - 1][k][2][1][l] - lhs[i][jsize][k][0][1][2] * lhs[i][jsize - 1][k][2][2][l] - lhs[i][jsize][k][0][1][3] * lhs[i][jsize - 1][k][2][3][l] - lhs[i][jsize][k][0][1][4] * lhs[i][jsize - 1][k][2][4][l];
                    lhs[i][jsize][k][1][2][l] = lhs[i][jsize][k][1][2][l] - lhs[i][jsize][k][0][2][0] * lhs[i][jsize - 1][k][2][0][l] - lhs[i][jsize][k][0][2][1] * lhs[i][jsize - 1][k][2][1][l] - lhs[i][jsize][k][0][2][2] * lhs[i][jsize - 1][k][2][2][l] - lhs[i][jsize][k][0][2][3] * lhs[i][jsize - 1][k][2][3][l] - lhs[i][jsize][k][0][2][4] * lhs[i][jsize - 1][k][2][4][l];
                    lhs[i][jsize][k][1][3][l] = lhs[i][jsize][k][1][3][l] - lhs[i][jsize][k][0][3][0] * lhs[i][jsize - 1][k][2][0][l] - lhs[i][jsize][k][0][3][1] * lhs[i][jsize - 1][k][2][1][l] - lhs[i][jsize][k][0][3][2] * lhs[i][jsize - 1][k][2][2][l] - lhs[i][jsize][k][0][3][3] * lhs[i][jsize - 1][k][2][3][l] - lhs[i][jsize][k][0][3][4] * lhs[i][jsize - 1][k][2][4][l];
                    lhs[i][jsize][k][1][4][l] = lhs[i][jsize][k][1][4][l] - lhs[i][jsize][k][0][4][0] * lhs[i][jsize - 1][k][2][0][l] - lhs[i][jsize][k][0][4][1] * lhs[i][jsize - 1][k][2][1][l] - lhs[i][jsize][k][0][4][2] * lhs[i][jsize - 1][k][2][2][l] - lhs[i][jsize][k][0][4][3] * lhs[i][jsize - 1][k][2][3][l] - lhs[i][jsize][k][0][4][4] * lhs[i][jsize - 1][k][2][4][l];
                }
            };
            {
                static double pivot;
                static double coeff;
                pivot = 1.0 / lhs[i][jsize][k][1][0][0];
                lhs[i][jsize][k][1][0][1] = lhs[i][jsize][k][1][0][1] * pivot;
                lhs[i][jsize][k][1][0][2] = lhs[i][jsize][k][1][0][2] * pivot;
                lhs[i][jsize][k][1][0][3] = lhs[i][jsize][k][1][0][3] * pivot;
                lhs[i][jsize][k][1][0][4] = lhs[i][jsize][k][1][0][4] * pivot;
                rhs[i][jsize][k][0] = rhs[i][jsize][k][0] * pivot;
                coeff = lhs[i][jsize][k][1][1][0];
                lhs[i][jsize][k][1][1][1] = lhs[i][jsize][k][1][1][1] - coeff * lhs[i][jsize][k][1][0][1];
                lhs[i][jsize][k][1][1][2] = lhs[i][jsize][k][1][1][2] - coeff * lhs[i][jsize][k][1][0][2];
                lhs[i][jsize][k][1][1][3] = lhs[i][jsize][k][1][1][3] - coeff * lhs[i][jsize][k][1][0][3];
                lhs[i][jsize][k][1][1][4] = lhs[i][jsize][k][1][1][4] - coeff * lhs[i][jsize][k][1][0][4];
                rhs[i][jsize][k][1] = rhs[i][jsize][k][1] - coeff * rhs[i][jsize][k][0];
                coeff = lhs[i][jsize][k][1][2][0];
                lhs[i][jsize][k][1][2][1] = lhs[i][jsize][k][1][2][1] - coeff * lhs[i][jsize][k][1][0][1];
                lhs[i][jsize][k][1][2][2] = lhs[i][jsize][k][1][2][2] - coeff * lhs[i][jsize][k][1][0][2];
                lhs[i][jsize][k][1][2][3] = lhs[i][jsize][k][1][2][3] - coeff * lhs[i][jsize][k][1][0][3];
                lhs[i][jsize][k][1][2][4] = lhs[i][jsize][k][1][2][4] - coeff * lhs[i][jsize][k][1][0][4];
                rhs[i][jsize][k][2] = rhs[i][jsize][k][2] - coeff * rhs[i][jsize][k][0];
                coeff = lhs[i][jsize][k][1][3][0];
                lhs[i][jsize][k][1][3][1] = lhs[i][jsize][k][1][3][1] - coeff * lhs[i][jsize][k][1][0][1];
                lhs[i][jsize][k][1][3][2] = lhs[i][jsize][k][1][3][2] - coeff * lhs[i][jsize][k][1][0][2];
                lhs[i][jsize][k][1][3][3] = lhs[i][jsize][k][1][3][3] - coeff * lhs[i][jsize][k][1][0][3];
                lhs[i][jsize][k][1][3][4] = lhs[i][jsize][k][1][3][4] - coeff * lhs[i][jsize][k][1][0][4];
                rhs[i][jsize][k][3] = rhs[i][jsize][k][3] - coeff * rhs[i][jsize][k][0];
                coeff = lhs[i][jsize][k][1][4][0];
                lhs[i][jsize][k][1][4][1] = lhs[i][jsize][k][1][4][1] - coeff * lhs[i][jsize][k][1][0][1];
                lhs[i][jsize][k][1][4][2] = lhs[i][jsize][k][1][4][2] - coeff * lhs[i][jsize][k][1][0][2];
                lhs[i][jsize][k][1][4][3] = lhs[i][jsize][k][1][4][3] - coeff * lhs[i][jsize][k][1][0][3];
                lhs[i][jsize][k][1][4][4] = lhs[i][jsize][k][1][4][4] - coeff * lhs[i][jsize][k][1][0][4];
                rhs[i][jsize][k][4] = rhs[i][jsize][k][4] - coeff * rhs[i][jsize][k][0];
                pivot = 1.0 / lhs[i][jsize][k][1][1][1];
                lhs[i][jsize][k][1][1][2] = lhs[i][jsize][k][1][1][2] * pivot;
                lhs[i][jsize][k][1][1][3] = lhs[i][jsize][k][1][1][3] * pivot;
                lhs[i][jsize][k][1][1][4] = lhs[i][jsize][k][1][1][4] * pivot;
                rhs[i][jsize][k][1] = rhs[i][jsize][k][1] * pivot;
                coeff = lhs[i][jsize][k][1][0][1];
                lhs[i][jsize][k][1][0][2] = lhs[i][jsize][k][1][0][2] - coeff * lhs[i][jsize][k][1][1][2];
                lhs[i][jsize][k][1][0][3] = lhs[i][jsize][k][1][0][3] - coeff * lhs[i][jsize][k][1][1][3];
                lhs[i][jsize][k][1][0][4] = lhs[i][jsize][k][1][0][4] - coeff * lhs[i][jsize][k][1][1][4];
                rhs[i][jsize][k][0] = rhs[i][jsize][k][0] - coeff * rhs[i][jsize][k][1];
                coeff = lhs[i][jsize][k][1][2][1];
                lhs[i][jsize][k][1][2][2] = lhs[i][jsize][k][1][2][2] - coeff * lhs[i][jsize][k][1][1][2];
                lhs[i][jsize][k][1][2][3] = lhs[i][jsize][k][1][2][3] - coeff * lhs[i][jsize][k][1][1][3];
                lhs[i][jsize][k][1][2][4] = lhs[i][jsize][k][1][2][4] - coeff * lhs[i][jsize][k][1][1][4];
                rhs[i][jsize][k][2] = rhs[i][jsize][k][2] - coeff * rhs[i][jsize][k][1];
                coeff = lhs[i][jsize][k][1][3][1];
                lhs[i][jsize][k][1][3][2] = lhs[i][jsize][k][1][3][2] - coeff * lhs[i][jsize][k][1][1][2];
                lhs[i][jsize][k][1][3][3] = lhs[i][jsize][k][1][3][3] - coeff * lhs[i][jsize][k][1][1][3];
                lhs[i][jsize][k][1][3][4] = lhs[i][jsize][k][1][3][4] - coeff * lhs[i][jsize][k][1][1][4];
                rhs[i][jsize][k][3] = rhs[i][jsize][k][3] - coeff * rhs[i][jsize][k][1];
                coeff = lhs[i][jsize][k][1][4][1];
                lhs[i][jsize][k][1][4][2] = lhs[i][jsize][k][1][4][2] - coeff * lhs[i][jsize][k][1][1][2];
                lhs[i][jsize][k][1][4][3] = lhs[i][jsize][k][1][4][3] - coeff * lhs[i][jsize][k][1][1][3];
                lhs[i][jsize][k][1][4][4] = lhs[i][jsize][k][1][4][4] - coeff * lhs[i][jsize][k][1][1][4];
                rhs[i][jsize][k][4] = rhs[i][jsize][k][4] - coeff * rhs[i][jsize][k][1];
                pivot = 1.0 / lhs[i][jsize][k][1][2][2];
                lhs[i][jsize][k][1][2][3] = lhs[i][jsize][k][1][2][3] * pivot;
                lhs[i][jsize][k][1][2][4] = lhs[i][jsize][k][1][2][4] * pivot;
                rhs[i][jsize][k][2] = rhs[i][jsize][k][2] * pivot;
                coeff = lhs[i][jsize][k][1][0][2];
                lhs[i][jsize][k][1][0][3] = lhs[i][jsize][k][1][0][3] - coeff * lhs[i][jsize][k][1][2][3];
                lhs[i][jsize][k][1][0][4] = lhs[i][jsize][k][1][0][4] - coeff * lhs[i][jsize][k][1][2][4];
                rhs[i][jsize][k][0] = rhs[i][jsize][k][0] - coeff * rhs[i][jsize][k][2];
                coeff = lhs[i][jsize][k][1][1][2];
                lhs[i][jsize][k][1][1][3] = lhs[i][jsize][k][1][1][3] - coeff * lhs[i][jsize][k][1][2][3];
                lhs[i][jsize][k][1][1][4] = lhs[i][jsize][k][1][1][4] - coeff * lhs[i][jsize][k][1][2][4];
                rhs[i][jsize][k][1] = rhs[i][jsize][k][1] - coeff * rhs[i][jsize][k][2];
                coeff = lhs[i][jsize][k][1][3][2];
                lhs[i][jsize][k][1][3][3] = lhs[i][jsize][k][1][3][3] - coeff * lhs[i][jsize][k][1][2][3];
                lhs[i][jsize][k][1][3][4] = lhs[i][jsize][k][1][3][4] - coeff * lhs[i][jsize][k][1][2][4];
                rhs[i][jsize][k][3] = rhs[i][jsize][k][3] - coeff * rhs[i][jsize][k][2];
                coeff = lhs[i][jsize][k][1][4][2];
                lhs[i][jsize][k][1][4][3] = lhs[i][jsize][k][1][4][3] - coeff * lhs[i][jsize][k][1][2][3];
                lhs[i][jsize][k][1][4][4] = lhs[i][jsize][k][1][4][4] - coeff * lhs[i][jsize][k][1][2][4];
                rhs[i][jsize][k][4] = rhs[i][jsize][k][4] - coeff * rhs[i][jsize][k][2];
                pivot = 1.0 / lhs[i][jsize][k][1][3][3];
                lhs[i][jsize][k][1][3][4] = lhs[i][jsize][k][1][3][4] * pivot;
                rhs[i][jsize][k][3] = rhs[i][jsize][k][3] * pivot;
                coeff = lhs[i][jsize][k][1][0][3];
                lhs[i][jsize][k][1][0][4] = lhs[i][jsize][k][1][0][4] - coeff * lhs[i][jsize][k][1][3][4];
                rhs[i][jsize][k][0] = rhs[i][jsize][k][0] - coeff * rhs[i][jsize][k][3];
                coeff = lhs[i][jsize][k][1][1][3];
                lhs[i][jsize][k][1][1][4] = lhs[i][jsize][k][1][1][4] - coeff * lhs[i][jsize][k][1][3][4];
                rhs[i][jsize][k][1] = rhs[i][jsize][k][1] - coeff * rhs[i][jsize][k][3];
                coeff = lhs[i][jsize][k][1][2][3];
                lhs[i][jsize][k][1][2][4] = lhs[i][jsize][k][1][2][4] - coeff * lhs[i][jsize][k][1][3][4];
                rhs[i][jsize][k][2] = rhs[i][jsize][k][2] - coeff * rhs[i][jsize][k][3];
                coeff = lhs[i][jsize][k][1][4][3];
                lhs[i][jsize][k][1][4][4] = lhs[i][jsize][k][1][4][4] - coeff * lhs[i][jsize][k][1][3][4];
                rhs[i][jsize][k][4] = rhs[i][jsize][k][4] - coeff * rhs[i][jsize][k][3];
                pivot = 1.0 / lhs[i][jsize][k][1][4][4];
                rhs[i][jsize][k][4] = rhs[i][jsize][k][4] * pivot;
                coeff = lhs[i][jsize][k][1][0][4];
                rhs[i][jsize][k][0] = rhs[i][jsize][k][0] - coeff * rhs[i][jsize][k][4];
                coeff = lhs[i][jsize][k][1][1][4];
                rhs[i][jsize][k][1] = rhs[i][jsize][k][1] - coeff * rhs[i][jsize][k][4];
                coeff = lhs[i][jsize][k][1][2][4];
                rhs[i][jsize][k][2] = rhs[i][jsize][k][2] - coeff * rhs[i][jsize][k][4];
                coeff = lhs[i][jsize][k][1][3][4];
                rhs[i][jsize][k][3] = rhs[i][jsize][k][3] - coeff * rhs[i][jsize][k][4];
            };
        }
    }

#pragma endscop
}
