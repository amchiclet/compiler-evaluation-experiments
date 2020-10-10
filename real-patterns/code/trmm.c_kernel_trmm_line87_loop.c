#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int m;
extern int j;
extern int n;
extern int k;
extern double  B[1000 + 0][1200 + 0] ;
extern double  A[1000 + 0][1000 + 0] ;
extern double alpha;

void loop()
{
#pragma scop

    for(i = 0; i < m; i++) for(j = 0; j < n; j++)
        {
            for(k = i + 1; k < m; k++) B[i][j] += A[k][i] * B[k][j];
            B[i][j] = alpha * B[i][j];
        }

#pragma endscop
}
