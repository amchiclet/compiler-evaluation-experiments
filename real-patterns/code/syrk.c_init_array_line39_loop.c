#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int n;
extern int j;
extern double  C[1200 + 0][1200 + 0] ;
extern int m;

void loop()
{
#pragma scop

    for(i = 0; i < n; i++) for(j = 0; j < n; j++) C[i][j] =((double )(i * j % m)) / m;

#pragma endscop
}
