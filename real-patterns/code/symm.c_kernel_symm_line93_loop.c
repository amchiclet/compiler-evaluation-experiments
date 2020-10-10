#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int m;
extern int j;
extern int n;
extern double temp2;
extern int k;
extern double  C[1000 + 0][1200 + 0] ;
extern double alpha;
extern double  B[1000 + 0][1200 + 0] ;
extern double  A[1000 + 0][1000 + 0] ;
extern double beta;

void loop()
{
#pragma scop

    for(i = 0; i < m; i++) for(j = 0; j < n; j++)
        {
            temp2 = 0;
            for(k = 0; k < i; k++)
            {
                C[k][j] += alpha * B[i][j] * A[i][k];
                temp2 += B[k][j] * A[i][k];
            }
            C[i][j] = beta * C[i][j] + alpha * B[i][j] * A[i][i] + alpha * temp2;
        }

#pragma endscop
}
