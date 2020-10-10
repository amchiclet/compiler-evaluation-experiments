#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern double * restrict cbval;
extern int * restrict partition;
extern double  bark[513] ;

void loop()
{
#pragma scop

    for(i = 0; i < 513; i++) cbval[partition[i]] += bark[i];

#pragma endscop
}
