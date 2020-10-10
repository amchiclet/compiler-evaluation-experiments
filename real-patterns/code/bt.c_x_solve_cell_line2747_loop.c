#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int isize;
extern int j;
extern int  grid_points[3] ;
extern int k;
extern double  rhs[64 / 2 * 2 + 1][64 / 2 * 2 + 1][64 / 2 * 2 + 1][5] ;
extern double  lhs[64 / 2 * 2 + 1][64 / 2 * 2 + 1][64 / 2 * 2 + 1][3][5][5] ;

void loop()
{
#pragma scop

    for(i = 1; i < isize; i++)
    {
        for(j = 1; j < grid_points[1] - 1; j++)
        {
            for(k = 1; k < grid_points[2] - 1; k++)
            {
                {
                    int l;
                    for(l = 0; l < 5; l++)
                    {
                        rhs[i][j][k][l] = rhs[i][j][k][l] - lhs[i][j][k][0][l][0] * rhs[i - 1][j][k][0] - lhs[i][j][k][0][l][1] * rhs[i - 1][j][k][1] - lhs[i][j][k][0][l][2] * rhs[i - 1][j][k][2] - lhs[i][j][k][0][l][3] * rhs[i - 1][j][k][3] - lhs[i][j][k][0][l][4] * rhs[i - 1][j][k][4];
                    }
                };
                {
                    int l;
                    for(l = 0; l < 5; l++)
                    {
                        lhs[i][j][k][1][0][l] = lhs[i][j][k][1][0][l] - lhs[i][j][k][0][0][0] * lhs[i - 1][j][k][2][0][l] - lhs[i][j][k][0][0][1] * lhs[i - 1][j][k][2][1][l] - lhs[i][j][k][0][0][2] * lhs[i - 1][j][k][2][2][l] - lhs[i][j][k][0][0][3] * lhs[i - 1][j][k][2][3][l] - lhs[i][j][k][0][0][4] * lhs[i - 1][j][k][2][4][l];
                        lhs[i][j][k][1][1][l] = lhs[i][j][k][1][1][l] - lhs[i][j][k][0][1][0] * lhs[i - 1][j][k][2][0][l] - lhs[i][j][k][0][1][1] * lhs[i - 1][j][k][2][1][l] - lhs[i][j][k][0][1][2] * lhs[i - 1][j][k][2][2][l] - lhs[i][j][k][0][1][3] * lhs[i - 1][j][k][2][3][l] - lhs[i][j][k][0][1][4] * lhs[i - 1][j][k][2][4][l];
                        lhs[i][j][k][1][2][l] = lhs[i][j][k][1][2][l] - lhs[i][j][k][0][2][0] * lhs[i - 1][j][k][2][0][l] - lhs[i][j][k][0][2][1] * lhs[i - 1][j][k][2][1][l] - lhs[i][j][k][0][2][2] * lhs[i - 1][j][k][2][2][l] - lhs[i][j][k][0][2][3] * lhs[i - 1][j][k][2][3][l] - lhs[i][j][k][0][2][4] * lhs[i - 1][j][k][2][4][l];
                        lhs[i][j][k][1][3][l] = lhs[i][j][k][1][3][l] - lhs[i][j][k][0][3][0] * lhs[i - 1][j][k][2][0][l] - lhs[i][j][k][0][3][1] * lhs[i - 1][j][k][2][1][l] - lhs[i][j][k][0][3][2] * lhs[i - 1][j][k][2][2][l] - lhs[i][j][k][0][3][3] * lhs[i - 1][j][k][2][3][l] - lhs[i][j][k][0][3][4] * lhs[i - 1][j][k][2][4][l];
                        lhs[i][j][k][1][4][l] = lhs[i][j][k][1][4][l] - lhs[i][j][k][0][4][0] * lhs[i - 1][j][k][2][0][l] - lhs[i][j][k][0][4][1] * lhs[i - 1][j][k][2][1][l] - lhs[i][j][k][0][4][2] * lhs[i - 1][j][k][2][2][l] - lhs[i][j][k][0][4][3] * lhs[i - 1][j][k][2][3][l] - lhs[i][j][k][0][4][4] * lhs[i - 1][j][k][2][4][l];
                    }
                };
                {
                    static double pivot;
                    static double coeff;
                    pivot = 1.0 / lhs[i][j][k][1][0][0];
                    lhs[i][j][k][1][0][1] = lhs[i][j][k][1][0][1] * pivot;
                    lhs[i][j][k][1][0][2] = lhs[i][j][k][1][0][2] * pivot;
                    lhs[i][j][k][1][0][3] = lhs[i][j][k][1][0][3] * pivot;
                    lhs[i][j][k][1][0][4] = lhs[i][j][k][1][0][4] * pivot;
                    lhs[i][j][k][2][0][0] = lhs[i][j][k][2][0][0] * pivot;
                    lhs[i][j][k][2][0][1] = lhs[i][j][k][2][0][1] * pivot;
                    lhs[i][j][k][2][0][2] = lhs[i][j][k][2][0][2] * pivot;
                    lhs[i][j][k][2][0][3] = lhs[i][j][k][2][0][3] * pivot;
                    lhs[i][j][k][2][0][4] = lhs[i][j][k][2][0][4] * pivot;
                    rhs[i][j][k][0] = rhs[i][j][k][0] * pivot;
                    coeff = lhs[i][j][k][1][1][0];
                    lhs[i][j][k][1][1][1] = lhs[i][j][k][1][1][1] - coeff * lhs[i][j][k][1][0][1];
                    lhs[i][j][k][1][1][2] = lhs[i][j][k][1][1][2] - coeff * lhs[i][j][k][1][0][2];
                    lhs[i][j][k][1][1][3] = lhs[i][j][k][1][1][3] - coeff * lhs[i][j][k][1][0][3];
                    lhs[i][j][k][1][1][4] = lhs[i][j][k][1][1][4] - coeff * lhs[i][j][k][1][0][4];
                    lhs[i][j][k][2][1][0] = lhs[i][j][k][2][1][0] - coeff * lhs[i][j][k][2][0][0];
                    lhs[i][j][k][2][1][1] = lhs[i][j][k][2][1][1] - coeff * lhs[i][j][k][2][0][1];
                    lhs[i][j][k][2][1][2] = lhs[i][j][k][2][1][2] - coeff * lhs[i][j][k][2][0][2];
                    lhs[i][j][k][2][1][3] = lhs[i][j][k][2][1][3] - coeff * lhs[i][j][k][2][0][3];
                    lhs[i][j][k][2][1][4] = lhs[i][j][k][2][1][4] - coeff * lhs[i][j][k][2][0][4];
                    rhs[i][j][k][1] = rhs[i][j][k][1] - coeff * rhs[i][j][k][0];
                    coeff = lhs[i][j][k][1][2][0];
                    lhs[i][j][k][1][2][1] = lhs[i][j][k][1][2][1] - coeff * lhs[i][j][k][1][0][1];
                    lhs[i][j][k][1][2][2] = lhs[i][j][k][1][2][2] - coeff * lhs[i][j][k][1][0][2];
                    lhs[i][j][k][1][2][3] = lhs[i][j][k][1][2][3] - coeff * lhs[i][j][k][1][0][3];
                    lhs[i][j][k][1][2][4] = lhs[i][j][k][1][2][4] - coeff * lhs[i][j][k][1][0][4];
                    lhs[i][j][k][2][2][0] = lhs[i][j][k][2][2][0] - coeff * lhs[i][j][k][2][0][0];
                    lhs[i][j][k][2][2][1] = lhs[i][j][k][2][2][1] - coeff * lhs[i][j][k][2][0][1];
                    lhs[i][j][k][2][2][2] = lhs[i][j][k][2][2][2] - coeff * lhs[i][j][k][2][0][2];
                    lhs[i][j][k][2][2][3] = lhs[i][j][k][2][2][3] - coeff * lhs[i][j][k][2][0][3];
                    lhs[i][j][k][2][2][4] = lhs[i][j][k][2][2][4] - coeff * lhs[i][j][k][2][0][4];
                    rhs[i][j][k][2] = rhs[i][j][k][2] - coeff * rhs[i][j][k][0];
                    coeff = lhs[i][j][k][1][3][0];
                    lhs[i][j][k][1][3][1] = lhs[i][j][k][1][3][1] - coeff * lhs[i][j][k][1][0][1];
                    lhs[i][j][k][1][3][2] = lhs[i][j][k][1][3][2] - coeff * lhs[i][j][k][1][0][2];
                    lhs[i][j][k][1][3][3] = lhs[i][j][k][1][3][3] - coeff * lhs[i][j][k][1][0][3];
                    lhs[i][j][k][1][3][4] = lhs[i][j][k][1][3][4] - coeff * lhs[i][j][k][1][0][4];
                    lhs[i][j][k][2][3][0] = lhs[i][j][k][2][3][0] - coeff * lhs[i][j][k][2][0][0];
                    lhs[i][j][k][2][3][1] = lhs[i][j][k][2][3][1] - coeff * lhs[i][j][k][2][0][1];
                    lhs[i][j][k][2][3][2] = lhs[i][j][k][2][3][2] - coeff * lhs[i][j][k][2][0][2];
                    lhs[i][j][k][2][3][3] = lhs[i][j][k][2][3][3] - coeff * lhs[i][j][k][2][0][3];
                    lhs[i][j][k][2][3][4] = lhs[i][j][k][2][3][4] - coeff * lhs[i][j][k][2][0][4];
                    rhs[i][j][k][3] = rhs[i][j][k][3] - coeff * rhs[i][j][k][0];
                    coeff = lhs[i][j][k][1][4][0];
                    lhs[i][j][k][1][4][1] = lhs[i][j][k][1][4][1] - coeff * lhs[i][j][k][1][0][1];
                    lhs[i][j][k][1][4][2] = lhs[i][j][k][1][4][2] - coeff * lhs[i][j][k][1][0][2];
                    lhs[i][j][k][1][4][3] = lhs[i][j][k][1][4][3] - coeff * lhs[i][j][k][1][0][3];
                    lhs[i][j][k][1][4][4] = lhs[i][j][k][1][4][4] - coeff * lhs[i][j][k][1][0][4];
                    lhs[i][j][k][2][4][0] = lhs[i][j][k][2][4][0] - coeff * lhs[i][j][k][2][0][0];
                    lhs[i][j][k][2][4][1] = lhs[i][j][k][2][4][1] - coeff * lhs[i][j][k][2][0][1];
                    lhs[i][j][k][2][4][2] = lhs[i][j][k][2][4][2] - coeff * lhs[i][j][k][2][0][2];
                    lhs[i][j][k][2][4][3] = lhs[i][j][k][2][4][3] - coeff * lhs[i][j][k][2][0][3];
                    lhs[i][j][k][2][4][4] = lhs[i][j][k][2][4][4] - coeff * lhs[i][j][k][2][0][4];
                    rhs[i][j][k][4] = rhs[i][j][k][4] - coeff * rhs[i][j][k][0];
                    pivot = 1.0 / lhs[i][j][k][1][1][1];
                    lhs[i][j][k][1][1][2] = lhs[i][j][k][1][1][2] * pivot;
                    lhs[i][j][k][1][1][3] = lhs[i][j][k][1][1][3] * pivot;
                    lhs[i][j][k][1][1][4] = lhs[i][j][k][1][1][4] * pivot;
                    lhs[i][j][k][2][1][0] = lhs[i][j][k][2][1][0] * pivot;
                    lhs[i][j][k][2][1][1] = lhs[i][j][k][2][1][1] * pivot;
                    lhs[i][j][k][2][1][2] = lhs[i][j][k][2][1][2] * pivot;
                    lhs[i][j][k][2][1][3] = lhs[i][j][k][2][1][3] * pivot;
                    lhs[i][j][k][2][1][4] = lhs[i][j][k][2][1][4] * pivot;
                    rhs[i][j][k][1] = rhs[i][j][k][1] * pivot;
                    coeff = lhs[i][j][k][1][0][1];
                    lhs[i][j][k][1][0][2] = lhs[i][j][k][1][0][2] - coeff * lhs[i][j][k][1][1][2];
                    lhs[i][j][k][1][0][3] = lhs[i][j][k][1][0][3] - coeff * lhs[i][j][k][1][1][3];
                    lhs[i][j][k][1][0][4] = lhs[i][j][k][1][0][4] - coeff * lhs[i][j][k][1][1][4];
                    lhs[i][j][k][2][0][0] = lhs[i][j][k][2][0][0] - coeff * lhs[i][j][k][2][1][0];
                    lhs[i][j][k][2][0][1] = lhs[i][j][k][2][0][1] - coeff * lhs[i][j][k][2][1][1];
                    lhs[i][j][k][2][0][2] = lhs[i][j][k][2][0][2] - coeff * lhs[i][j][k][2][1][2];
                    lhs[i][j][k][2][0][3] = lhs[i][j][k][2][0][3] - coeff * lhs[i][j][k][2][1][3];
                    lhs[i][j][k][2][0][4] = lhs[i][j][k][2][0][4] - coeff * lhs[i][j][k][2][1][4];
                    rhs[i][j][k][0] = rhs[i][j][k][0] - coeff * rhs[i][j][k][1];
                    coeff = lhs[i][j][k][1][2][1];
                    lhs[i][j][k][1][2][2] = lhs[i][j][k][1][2][2] - coeff * lhs[i][j][k][1][1][2];
                    lhs[i][j][k][1][2][3] = lhs[i][j][k][1][2][3] - coeff * lhs[i][j][k][1][1][3];
                    lhs[i][j][k][1][2][4] = lhs[i][j][k][1][2][4] - coeff * lhs[i][j][k][1][1][4];
                    lhs[i][j][k][2][2][0] = lhs[i][j][k][2][2][0] - coeff * lhs[i][j][k][2][1][0];
                    lhs[i][j][k][2][2][1] = lhs[i][j][k][2][2][1] - coeff * lhs[i][j][k][2][1][1];
                    lhs[i][j][k][2][2][2] = lhs[i][j][k][2][2][2] - coeff * lhs[i][j][k][2][1][2];
                    lhs[i][j][k][2][2][3] = lhs[i][j][k][2][2][3] - coeff * lhs[i][j][k][2][1][3];
                    lhs[i][j][k][2][2][4] = lhs[i][j][k][2][2][4] - coeff * lhs[i][j][k][2][1][4];
                    rhs[i][j][k][2] = rhs[i][j][k][2] - coeff * rhs[i][j][k][1];
                    coeff = lhs[i][j][k][1][3][1];
                    lhs[i][j][k][1][3][2] = lhs[i][j][k][1][3][2] - coeff * lhs[i][j][k][1][1][2];
                    lhs[i][j][k][1][3][3] = lhs[i][j][k][1][3][3] - coeff * lhs[i][j][k][1][1][3];
                    lhs[i][j][k][1][3][4] = lhs[i][j][k][1][3][4] - coeff * lhs[i][j][k][1][1][4];
                    lhs[i][j][k][2][3][0] = lhs[i][j][k][2][3][0] - coeff * lhs[i][j][k][2][1][0];
                    lhs[i][j][k][2][3][1] = lhs[i][j][k][2][3][1] - coeff * lhs[i][j][k][2][1][1];
                    lhs[i][j][k][2][3][2] = lhs[i][j][k][2][3][2] - coeff * lhs[i][j][k][2][1][2];
                    lhs[i][j][k][2][3][3] = lhs[i][j][k][2][3][3] - coeff * lhs[i][j][k][2][1][3];
                    lhs[i][j][k][2][3][4] = lhs[i][j][k][2][3][4] - coeff * lhs[i][j][k][2][1][4];
                    rhs[i][j][k][3] = rhs[i][j][k][3] - coeff * rhs[i][j][k][1];
                    coeff = lhs[i][j][k][1][4][1];
                    lhs[i][j][k][1][4][2] = lhs[i][j][k][1][4][2] - coeff * lhs[i][j][k][1][1][2];
                    lhs[i][j][k][1][4][3] = lhs[i][j][k][1][4][3] - coeff * lhs[i][j][k][1][1][3];
                    lhs[i][j][k][1][4][4] = lhs[i][j][k][1][4][4] - coeff * lhs[i][j][k][1][1][4];
                    lhs[i][j][k][2][4][0] = lhs[i][j][k][2][4][0] - coeff * lhs[i][j][k][2][1][0];
                    lhs[i][j][k][2][4][1] = lhs[i][j][k][2][4][1] - coeff * lhs[i][j][k][2][1][1];
                    lhs[i][j][k][2][4][2] = lhs[i][j][k][2][4][2] - coeff * lhs[i][j][k][2][1][2];
                    lhs[i][j][k][2][4][3] = lhs[i][j][k][2][4][3] - coeff * lhs[i][j][k][2][1][3];
                    lhs[i][j][k][2][4][4] = lhs[i][j][k][2][4][4] - coeff * lhs[i][j][k][2][1][4];
                    rhs[i][j][k][4] = rhs[i][j][k][4] - coeff * rhs[i][j][k][1];
                    pivot = 1.0 / lhs[i][j][k][1][2][2];
                    lhs[i][j][k][1][2][3] = lhs[i][j][k][1][2][3] * pivot;
                    lhs[i][j][k][1][2][4] = lhs[i][j][k][1][2][4] * pivot;
                    lhs[i][j][k][2][2][0] = lhs[i][j][k][2][2][0] * pivot;
                    lhs[i][j][k][2][2][1] = lhs[i][j][k][2][2][1] * pivot;
                    lhs[i][j][k][2][2][2] = lhs[i][j][k][2][2][2] * pivot;
                    lhs[i][j][k][2][2][3] = lhs[i][j][k][2][2][3] * pivot;
                    lhs[i][j][k][2][2][4] = lhs[i][j][k][2][2][4] * pivot;
                    rhs[i][j][k][2] = rhs[i][j][k][2] * pivot;
                    coeff = lhs[i][j][k][1][0][2];
                    lhs[i][j][k][1][0][3] = lhs[i][j][k][1][0][3] - coeff * lhs[i][j][k][1][2][3];
                    lhs[i][j][k][1][0][4] = lhs[i][j][k][1][0][4] - coeff * lhs[i][j][k][1][2][4];
                    lhs[i][j][k][2][0][0] = lhs[i][j][k][2][0][0] - coeff * lhs[i][j][k][2][2][0];
                    lhs[i][j][k][2][0][1] = lhs[i][j][k][2][0][1] - coeff * lhs[i][j][k][2][2][1];
                    lhs[i][j][k][2][0][2] = lhs[i][j][k][2][0][2] - coeff * lhs[i][j][k][2][2][2];
                    lhs[i][j][k][2][0][3] = lhs[i][j][k][2][0][3] - coeff * lhs[i][j][k][2][2][3];
                    lhs[i][j][k][2][0][4] = lhs[i][j][k][2][0][4] - coeff * lhs[i][j][k][2][2][4];
                    rhs[i][j][k][0] = rhs[i][j][k][0] - coeff * rhs[i][j][k][2];
                    coeff = lhs[i][j][k][1][1][2];
                    lhs[i][j][k][1][1][3] = lhs[i][j][k][1][1][3] - coeff * lhs[i][j][k][1][2][3];
                    lhs[i][j][k][1][1][4] = lhs[i][j][k][1][1][4] - coeff * lhs[i][j][k][1][2][4];
                    lhs[i][j][k][2][1][0] = lhs[i][j][k][2][1][0] - coeff * lhs[i][j][k][2][2][0];
                    lhs[i][j][k][2][1][1] = lhs[i][j][k][2][1][1] - coeff * lhs[i][j][k][2][2][1];
                    lhs[i][j][k][2][1][2] = lhs[i][j][k][2][1][2] - coeff * lhs[i][j][k][2][2][2];
                    lhs[i][j][k][2][1][3] = lhs[i][j][k][2][1][3] - coeff * lhs[i][j][k][2][2][3];
                    lhs[i][j][k][2][1][4] = lhs[i][j][k][2][1][4] - coeff * lhs[i][j][k][2][2][4];
                    rhs[i][j][k][1] = rhs[i][j][k][1] - coeff * rhs[i][j][k][2];
                    coeff = lhs[i][j][k][1][3][2];
                    lhs[i][j][k][1][3][3] = lhs[i][j][k][1][3][3] - coeff * lhs[i][j][k][1][2][3];
                    lhs[i][j][k][1][3][4] = lhs[i][j][k][1][3][4] - coeff * lhs[i][j][k][1][2][4];
                    lhs[i][j][k][2][3][0] = lhs[i][j][k][2][3][0] - coeff * lhs[i][j][k][2][2][0];
                    lhs[i][j][k][2][3][1] = lhs[i][j][k][2][3][1] - coeff * lhs[i][j][k][2][2][1];
                    lhs[i][j][k][2][3][2] = lhs[i][j][k][2][3][2] - coeff * lhs[i][j][k][2][2][2];
                    lhs[i][j][k][2][3][3] = lhs[i][j][k][2][3][3] - coeff * lhs[i][j][k][2][2][3];
                    lhs[i][j][k][2][3][4] = lhs[i][j][k][2][3][4] - coeff * lhs[i][j][k][2][2][4];
                    rhs[i][j][k][3] = rhs[i][j][k][3] - coeff * rhs[i][j][k][2];
                    coeff = lhs[i][j][k][1][4][2];
                    lhs[i][j][k][1][4][3] = lhs[i][j][k][1][4][3] - coeff * lhs[i][j][k][1][2][3];
                    lhs[i][j][k][1][4][4] = lhs[i][j][k][1][4][4] - coeff * lhs[i][j][k][1][2][4];
                    lhs[i][j][k][2][4][0] = lhs[i][j][k][2][4][0] - coeff * lhs[i][j][k][2][2][0];
                    lhs[i][j][k][2][4][1] = lhs[i][j][k][2][4][1] - coeff * lhs[i][j][k][2][2][1];
                    lhs[i][j][k][2][4][2] = lhs[i][j][k][2][4][2] - coeff * lhs[i][j][k][2][2][2];
                    lhs[i][j][k][2][4][3] = lhs[i][j][k][2][4][3] - coeff * lhs[i][j][k][2][2][3];
                    lhs[i][j][k][2][4][4] = lhs[i][j][k][2][4][4] - coeff * lhs[i][j][k][2][2][4];
                    rhs[i][j][k][4] = rhs[i][j][k][4] - coeff * rhs[i][j][k][2];
                    pivot = 1.0 / lhs[i][j][k][1][3][3];
                    lhs[i][j][k][1][3][4] = lhs[i][j][k][1][3][4] * pivot;
                    lhs[i][j][k][2][3][0] = lhs[i][j][k][2][3][0] * pivot;
                    lhs[i][j][k][2][3][1] = lhs[i][j][k][2][3][1] * pivot;
                    lhs[i][j][k][2][3][2] = lhs[i][j][k][2][3][2] * pivot;
                    lhs[i][j][k][2][3][3] = lhs[i][j][k][2][3][3] * pivot;
                    lhs[i][j][k][2][3][4] = lhs[i][j][k][2][3][4] * pivot;
                    rhs[i][j][k][3] = rhs[i][j][k][3] * pivot;
                    coeff = lhs[i][j][k][1][0][3];
                    lhs[i][j][k][1][0][4] = lhs[i][j][k][1][0][4] - coeff * lhs[i][j][k][1][3][4];
                    lhs[i][j][k][2][0][0] = lhs[i][j][k][2][0][0] - coeff * lhs[i][j][k][2][3][0];
                    lhs[i][j][k][2][0][1] = lhs[i][j][k][2][0][1] - coeff * lhs[i][j][k][2][3][1];
                    lhs[i][j][k][2][0][2] = lhs[i][j][k][2][0][2] - coeff * lhs[i][j][k][2][3][2];
                    lhs[i][j][k][2][0][3] = lhs[i][j][k][2][0][3] - coeff * lhs[i][j][k][2][3][3];
                    lhs[i][j][k][2][0][4] = lhs[i][j][k][2][0][4] - coeff * lhs[i][j][k][2][3][4];
                    rhs[i][j][k][0] = rhs[i][j][k][0] - coeff * rhs[i][j][k][3];
                    coeff = lhs[i][j][k][1][1][3];
                    lhs[i][j][k][1][1][4] = lhs[i][j][k][1][1][4] - coeff * lhs[i][j][k][1][3][4];
                    lhs[i][j][k][2][1][0] = lhs[i][j][k][2][1][0] - coeff * lhs[i][j][k][2][3][0];
                    lhs[i][j][k][2][1][1] = lhs[i][j][k][2][1][1] - coeff * lhs[i][j][k][2][3][1];
                    lhs[i][j][k][2][1][2] = lhs[i][j][k][2][1][2] - coeff * lhs[i][j][k][2][3][2];
                    lhs[i][j][k][2][1][3] = lhs[i][j][k][2][1][3] - coeff * lhs[i][j][k][2][3][3];
                    lhs[i][j][k][2][1][4] = lhs[i][j][k][2][1][4] - coeff * lhs[i][j][k][2][3][4];
                    rhs[i][j][k][1] = rhs[i][j][k][1] - coeff * rhs[i][j][k][3];
                    coeff = lhs[i][j][k][1][2][3];
                    lhs[i][j][k][1][2][4] = lhs[i][j][k][1][2][4] - coeff * lhs[i][j][k][1][3][4];
                    lhs[i][j][k][2][2][0] = lhs[i][j][k][2][2][0] - coeff * lhs[i][j][k][2][3][0];
                    lhs[i][j][k][2][2][1] = lhs[i][j][k][2][2][1] - coeff * lhs[i][j][k][2][3][1];
                    lhs[i][j][k][2][2][2] = lhs[i][j][k][2][2][2] - coeff * lhs[i][j][k][2][3][2];
                    lhs[i][j][k][2][2][3] = lhs[i][j][k][2][2][3] - coeff * lhs[i][j][k][2][3][3];
                    lhs[i][j][k][2][2][4] = lhs[i][j][k][2][2][4] - coeff * lhs[i][j][k][2][3][4];
                    rhs[i][j][k][2] = rhs[i][j][k][2] - coeff * rhs[i][j][k][3];
                    coeff = lhs[i][j][k][1][4][3];
                    lhs[i][j][k][1][4][4] = lhs[i][j][k][1][4][4] - coeff * lhs[i][j][k][1][3][4];
                    lhs[i][j][k][2][4][0] = lhs[i][j][k][2][4][0] - coeff * lhs[i][j][k][2][3][0];
                    lhs[i][j][k][2][4][1] = lhs[i][j][k][2][4][1] - coeff * lhs[i][j][k][2][3][1];
                    lhs[i][j][k][2][4][2] = lhs[i][j][k][2][4][2] - coeff * lhs[i][j][k][2][3][2];
                    lhs[i][j][k][2][4][3] = lhs[i][j][k][2][4][3] - coeff * lhs[i][j][k][2][3][3];
                    lhs[i][j][k][2][4][4] = lhs[i][j][k][2][4][4] - coeff * lhs[i][j][k][2][3][4];
                    rhs[i][j][k][4] = rhs[i][j][k][4] - coeff * rhs[i][j][k][3];
                    pivot = 1.0 / lhs[i][j][k][1][4][4];
                    lhs[i][j][k][2][4][0] = lhs[i][j][k][2][4][0] * pivot;
                    lhs[i][j][k][2][4][1] = lhs[i][j][k][2][4][1] * pivot;
                    lhs[i][j][k][2][4][2] = lhs[i][j][k][2][4][2] * pivot;
                    lhs[i][j][k][2][4][3] = lhs[i][j][k][2][4][3] * pivot;
                    lhs[i][j][k][2][4][4] = lhs[i][j][k][2][4][4] * pivot;
                    rhs[i][j][k][4] = rhs[i][j][k][4] * pivot;
                    coeff = lhs[i][j][k][1][0][4];
                    lhs[i][j][k][2][0][0] = lhs[i][j][k][2][0][0] - coeff * lhs[i][j][k][2][4][0];
                    lhs[i][j][k][2][0][1] = lhs[i][j][k][2][0][1] - coeff * lhs[i][j][k][2][4][1];
                    lhs[i][j][k][2][0][2] = lhs[i][j][k][2][0][2] - coeff * lhs[i][j][k][2][4][2];
                    lhs[i][j][k][2][0][3] = lhs[i][j][k][2][0][3] - coeff * lhs[i][j][k][2][4][3];
                    lhs[i][j][k][2][0][4] = lhs[i][j][k][2][0][4] - coeff * lhs[i][j][k][2][4][4];
                    rhs[i][j][k][0] = rhs[i][j][k][0] - coeff * rhs[i][j][k][4];
                    coeff = lhs[i][j][k][1][1][4];
                    lhs[i][j][k][2][1][0] = lhs[i][j][k][2][1][0] - coeff * lhs[i][j][k][2][4][0];
                    lhs[i][j][k][2][1][1] = lhs[i][j][k][2][1][1] - coeff * lhs[i][j][k][2][4][1];
                    lhs[i][j][k][2][1][2] = lhs[i][j][k][2][1][2] - coeff * lhs[i][j][k][2][4][2];
                    lhs[i][j][k][2][1][3] = lhs[i][j][k][2][1][3] - coeff * lhs[i][j][k][2][4][3];
                    lhs[i][j][k][2][1][4] = lhs[i][j][k][2][1][4] - coeff * lhs[i][j][k][2][4][4];
                    rhs[i][j][k][1] = rhs[i][j][k][1] - coeff * rhs[i][j][k][4];
                    coeff = lhs[i][j][k][1][2][4];
                    lhs[i][j][k][2][2][0] = lhs[i][j][k][2][2][0] - coeff * lhs[i][j][k][2][4][0];
                    lhs[i][j][k][2][2][1] = lhs[i][j][k][2][2][1] - coeff * lhs[i][j][k][2][4][1];
                    lhs[i][j][k][2][2][2] = lhs[i][j][k][2][2][2] - coeff * lhs[i][j][k][2][4][2];
                    lhs[i][j][k][2][2][3] = lhs[i][j][k][2][2][3] - coeff * lhs[i][j][k][2][4][3];
                    lhs[i][j][k][2][2][4] = lhs[i][j][k][2][2][4] - coeff * lhs[i][j][k][2][4][4];
                    rhs[i][j][k][2] = rhs[i][j][k][2] - coeff * rhs[i][j][k][4];
                    coeff = lhs[i][j][k][1][3][4];
                    lhs[i][j][k][2][3][0] = lhs[i][j][k][2][3][0] - coeff * lhs[i][j][k][2][4][0];
                    lhs[i][j][k][2][3][1] = lhs[i][j][k][2][3][1] - coeff * lhs[i][j][k][2][4][1];
                    lhs[i][j][k][2][3][2] = lhs[i][j][k][2][3][2] - coeff * lhs[i][j][k][2][4][2];
                    lhs[i][j][k][2][3][3] = lhs[i][j][k][2][3][3] - coeff * lhs[i][j][k][2][4][3];
                    lhs[i][j][k][2][3][4] = lhs[i][j][k][2][3][4] - coeff * lhs[i][j][k][2][4][4];
                    rhs[i][j][k][3] = rhs[i][j][k][3] - coeff * rhs[i][j][k][4];
                };
            }
        }
    }

#pragma endscop
}
