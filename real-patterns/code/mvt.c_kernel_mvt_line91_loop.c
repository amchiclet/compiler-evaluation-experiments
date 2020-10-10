#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int n;
extern int j;
extern double  x2[2000 + 0] ;
extern double  A[2000 + 0][2000 + 0] ;
extern double  y_2[2000 + 0] ;

void loop()
{
#pragma scop

    for(i = 0; i < n; i++) for(j = 0; j < n; j++) x2[i] = x2[i] + A[j][i] * y_2[j];

#pragma endscop
}
