#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int t;
extern int i;
extern int n;
extern int j;
extern int k;
extern double  B[120 + 0][120 + 0][120 + 0] ;
extern double  A[120 + 0][120 + 0][120 + 0] ;

void loop()
{
#pragma scop

    for(t = 1; t <= 500; t++)
    {
        for(i = 1; i < n - 1; i++)
        {
            for(j = 1; j < n - 1; j++)
            {
                for(k = 1; k < n - 1; k++)
                {
                    B[i][j][k] = 0.125 *(A[i + 1][j][k] - 2.0 * A[i][j][k] + A[i - 1][j][k]) + 0.125 *(A[i][j + 1][k] - 2.0 * A[i][j][k] + A[i][j - 1][k]) + 0.125 *(A[i][j][k + 1] - 2.0 * A[i][j][k] + A[i][j][k - 1]) + A[i][j][k];
                }
            }
        }
        for(i = 1; i < n - 1; i++)
        {
            for(j = 1; j < n - 1; j++)
            {
                for(k = 1; k < n - 1; k++)
                {
                    A[i][j][k] = 0.125 *(B[i + 1][j][k] - 2.0 * B[i][j][k] + B[i - 1][j][k]) + 0.125 *(B[i][j + 1][k] - 2.0 * B[i][j][k] + B[i][j - 1][k]) + 0.125 *(B[i][j][k + 1] - 2.0 * B[i][j][k] + B[i][j][k - 1]) + B[i][j][k];
                }
            }
        }
    }

#pragma endscop
}
