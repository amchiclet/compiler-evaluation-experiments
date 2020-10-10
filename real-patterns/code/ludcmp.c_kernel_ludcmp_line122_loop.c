#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int n;
extern double w;
extern double  b[2000 + 0] ;
extern int j;
extern double  A[2000 + 0][2000 + 0] ;
extern double  y[2000 + 0] ;

void loop()
{
#pragma scop

    for(i = 0; i < n; i++)
    {
        w = b[i];
        for(j = 0; j < i; j++) w -= A[i][j] * y[j];
        y[i] = w;
    }

#pragma endscop
}
