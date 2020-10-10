#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int n;
extern double  x[1 << 6] ;
extern double  floatcoefs[1 << 6][1 << 6] ;
extern int j;

void loop()
{
#pragma scop

    for(i = 0; i < n; i++) x[i] = floatcoefs[i][j];

#pragma endscop
}
