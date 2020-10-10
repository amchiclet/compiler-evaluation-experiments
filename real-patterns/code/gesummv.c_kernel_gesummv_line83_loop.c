#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int n;
extern double  tmp[1300 + 0] ;
extern double  y[1300 + 0] ;
extern int j;
extern double  A[1300 + 0][1300 + 0] ;
extern double  x[1300 + 0] ;
extern double  B[1300 + 0][1300 + 0] ;
extern double alpha;
extern double beta;

void loop()
{
#pragma scop

    for(i = 0; i < n; i++)
    {
        tmp[i] = 0.0;
        y[i] = 0.0;
        for(j = 0; j < n; j++)
        {
            tmp[i] = A[i][j] * x[j] + tmp[i];
            y[i] = B[i][j] * x[j] + y[i];
        }
        y[i] = alpha * tmp[i] + beta * y[i];
    }

#pragma endscop
}
