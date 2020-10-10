#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int n;
extern int j;
extern int m;
extern double  A[1200 + 0][1000 + 0] ;

void loop()
{
#pragma scop

    for(i = 0; i < n; i++) for(j = 0; j < m; j++) A[i][j] =((double )(i * j % n)) / n;

#pragma endscop
}
