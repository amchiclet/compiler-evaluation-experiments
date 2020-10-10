#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int n;
extern double  x[2000 + 0] ;
extern double  z[2000 + 0] ;

void loop()
{
#pragma scop

    for(i = 0; i < n; i++) x[i] = x[i] + z[i];

#pragma endscop
}
