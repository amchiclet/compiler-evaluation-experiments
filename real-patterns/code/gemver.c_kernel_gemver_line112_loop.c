#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int n;
extern int j;
extern double  w[2000 + 0] ;
extern double alpha;
extern double  A[2000 + 0][2000 + 0] ;
extern double  x[2000 + 0] ;

void loop()
{
#pragma scop

    for(i = 0; i < n; i++) for(j = 0; j < n; j++) w[i] = w[i] + alpha * A[i][j] * x[j];

#pragma endscop
}
