#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int m;
extern double  tmp[1900 + 0] ;
extern int j;
extern int n;
extern double  A[1900 + 0][2100 + 0] ;
extern double  x[2100 + 0] ;
extern double  y[2100 + 0] ;

void loop()
{
#pragma scop

    for(i = 0; i < m; i++)
    {
        tmp[i] = 0.0;
        for(j = 0; j < n; j++) tmp[i] = tmp[i] + A[i][j] * x[j];
        for(j = 0; j < n; j++) y[j] = y[j] + A[i][j] * tmp[i];
    }

#pragma endscop
}
