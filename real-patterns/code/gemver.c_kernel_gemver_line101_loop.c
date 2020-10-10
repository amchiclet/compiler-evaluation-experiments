#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int n;
extern int j;
extern double  A[2000 + 0][2000 + 0] ;
extern double  u1[2000 + 0] ;
extern double  v1[2000 + 0] ;
extern double  u2[2000 + 0] ;
extern double  v2[2000 + 0] ;

void loop()
{
#pragma scop

    for(i = 0; i < n; i++) for(j = 0; j < n; j++) A[i][j] = A[i][j] + u1[i] * v1[j] + u2[i] * v2[j];

#pragma endscop
}
