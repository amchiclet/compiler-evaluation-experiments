#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int n;
extern int j;
extern int k;
extern double  A[120 + 0][120 + 0][120 + 0] ;
extern double  B[120 + 0][120 + 0][120 + 0] ;

void loop()
{
#pragma scop

    for(i = 0; i < n; i++) for(j = 0; j < n; j++) for(k = 0; k < n; k++) A[i][j][k] = B[i][j][k] =((double )(i + j +(n - k))) * 10 / n;

#pragma endscop
}
