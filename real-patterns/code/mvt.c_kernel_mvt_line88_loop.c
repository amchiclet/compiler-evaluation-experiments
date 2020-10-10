#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int n;
extern int j;
extern double  x1[2000 + 0] ;
extern double  A[2000 + 0][2000 + 0] ;
extern double  y_1[2000 + 0] ;

void loop()
{
#pragma scop

    for(i = 0; i < n; i++) for(j = 0; j < n; j++) x1[i] = x1[i] + A[i][j] * y_1[j];

#pragma endscop
}
