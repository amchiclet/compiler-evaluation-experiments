#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int n;
extern int j;
extern double  C[1200 + 0][1200 + 0] ;
extern double beta;
extern int k;
extern int m;
extern double alpha;
extern double  A[1200 + 0][1000 + 0] ;

void loop()
{
#pragma scop

    for(i = 0; i < n; i++)
    {
        for(j = 0; j <= i; j++) C[i][j] *= beta;
        for(k = 0; k < m; k++)
        {
            for(j = 0; j <= i; j++) C[i][j] += alpha * A[i][k] * A[j][k];
        }
    }

#pragma endscop
}
