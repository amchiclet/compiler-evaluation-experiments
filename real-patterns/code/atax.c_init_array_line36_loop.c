#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int m;
extern int j;
extern int n;
extern double  A[1900 + 0][2100 + 0] ;

void loop()
{
#pragma scop

    for(i = 0; i < m; i++) for(j = 0; j < n; j++) A[i][j] =((double )((i + j) % n)) /(5 * m);

#pragma endscop
}
