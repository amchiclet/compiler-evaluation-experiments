#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int n;
extern int j;
extern int k;
extern double  A[2000 + 0][2000 + 0] ;

void loop()
{
#pragma scop

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < i; j++)
        {
            for(k = 0; k < j; k++)
            {
                A[i][j] -= A[i][k] * A[k][j];
            }
            A[i][j] /= A[j][j];
        }
        for(j = i; j < n; j++)
        {
            for(k = 0; k < i; k++)
            {
                A[i][j] -= A[i][k] * A[k][j];
            }
        }
    }

#pragma endscop
}
