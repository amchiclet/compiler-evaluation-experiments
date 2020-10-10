#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int n;
extern int j;
extern double  A[2000 + 0][2000 + 0] ;

void loop()
{
#pragma scop

    for(i = 0; i < n; i++) for(j = 0; j < n; j++) A[i][j] =(((double )i) *(j + 2) + 2) / n;

#pragma endscop
}
