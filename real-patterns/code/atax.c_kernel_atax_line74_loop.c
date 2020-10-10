#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int n;
extern double  y[2100 + 0] ;

void loop()
{
#pragma scop

    for(i = 0; i < n; i++) y[i] = 0;

#pragma endscop
}
