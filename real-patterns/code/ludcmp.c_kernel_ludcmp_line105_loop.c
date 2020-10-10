#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int n;
extern int j;
extern double w;
extern double  A[2000 + 0][2000 + 0] ;
extern int k;

void loop()
{
#pragma scop

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < i; j++)
        {
            w = A[i][j];
            for(k = 0; k < j; k++)
            {
                w -= A[i][k] * A[k][j];
            }
            A[i][j] = w / A[j][j];
        }
        for(j = i; j < n; j++)
        {
            w = A[i][j];
            for(k = 0; k < i; k++)
            {
                w -= A[i][k] * A[k][j];
            }
            A[i][j] = w;
        }
    }

#pragma endscop
}
