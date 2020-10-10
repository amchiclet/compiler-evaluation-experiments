#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int n;
extern int j;
extern double  x[2000 + 0] ;
extern double beta;
extern double  A[2000 + 0][2000 + 0] ;
extern double  y[2000 + 0] ;

void loop()
{
#pragma scop

    for(i = 0; i < n; i++) for(j = 0; j < n; j++) x[i] = x[i] + beta * A[j][i] * y[j];

#pragma endscop
}
