#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int n;
extern double  x[2100 + 0] ;
extern double fn;

void loop()
{
#pragma scop

    for(i = 0; i < n; i++) x[i] = 1 + i / fn;

#pragma endscop
}
