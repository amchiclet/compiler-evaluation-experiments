#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int n;
extern int j;
extern int m;
extern double  data[1400 + 0][1200 + 0] ;
extern double  mean[1200 + 0] ;

void loop()
{
#pragma scop

    for(i = 0; i < n; i++) for(j = 0; j < m; j++) data[i][j] -= mean[j];

#pragma endscop
}
